#ifndef PHYSICS_FORMULAS_HPP
#define PHYSICS_FORMULAS_HPP

#include <string>
#include <vector>
#include "../dimeval.hpp"

namespace Physics {

struct Variable {
    std::string name;                    // "F", "q_1", "r", etc.
    dv::UnitVector units;           // [m, s, kg, A, K, mol, cd]
    std::string description;             // "Force", "Charge 1", "Distance"
    bool is_constant;                    // true for k, G, epsilon_0, etc.
};

struct Formula {
    std::string name;                    // "Coulomb's Law"
    std::string latex;                   // "F = k \\frac{q_1 q_2}{r^2}"
    std::vector<Variable> variables;     // All variables in the equation
    std::string solve_for;               // "F" (which variable this solves for)
    std::string category;
};

class FormulaDatabase {
public:
    FormulaDatabase();
    const std::vector<Formula> get_formulas() const { return formulas; }
    
private:
    std::vector<Formula> formulas;
};

} // namespace Physics

#endif // PHYSICS_FORMULAS_HPP
