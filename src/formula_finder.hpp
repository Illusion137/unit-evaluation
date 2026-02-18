#include "dimeval.hpp"
#include "formulas/physics_formulas.hpp"
#include <algorithm>
#include <set>
#include <string>
#include <vector>

const auto formula_database = Physics::FormulaDatabase{};

class FormulaSearcher {
private:
    const Physics::FormulaDatabase& db;
public:
    FormulaSearcher() : db(formula_database) {}
    FormulaSearcher(const Physics::FormulaDatabase& database) : db(database) {}
    
    // Search by unit signature (find what you can calculate)
    // Returns exact matches first, then close matches (missing 1 unit) at the end.
    // Deduplicates by formula name.
    std::vector<Physics::Formula> find_by_units(
        const std::vector<dv::UnitVector>& available_units,
        const dv::UnitVector& targetUnit
    ) const {
        struct ScoredFormula {
            Physics::Formula formula;
            int missing;
            int matched;
            int total_inputs;
        };

        auto score_and_collect = [&](
            const std::vector<dv::UnitVector>& units,
            const dv::UnitVector& target,
            int max_missing
        ) -> std::vector<ScoredFormula> {
            std::vector<ScoredFormula> candidates;
            std::set<std::string> seen;

            for (const auto& formula : db.get_formulas()) {
                auto solveForVar = std::find_if(
                    formula.variables.begin(),
                    formula.variables.end(),
                    [&](const Physics::Variable& v) { return v.name == formula.solve_for; }
                );

                if (solveForVar == formula.variables.end()) continue;
                if (target.vec != solveForVar->units) continue;
                if (seen.contains(formula.name)) continue;

                int missing = 0, matched = 0, total_inputs = 0;

                for (const auto& var : formula.variables) {
                    if (var.is_constant) continue;
                    if (var.name == formula.solve_for) continue;

                    total_inputs++;

                    bool found = std::any_of(
                        units.begin(), units.end(),
                        [&](const dv::UnitVector& u) { return u.vec == var.units; }
                    );

                    if (found) matched++;
                    else missing++;
                }

                if (missing > max_missing) continue;

                seen.insert(formula.name);
                candidates.push_back({ formula, missing, matched, total_inputs });
            }

            std::sort(candidates.begin(), candidates.end(),
                [](const ScoredFormula& a, const ScoredFormula& b) {
                    if (a.missing != b.missing) return a.missing < b.missing;
                    if (a.matched != b.matched) return a.matched > b.matched;
                    return a.total_inputs < b.total_inputs;
                }
            );

            return candidates;
        };

        // --- Step 1: Find main formulas ---
        auto main_candidates = score_and_collect(available_units, targetUnit, 1);

        // --- Step 2: Collect all units missing across close-match main formulas ---
        // Also track which units are "reachable" by expanding available_units
        // with outputs of exact subformulas found so far.
        std::set<std::string> seen_subformulas;
        std::vector<Physics::Formula> subformulas;

        // Seed seen_subformulas with main formula names to avoid re-adding them
        for (const auto& sc : main_candidates)
            seen_subformulas.insert(sc.formula.name);

        // Collect missing units from close matches
        std::vector<dv::UnitVector> missing_units;
        for (const auto& sc : main_candidates) {
            if (sc.missing == 0) continue; // only close matches have gaps

            for (const auto& var : sc.formula.variables) {
                if (var.is_constant) continue;
                if (var.name == sc.formula.solve_for) continue;

                bool already_have = std::any_of(
                    available_units.begin(), available_units.end(),
                    [&](const dv::UnitVector& u) { return u.vec == var.units; }
                );
                if (already_have) continue;

                // Avoid duplicate missing unit searches
                bool already_queued = std::any_of(
                    missing_units.begin(), missing_units.end(),
                    [&](const dv::UnitVector& u) { return u.vec == var.units; }
                );
                if (!already_queued)
                    missing_units.push_back({ var.units });
            }
        }

        // --- Step 3: For each missing unit, find exact subformulas ---
        // Expand available units as we find subformulas (breadth-first, one level)
        std::vector<dv::UnitVector> expanded_units = available_units;

        for (const auto& missing_unit : missing_units) {
            auto sub_candidates = score_and_collect(expanded_units, missing_unit, 0);

            for (auto& sc : sub_candidates) {
                if (seen_subformulas.contains(sc.formula.name)) continue;
                seen_subformulas.insert(sc.formula.name);

                Physics::Formula tagged = sc.formula;
                tagged.category = "---";
                subformulas.push_back(std::move(tagged));

                // Add this unit to expanded so later missing units can chain
                expanded_units.push_back(missing_unit);
            }
        }

        // --- Step 4: Assemble result ---
        std::vector<Physics::Formula> result;
        result.reserve(main_candidates.size() + subformulas.size());

        for (auto& sc : main_candidates)
            result.push_back(std::move(sc.formula));

        for (auto& f : subformulas)
            result.push_back(std::move(f));

        return result;
    }   
};