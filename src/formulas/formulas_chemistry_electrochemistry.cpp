#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_chemistry_electrochemistry() {
    
    // ========================================================================
    // CELL POTENTIAL: E_cell = E_cathode - E_anode
    // ========================================================================
    
    formulas.push_back({
        "Cell Potential (solve for E_cell)",
        "E_{cell} = E_{cathode} - E_{anode}",
        {
            {"E_{cell}", {2, -3, 1, -1, 0, 0, 0}, "Cell potential", false},
            {"E_{cathode}", {2, -3, 1, -1, 0, 0, 0}, "Cathode potential", false},
            {"E_{anode}", {2, -3, 1, -1, 0, 0, 0}, "Anode potential", false}
        },
        "Chemistry - Electrochemistry",
        "Cell Potential",
        "E_{cell}"
    });
    
    formulas.push_back({
        "Cell Potential (solve for E_cathode)",
        "E_{cathode} = E_{cell} + E_{anode}",
        {
            {"E_{cathode}", {2, -3, 1, -1, 0, 0, 0}, "Cathode potential", false},
            {"E_{cell}", {2, -3, 1, -1, 0, 0, 0}, "Cell potential", false},
            {"E_{anode}", {2, -3, 1, -1, 0, 0, 0}, "Anode potential", false}
        },
        "Chemistry - Electrochemistry",
        "Cell Potential",
        "E_{cathode}"
    });
    
    formulas.push_back({
        "Cell Potential (solve for E_anode)",
        "E_{anode} = E_{cathode} - E_{cell}",
        {
            {"E_{anode}", {2, -3, 1, -1, 0, 0, 0}, "Anode potential", false},
            {"E_{cathode}", {2, -3, 1, -1, 0, 0, 0}, "Cathode potential", false},
            {"E_{cell}", {2, -3, 1, -1, 0, 0, 0}, "Cell potential", false}
        },
        "Chemistry - Electrochemistry",
        "Cell Potential",
        "E_{anode}"
    });
    
    // ========================================================================
    // NERNST EQUATION: E = E° - (RT/nF) * ln(Q)
    // Simplified at 25°C: E = E° - (0.0592/n) * log(Q)
    // ========================================================================
    
    formulas.push_back({
        "Nernst Equation (general form)",
        "E = E^\\circ - \\frac{RT}{nF}\\ln Q",
        {
            {"E", {2, -3, 1, -1, 0, 0, 0}, "Cell potential", false},
            {"E^\\circ", {2, -3, 1, -1, 0, 0, 0}, "Standard cell potential", false},
            {"R", {2, -2, 1, 0, -1, -1, 0}, "Gas constant", true},
            {"T", {0, 0, 0, 0, 1, 0, 0}, "Temperature", false},
            {"n", {0, 0, 0, 0, 0, 0, 0}, "Number of electrons transferred", false},
            {"F", {0, 1, 0, 1, 0, -1, 0}, "Faraday constant", true},
            {"Q", {0, 0, 0, 0, 0, 0, 0}, "Reaction quotient", false}
        },
        "Chemistry - Electrochemistry",
        "Nernst Equation",
        "E"
    });
    
    // ========================================================================
    // FARADAY'S LAW OF ELECTROLYSIS: m = (Q * M) / (n * F)
    // Where Q = charge, M = molar mass, n = electrons, F = Faraday constant
    // ========================================================================
    
    formulas.push_back({
        "Faraday's Law of Electrolysis (solve for m)",
        "m = \\frac{QM}{nF}",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass deposited", false},
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Total charge", false},
            {"M", {0, 0, 1, 0, 0, -1, 0}, "Molar mass", false},
            {"n", {0, 0, 0, 0, 0, 0, 0}, "Number of electrons", false},
            {"F", {0, 1, 0, 1, 0, -1, 0}, "Faraday constant", true}
        },
        "Chemistry - Electrochemistry",
        "Faraday's Law of Electrolysis",
        "m"
    });
    
    formulas.push_back({
        "Faraday's Law of Electrolysis (solve for Q)",
        "Q = \\frac{mnF}{M}",
        {
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Total charge", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass deposited", false},
            {"n", {0, 0, 0, 0, 0, 0, 0}, "Number of electrons", false},
            {"F", {0, 1, 0, 1, 0, -1, 0}, "Faraday constant", true},
            {"M", {0, 0, 1, 0, 0, -1, 0}, "Molar mass", false}
        },
        "Chemistry - Electrochemistry",
        "Faraday's Law of Electrolysis",
        "Q"
    });
    
    // ========================================================================
    // CHARGE: Q = I * t
    // ========================================================================
    
    formulas.push_back({
        "Charge (solve for Q)",
        "Q = It",
        {
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false}
        },
        "Chemistry - Electrochemistry",
        "Charge",
        "Q"
    });
    
    formulas.push_back({
        "Charge (solve for I)",
        "I = \\frac{Q}{t}",
        {
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false}
        },
        "Chemistry - Electrochemistry",
        "Charge",
        "I"
    });
    
    formulas.push_back({
        "Charge (solve for t)",
        "t = \\frac{Q}{I}",
        {
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false},
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false}
        },
        "Chemistry - Electrochemistry",
        "Charge",
        "t"
    });
    
    // ========================================================================
    // GIBBS FREE ENERGY AND CELL POTENTIAL: Delta_G = -n * F * E
    // ========================================================================
    
    formulas.push_back({
        "Gibbs Free Energy from Cell Potential (solve for Delta_G)",
        "\\Delta G = -nFE",
        {
            {"\\Delta G", {2, -2, 1, 0, 0, 0, 0}, "Gibbs free energy change", false},
            {"n", {0, 0, 0, 0, 0, 0, 0}, "Number of electrons", false},
            {"F", {0, 1, 0, 1, 0, -1, 0}, "Faraday constant", true},
            {"E", {2, -3, 1, -1, 0, 0, 0}, "Cell potential", false}
        },
        "Chemistry - Electrochemistry",
        "Gibbs Free Energy from Cell Potential",
        "\\Delta G"
    });
    
    formulas.push_back({
        "Gibbs Free Energy from Cell Potential (solve for E)",
        "E = -\\frac{\\Delta G}{nF}",
        {
            {"E", {2, -3, 1, -1, 0, 0, 0}, "Cell potential", false},
            {"\\Delta G", {2, -2, 1, 0, 0, 0, 0}, "Gibbs free energy change", false},
            {"n", {0, 0, 0, 0, 0, 0, 0}, "Number of electrons", false},
            {"F", {0, 1, 0, 1, 0, -1, 0}, "Faraday constant", true}
        },
        "Chemistry - Electrochemistry",
        "Gibbs Free Energy from Cell Potential",
        "E"
    });
}

} // namespace Physics
