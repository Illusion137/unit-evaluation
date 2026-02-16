#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_chemistry_thermochemistry() {
    
    // ========================================================================
    // ENTHALPY CHANGE: Delta_H = H_products - H_reactants
    // ========================================================================
    
    formulas.push_back({
        "Enthalpy Change (solve for Delta_H)",
        "\\Delta H = H_{products} - H_{reactants}",
        {
            {"\\Delta H", {2, -2, 1, 0, 0, 0, 0}, "Enthalpy change", false},
            {"H_{products}", {2, -2, 1, 0, 0, 0, 0}, "Enthalpy of products", false},
            {"H_{reactants}", {2, -2, 1, 0, 0, 0, 0}, "Enthalpy of reactants", false}
        },
        "Chemistry - Thermochemistry",
        "Enthalpy Change",
        "\\Delta H"
    });
    
    formulas.push_back({
        "Enthalpy Change (solve for H_products)",
        "H_{products} = \\Delta H + H_{reactants}",
        {
            {"H_{products}", {2, -2, 1, 0, 0, 0, 0}, "Enthalpy of products", false},
            {"\\Delta H", {2, -2, 1, 0, 0, 0, 0}, "Enthalpy change", false},
            {"H_{reactants}", {2, -2, 1, 0, 0, 0, 0}, "Enthalpy of reactants", false}
        },
        "Chemistry - Thermochemistry",
        "Enthalpy Change",
        "H_{products}"
    });
    
    formulas.push_back({
        "Enthalpy Change (solve for H_reactants)",
        "H_{reactants} = H_{products} - \\Delta H",
        {
            {"H_{reactants}", {2, -2, 1, 0, 0, 0, 0}, "Enthalpy of reactants", false},
            {"H_{products}", {2, -2, 1, 0, 0, 0, 0}, "Enthalpy of products", false},
            {"\\Delta H", {2, -2, 1, 0, 0, 0, 0}, "Enthalpy change", false}
        },
        "Chemistry - Thermochemistry",
        "Enthalpy Change",
        "H_{reactants}"
    });
    
    // ========================================================================
    // GIBBS FREE ENERGY: Delta_G = Delta_H - T * Delta_S
    // ========================================================================
    
    formulas.push_back({
        "Gibbs Free Energy (solve for Delta_G)",
        "\\Delta G = \\Delta H - T\\Delta S",
        {
            {"\\Delta G", {2, -2, 1, 0, 0, 0, 0}, "Gibbs free energy change", false},
            {"\\Delta H", {2, -2, 1, 0, 0, 0, 0}, "Enthalpy change", false},
            {"T", {0, 0, 0, 0, 1, 0, 0}, "Temperature", false},
            {"\\Delta S", {2, -2, 1, 0, -1, 0, 0}, "Entropy change", false}
        },
        "Chemistry - Thermochemistry",
        "Gibbs Free Energy",
        "\\Delta G"
    });
    
    formulas.push_back({
        "Gibbs Free Energy (solve for Delta_H)",
        "\\Delta H = \\Delta G + T\\Delta S",
        {
            {"\\Delta H", {2, -2, 1, 0, 0, 0, 0}, "Enthalpy change", false},
            {"\\Delta G", {2, -2, 1, 0, 0, 0, 0}, "Gibbs free energy change", false},
            {"T", {0, 0, 0, 0, 1, 0, 0}, "Temperature", false},
            {"\\Delta S", {2, -2, 1, 0, -1, 0, 0}, "Entropy change", false}
        },
        "Chemistry - Thermochemistry",
        "Gibbs Free Energy",
        "\\Delta H"
    });
    
    formulas.push_back({
        "Gibbs Free Energy (solve for T)",
        "T = \\frac{\\Delta H - \\Delta G}{\\Delta S}",
        {
            {"T", {0, 0, 0, 0, 1, 0, 0}, "Temperature", false},
            {"\\Delta H", {2, -2, 1, 0, 0, 0, 0}, "Enthalpy change", false},
            {"\\Delta G", {2, -2, 1, 0, 0, 0, 0}, "Gibbs free energy change", false},
            {"\\Delta S", {2, -2, 1, 0, -1, 0, 0}, "Entropy change", false}
        },
        "Chemistry - Thermochemistry",
        "Gibbs Free Energy",
        "T"
    });
    
    formulas.push_back({
        "Gibbs Free Energy (solve for Delta_S)",
        "\\Delta S = \\frac{\\Delta H - \\Delta G}{T}",
        {
            {"\\Delta S", {2, -2, 1, 0, -1, 0, 0}, "Entropy change", false},
            {"\\Delta H", {2, -2, 1, 0, 0, 0, 0}, "Enthalpy change", false},
            {"\\Delta G", {2, -2, 1, 0, 0, 0, 0}, "Gibbs free energy change", false},
            {"T", {0, 0, 0, 0, 1, 0, 0}, "Temperature", false}
        },
        "Chemistry - Thermochemistry",
        "Gibbs Free Energy",
        "\\Delta S"
    });
    
    // ========================================================================
    // GIBBS FREE ENERGY AND EQUILIBRIUM: Delta_G = -RT * ln(K)
    // ========================================================================
    
    formulas.push_back({
        "Gibbs Free Energy and Equilibrium (solve for Delta_G)",
        "\\Delta G = -RT\\ln K",
        {
            {"\\Delta G", {2, -2, 1, 0, 0, 0, 0}, "Gibbs free energy change", false},
            {"R", {2, -2, 1, 0, -1, -1, 0}, "Gas constant", true},
            {"T", {0, 0, 0, 0, 1, 0, 0}, "Temperature", false},
            {"K", {0, 0, 0, 0, 0, 0, 0}, "Equilibrium constant", false}
        },
        "Chemistry - Thermochemistry",
        "Gibbs Free Energy and Equilibrium",
        "\\Delta G"
    });
    
    formulas.push_back({
        "Gibbs Free Energy and Equilibrium (solve for K)",
        "K = e^{-\\Delta G / RT}",
        {
            {"K", {0, 0, 0, 0, 0, 0, 0}, "Equilibrium constant", false},
            {"\\Delta G", {2, -2, 1, 0, 0, 0, 0}, "Gibbs free energy change", false},
            {"R", {2, -2, 1, 0, -1, -1, 0}, "Gas constant", true},
            {"T", {0, 0, 0, 0, 1, 0, 0}, "Temperature", false}
        },
        "Chemistry - Thermochemistry",
        "Gibbs Free Energy and Equilibrium",
        "K"
    });
    
    formulas.push_back({
        "Gibbs Free Energy and Equilibrium (solve for T)",
        "T = -\\frac{\\Delta G}{R\\ln K}",
        {
            {"T", {0, 0, 0, 0, 1, 0, 0}, "Temperature", false},
            {"\\Delta G", {2, -2, 1, 0, 0, 0, 0}, "Gibbs free energy change", false},
            {"R", {2, -2, 1, 0, -1, -1, 0}, "Gas constant", true},
            {"K", {0, 0, 0, 0, 0, 0, 0}, "Equilibrium constant", false}
        },
        "Chemistry - Thermochemistry",
        "Gibbs Free Energy and Equilibrium",
        "T"
    });
}

} // namespace Physics
