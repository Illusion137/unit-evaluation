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
            int missing;        // 0 = exact, 1 = close
            int matched;        // how many inputs were matched from available_units
            int total_inputs;   // total non-constant, non-solve_for variables
        };

        std::vector<ScoredFormula> candidates;
        std::set<std::string> seen;

        for (const auto& formula : db.get_formulas()) {
            auto solveForVar = std::find_if(
                formula.variables.begin(),
                formula.variables.end(),
                [&](const Physics::Variable& v) { return v.name == formula.solve_for; }
            );

            if (solveForVar == formula.variables.end()) continue;
            if (targetUnit.vec != solveForVar->units) continue;
            if (seen.contains(formula.name)) continue;

            int missing = 0;
            int matched = 0;
            int total_inputs = 0;

            for (const auto& var : formula.variables) {
                if (var.is_constant) continue;
                if (var.name == formula.solve_for) continue;

                total_inputs++;

                bool found = std::any_of(
                    available_units.begin(),
                    available_units.end(),
                    [&](const dv::UnitVector& unit) { return unit.vec == var.units; }
                );

                if (found) matched++;
                else missing++;
            }

            if (missing > 1) continue;

            seen.insert(formula.name);
            candidates.push_back({ formula, missing, matched, total_inputs });
        }

        // Sort by:
        // 1. Exact matches before close matches (missing == 0 first)
        // 2. Higher matched count first (uses more of your available units)
        // 3. Lower total_inputs first (simpler formula wins ties)
        std::sort(candidates.begin(), candidates.end(),
            [](const ScoredFormula& a, const ScoredFormula& b) {
                if (a.missing != b.missing)
                    return a.missing < b.missing;
                if (a.matched != b.matched)
                    return a.matched > b.matched;
                return a.total_inputs < b.total_inputs;
            }
        );

        std::vector<Physics::Formula> result;
        result.reserve(candidates.size());
        for (auto& sc : candidates)
            result.push_back(std::move(sc.formula));
        return result;
    }
    
};