#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_chemistry_kinetics() {
    
    // ========================================================================
    // ARRHENIUS EQUATION: k = A * exp(-E_a / RT)
    // Logarithmic form: ln(k) = ln(A) - E_a/RT
    // ========================================================================
    
    formulas.push_back({
        "Arrhenius Equation Logarithmic (solve for ln_k)",
        "\\ln k = \\ln A - \\frac{E_a}{RT}",
        {
            {"\\ln k", {0, 0, 0, 0, 0, 0, 0}, "Natural log of rate constant", false},
            {"\\ln A", {0, 0, 0, 0, 0, 0, 0}, "Natural log of frequency factor", false},
            {"E_a", {2, -2, 1, 0, 0, 0, 0}, "Activation energy", false},
            {"R", {2, -2, 1, 0, -1, -1, 0}, "Gas constant", true},
            {"T", {0, 0, 0, 0, 1, 0, 0}, "Temperature", false}
        },
        "Chemistry - Kinetics",
        "Arrhenius Equation Logarithmic",
        "\\ln k"
    });
    
    // ========================================================================
    // FIRST ORDER HALF-LIFE: t_1/2 = 0.693 / k
    // ========================================================================
    
    formulas.push_back({
        "First Order Half-Life (solve for t_half)",
        "t_{1/2} = \\frac{0.693}{k}",
        {
            {"t_{1/2}", {0, 1, 0, 0, 0, 0, 0}, "Half-life", false},
            {"k", {0, -1, 0, 0, 0, 0, 0}, "Rate constant", false}
        },
        "Chemistry - Kinetics",
        "First Order Half-Life",
        "t_{1/2}"
    });
    
    formulas.push_back({
        "First Order Half-Life (solve for k)",
        "k = \\frac{0.693}{t_{1/2}}",
        {
            {"k", {0, -1, 0, 0, 0, 0, 0}, "Rate constant", false},
            {"t_{1/2}", {0, 1, 0, 0, 0, 0, 0}, "Half-life", false}
        },
        "Chemistry - Kinetics",
        "First Order Half-Life",
        "k"
    });
    
    // ========================================================================
    // FIRST ORDER INTEGRATED RATE LAW: ln[A] = ln[A]_0 - kt
    // ========================================================================
    
    formulas.push_back({
        "First Order Rate Law (relationship)",
        "\\ln[A] = \\ln[A]_0 - kt",
        {
            {"\\ln[A]", {0, 0, 0, 0, 0, 0, 0}, "Natural log of concentration", false},
            {"\\ln[A]_0", {0, 0, 0, 0, 0, 0, 0}, "Natural log of initial concentration", false},
            {"k", {0, -1, 0, 0, 0, 0, 0}, "Rate constant", false},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false}
        },
        "Chemistry - Kinetics",
        "First Order Rate Law",
        "relationship"
    });
    
    // ========================================================================
    // SECOND ORDER HALF-LIFE: t_1/2 = 1 / (k * [A]_0)
    // ========================================================================
    
    formulas.push_back({
        "Second Order Half-Life (solve for t_half)",
        "t_{1/2} = \\frac{1}{k[A]_0}",
        {
            {"t_{1/2}", {0, 1, 0, 0, 0, 0, 0}, "Half-life", false},
            {"k", {3, -1, 0, 0, 0, -1, 0}, "Rate constant", false},
            {"[A]_0", {-3, 0, 0, 0, 0, 1, 0}, "Initial concentration", false}
        },
        "Chemistry - Kinetics",
        "Second Order Half-Life",
        "t_{1/2}"
    });
    
    formulas.push_back({
        "Second Order Half-Life (solve for k)",
        "k = \\frac{1}{t_{1/2}[A]_0}",
        {
            {"k", {3, -1, 0, 0, 0, -1, 0}, "Rate constant", false},
            {"t_{1/2}", {0, 1, 0, 0, 0, 0, 0}, "Half-life", false},
            {"[A]_0", {-3, 0, 0, 0, 0, 1, 0}, "Initial concentration", false}
        },
        "Chemistry - Kinetics",
        "Second Order Half-Life",
        "k"
    });
}

} // namespace Physics
