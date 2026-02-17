#include "dimeval.hpp"
#include "formulas/physics_formulas.hpp"
#include <vector>

const auto formula_database = Physics::FormulaDatabase{};

class FormulaSearcher {
private:
    const Physics::FormulaDatabase& db;
public:
    FormulaSearcher() : db(formula_database) {}
    FormulaSearcher(const Physics::FormulaDatabase& database) : db(database) {}
    
    // Search by available variables and their units
    // std::vector<Physics::Formula> find_formulas(
    //     const std::map<std::string, dv::EValue>& availableVars,
    //     const std::string& solveFor = ""
    // ) const {
    //     std::vector<Physics::Formula> matches;
        
    //     for (const auto& formula : db.get_formulas()) {
    //         // If we want to solve for a specific variable, check if this formula does
    //         if (!solveFor.empty() && formula.solve_for != solveFor) {
    //             continue;
    //         }
            
    //         // Check if we have all required non-constant variables
    //         bool hasAllVars = true;
    //         std::multiset<dv::UnitVector> requiredUnits;
    //         std::multiset<dv::UnitVector> availableUnits;
            
    //         for (const auto& var : formula.variables) {
    //             // Skip constants
    //             if (var.is_constant) continue;
                
    //             // Skip the variable we're solving for
    //             if (var.name == formula.solve_for) continue;
                
    //             // Check if we have this variable (by unit matching)
    //             bool found = false;
    //             for (const auto& [name, evalue] : availableVars) {
    //                 if (evalue.unit.vec == var.units) {
    //                     found = true;
    //                     break;
    //                 }
    //             }
                
    //             if (!found) {
    //                 hasAllVars = false;
    //                 break;
    //             }
                
    //             requiredUnits.insert(var.units);
    //         }
            
    //         // Also verify unit counts match (for formulas with repeated variables)
    //         if (hasAllVars) {
    //             for (const auto& [name, evalue] : availableVars) {
    //                 availableUnits.insert(evalue.unit);
    //             }
                
    //             if (requiredUnits == availableUnits || requiredUnits.size() <= availableUnits.size()) {
    //                 matches.push_back(formula);
    //             }
    //         }
    //     }
        
    //     return matches;
    // }
    
    // Search by unit signature (find what you can calculate)
    std::vector<Physics::Formula> find_by_units(
        const std::vector<dv::UnitVector>& available_units,
        const dv::UnitVector& targetUnit
    ) const {
        std::vector<Physics::Formula> matches;
        
        for (const auto &formula : db.get_formulas()) {
            auto solveForVar = std::find_if(
                formula.variables.begin(),
                formula.variables.end(),
                [&](const Physics::Variable& v) { return v.name == formula.solve_for; }
            );
            
            if (solveForVar == formula.variables.end()) continue;
            
            // Check if output unit matches target
            if (targetUnit.vec != solveForVar->units) continue;
            
            // Check if we have all input units
            bool hasAllUnits = true;
            for (const auto& var : formula.variables) {
                if (var.is_constant) continue;
                if (var.name == formula.solve_for) continue;
                
                bool found = false;
                for (const auto& unit : available_units) {
                    if (unit.vec == var.units) {
                        found = true;
                        break;
                    }
                }
                
                if (!found) {
                    hasAllUnits = false;
                    break;
                }
            }
            
            if (hasAllUnits) {
                matches.push_back(formula);
            }
        }
        
        return matches;
    }
    
    // Search by category
    // std::vector<Physics::Formula> find_by_category(const std::string& category) const {
    //     std::vector<Physics::Formula> matches;
        
    //     for (const auto& formula : db.get_formulas()) {
    //         if (formula.category == category) {
    //             matches.push_back(formula);
    //         }
    //     }
        
    //     return matches;
    // }
    
    // // Find what you can solve for given specific variables
    // std::set<std::string> find_possible_outputs(
    //     const std::map<std::string, dv::EValue>& availableVars
    // ) const {
    //     std::set<std::string> outputs;
        
    //     for (const auto& formula : db.get_formulas()) {
    //         bool canUse = true;
            
    //         for (const auto& var : formula.variables) {
    //             if (var.is_constant) continue;
    //             if (var.name == formula.solve_for) continue;
                
    //             bool found = false;
    //             for (const auto& [name, evalue] : availableVars) {
    //                 if (evalue.unit.vec == var.units) {
    //                     found = true;
    //                     break;
    //                 }
    //             }
                
    //             if (!found) {
    //                 canUse = false;
    //                 break;
    //             }
    //         }
            
    //         if (canUse) {
    //             outputs.insert(formula.solve_for);
    //         }
    //     }
        
    //     return outputs;
    // }
};

// Usage Example
// int main() {
//     Physics::FormulaDatabase db;
//     FormulaSearcher searcher(db);
    
//     // Example 1: You have voltage and resistance, want current
//     std::map<std::string, dv::EValue> myVars;
//     myVars["V"] = dv::EValue(12.0, dv::UnitVector{{2, -3, 1, -1, 0, 0, 0}});  // 12V
//     myVars["R"] = dv::EValue(100.0, dv::UnitVector{{2, -3, 1, -2, 0, 0, 0}}); // 100Ω
    
//     auto formulas = searcher.findFormulas(myVars, "I");
    
//     std::cout << "Found " << formulas.size() << " formulas to solve for I:\n";
//     for (const auto& f : formulas) {
//         std::cout << "  - " << f.name << ": " << f.latex << "\n";
//     }
    
//     // Example 2: What can I calculate with these variables?
//     auto possibleOutputs = searcher.findPossibleOutputs(myVars);
//     std::cout << "\nWith V and R, you can solve for:\n";
//     for (const auto& output : possibleOutputs) {
//         std::cout << "  - " << output << "\n";
//     }
    
//     // Example 3: Search by target unit (find all force formulas)
//     dv::UnitVector forceUnit{{1, -2, 1, 0, 0, 0, 0}};  // Force = kg⋅m⋅s⁻²
//     std::vector<dv::UnitVector> available = {
//         dv::UnitVector{{0, 0, 1, 0, 0, 0, 0}},  // mass
//         dv::UnitVector{{1, -2, 0, 0, 0, 0, 0}}   // acceleration
//     };
    
//     auto forceFormulas = searcher.findByUnits(available, forceUnit);
//     std::cout << "\nFormulas that give force from mass and acceleration:\n";
//     for (const auto& f : forceFormulas) {
//         std::cout << "  - " << f.name << "\n";
//     }
    
//     return 0;
// }