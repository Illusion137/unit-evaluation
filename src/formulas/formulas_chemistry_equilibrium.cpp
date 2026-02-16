#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_chemistry_equilibrium() {
    
    // ========================================================================
    // EQUILIBRIUM CONSTANT (generic relationship)
    // K_c = [products] / [reactants]
    // ========================================================================
    
    formulas.push_back({
        "Equilibrium Constant (conceptual)",
        "K_c = \\frac{[C]^c[D]^d}{[A]^a[B]^b}",
        {
            {"K_c", {0, 0, 0, 0, 0, 0, 0}, "Equilibrium constant", false},
            {"[C]", {-3, 0, 0, 0, 0, 1, 0}, "Concentration of C", false},
            {"[D]", {-3, 0, 0, 0, 0, 1, 0}, "Concentration of D", false},
            {"[A]", {-3, 0, 0, 0, 0, 1, 0}, "Concentration of A", false},
            {"[B]", {-3, 0, 0, 0, 0, 1, 0}, "Concentration of B", false}
        },
        "Chemistry - Equilibrium",
        "Equilibrium Constant",
        "K_c"
    });
    
    // ========================================================================
    // RELATIONSHIP BETWEEN K_c AND K_p: K_p = K_c * (RT)^(Delta_n)
    // ========================================================================
    
    formulas.push_back({
        "Kp and Kc Relationship (conceptual)",
        "K_p = K_c(RT)^{\\Delta n}",
        {
            {"K_p", {0, 0, 0, 0, 0, 0, 0}, "Pressure equilibrium constant", false},
            {"K_c", {0, 0, 0, 0, 0, 0, 0}, "Concentration equilibrium constant", false},
            {"R", {2, -2, 1, 0, -1, -1, 0}, "Gas constant", true},
            {"T", {0, 0, 0, 0, 1, 0, 0}, "Temperature", false},
            {"\\Delta n", {0, 0, 0, 0, 0, 0, 0}, "Change in moles of gas", false}
        },
        "Chemistry - Equilibrium",
        "Kp and Kc Relationship",
        "K_p"
    });
    
    // ========================================================================
    // REACTION QUOTIENT: Q has same form as K
    // ========================================================================
    
    formulas.push_back({
        "Reaction Quotient (conceptual)",
        "Q = \\frac{[C]^c[D]^d}{[A]^a[B]^b}",
        {
            {"Q", {0, 0, 0, 0, 0, 0, 0}, "Reaction quotient", false},
            {"[C]", {-3, 0, 0, 0, 0, 1, 0}, "Concentration of C", false},
            {"[D]", {-3, 0, 0, 0, 0, 1, 0}, "Concentration of D", false},
            {"[A]", {-3, 0, 0, 0, 0, 1, 0}, "Concentration of A", false},
            {"[B]", {-3, 0, 0, 0, 0, 1, 0}, "Concentration of B", false}
        },
        "Chemistry - Equilibrium",
        "Reaction Quotient",
        "Q"
    });
}

} // namespace Physics
