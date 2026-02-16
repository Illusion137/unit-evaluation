#ifndef PHYSICS_FORMULAS_HPP
#define PHYSICS_FORMULAS_HPP

#include <string>
#include <vector>
#include <array>

namespace Physics {

struct Variable {
    std::string name;                    // "F", "q_1", "r", etc.
    std::array<int, 7> units;           // [m, s, kg, A, K, mol, cd]
    std::string description;             // "Force", "Charge 1", "Distance"
    bool is_constant;                    // true for k, G, epsilon_0, etc.
};

struct Formula {
    std::string name;                    // "Coulomb's Law (solve for F)"
    std::string latex;                   // "F = k \\frac{q_1 q_2}{r^2}"
    std::vector<Variable> variables;     // All variables in the equation
    std::string category;                // "Electrostatics", "Kinematics", etc.
    std::string base_formula;            // "Coulomb's Law" (same for all variants)
    std::string solve_for;               // "F" (which variable this solves for)
};

class FormulaDatabase {
public:
    FormulaDatabase();
    const std::vector<Formula>& get_formulas() const { return formulas; }
    
private:
    std::vector<Formula> formulas;
    
    // Each category has its own initialization function
    // Implemented in separate cpp files
    void initialize_electrostatics();
    void initialize_circuits();
    void initialize_magnetism();
    void initialize_induction();
    void initialize_electromagnetic_waves();
    void initialize_kinematics();
    void initialize_dynamics();
    void initialize_circular_motion();
    void initialize_gravity();
    void initialize_energy();
    void initialize_momentum();
    void initialize_rotational_mechanics();
    void initialize_oscillations();
    void initialize_waves();
    void initialize_fluids();
    void initialize_thermodynamics();
    void initialize_optics();
    void initialize_modern_physics();
    void initialize_chemistry_basic();
    void initialize_chemistry_solutions();
    void initialize_chemistry_kinetics();
    void initialize_chemistry_equilibrium();
    void initialize_chemistry_acids_bases();
    void initialize_chemistry_thermochemistry();
    void initialize_chemistry_electrochemistry();
};

} // namespace Physics

#endif // PHYSICS_FORMULAS_HPP
