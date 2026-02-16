#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_induction() {
    
    // ========================================================================
    // FARADAY'S LAW: EMF = -N * dPhi/dt (simplified: EMF = N * Delta_Phi / Delta_t)
    // ========================================================================
    
    formulas.push_back({
        "Faraday's Law (solve for EMF)",
        "\\varepsilon = N \\frac{\\Delta \\Phi}{\\Delta t}",
        {
            {"\\varepsilon", {2, -3, 1, -1, 0, 0, 0}, "Induced EMF", false},
            {"N", {0, 0, 0, 0, 0, 0, 0}, "Number of turns", false},
            {"\\Delta \\Phi", {2, -2, 1, -1, 0, 0, 0}, "Change in magnetic flux", false},
            {"\\Delta t", {0, 1, 0, 0, 0, 0, 0}, "Time interval", false}
        },
        "Induction",
        "Faraday's Law",
        "\\varepsilon"
    });
    
    formulas.push_back({
        "Faraday's Law (solve for N)",
        "N = \\frac{\\varepsilon \\Delta t}{\\Delta \\Phi}",
        {
            {"N", {0, 0, 0, 0, 0, 0, 0}, "Number of turns", false},
            {"\\varepsilon", {2, -3, 1, -1, 0, 0, 0}, "Induced EMF", false},
            {"\\Delta t", {0, 1, 0, 0, 0, 0, 0}, "Time interval", false},
            {"\\Delta \\Phi", {2, -2, 1, -1, 0, 0, 0}, "Change in magnetic flux", false}
        },
        "Induction",
        "Faraday's Law",
        "N"
    });
    
    formulas.push_back({
        "Faraday's Law (solve for Delta_Phi)",
        "\\Delta \\Phi = \\frac{\\varepsilon \\Delta t}{N}",
        {
            {"\\Delta \\Phi", {2, -2, 1, -1, 0, 0, 0}, "Change in magnetic flux", false},
            {"\\varepsilon", {2, -3, 1, -1, 0, 0, 0}, "Induced EMF", false},
            {"\\Delta t", {0, 1, 0, 0, 0, 0, 0}, "Time interval", false},
            {"N", {0, 0, 0, 0, 0, 0, 0}, "Number of turns", false}
        },
        "Induction",
        "Faraday's Law",
        "\\Delta \\Phi"
    });
    
    formulas.push_back({
        "Faraday's Law (solve for Delta_t)",
        "\\Delta t = \\frac{N \\Delta \\Phi}{\\varepsilon}",
        {
            {"\\Delta t", {0, 1, 0, 0, 0, 0, 0}, "Time interval", false},
            {"N", {0, 0, 0, 0, 0, 0, 0}, "Number of turns", false},
            {"\\Delta \\Phi", {2, -2, 1, -1, 0, 0, 0}, "Change in magnetic flux", false},
            {"\\varepsilon", {2, -3, 1, -1, 0, 0, 0}, "Induced EMF", false}
        },
        "Induction",
        "Faraday's Law",
        "\\Delta t"
    });
    
    // ========================================================================
    // MOTIONAL EMF: EMF = B * L * v
    // ========================================================================
    
    formulas.push_back({
        "Motional EMF (solve for EMF)",
        "\\varepsilon = BLv",
        {
            {"\\varepsilon", {2, -3, 1, -1, 0, 0, 0}, "Induced EMF", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"L", {1, 0, 0, 0, 0, 0, 0}, "Length", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false}
        },
        "Induction",
        "Motional EMF",
        "\\varepsilon"
    });
    
    formulas.push_back({
        "Motional EMF (solve for B)",
        "B = \\frac{\\varepsilon}{Lv}",
        {
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"\\varepsilon", {2, -3, 1, -1, 0, 0, 0}, "Induced EMF", false},
            {"L", {1, 0, 0, 0, 0, 0, 0}, "Length", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false}
        },
        "Induction",
        "Motional EMF",
        "B"
    });
    
    formulas.push_back({
        "Motional EMF (solve for L)",
        "L = \\frac{\\varepsilon}{Bv}",
        {
            {"L", {1, 0, 0, 0, 0, 0, 0}, "Length", false},
            {"\\varepsilon", {2, -3, 1, -1, 0, 0, 0}, "Induced EMF", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false}
        },
        "Induction",
        "Motional EMF",
        "L"
    });
    
    formulas.push_back({
        "Motional EMF (solve for v)",
        "v = \\frac{\\varepsilon}{BL}",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"\\varepsilon", {2, -3, 1, -1, 0, 0, 0}, "Induced EMF", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"L", {1, 0, 0, 0, 0, 0, 0}, "Length", false}
        },
        "Induction",
        "Motional EMF",
        "v"
    });
    
    // ========================================================================
    // INDUCTANCE EMF: EMF = -L * dI/dt (simplified: EMF = L * Delta_I / Delta_t)
    // ========================================================================
    
    formulas.push_back({
        "Inductance EMF (solve for EMF)",
        "\\varepsilon = L \\frac{\\Delta I}{\\Delta t}",
        {
            {"\\varepsilon", {2, -3, 1, -1, 0, 0, 0}, "Induced EMF", false},
            {"L", {2, -2, 1, -2, 0, 0, 0}, "Inductance", false},
            {"\\Delta I", {0, 0, 0, 1, 0, 0, 0}, "Change in current", false},
            {"\\Delta t", {0, 1, 0, 0, 0, 0, 0}, "Time interval", false}
        },
        "Induction",
        "Inductance EMF",
        "\\varepsilon"
    });
    
    formulas.push_back({
        "Inductance EMF (solve for L)",
        "L = \\frac{\\varepsilon \\Delta t}{\\Delta I}",
        {
            {"L", {2, -2, 1, -2, 0, 0, 0}, "Inductance", false},
            {"\\varepsilon", {2, -3, 1, -1, 0, 0, 0}, "Induced EMF", false},
            {"\\Delta t", {0, 1, 0, 0, 0, 0, 0}, "Time interval", false},
            {"\\Delta I", {0, 0, 0, 1, 0, 0, 0}, "Change in current", false}
        },
        "Induction",
        "Inductance EMF",
        "L"
    });
    
    formulas.push_back({
        "Inductance EMF (solve for Delta_I)",
        "\\Delta I = \\frac{\\varepsilon \\Delta t}{L}",
        {
            {"\\Delta I", {0, 0, 0, 1, 0, 0, 0}, "Change in current", false},
            {"\\varepsilon", {2, -3, 1, -1, 0, 0, 0}, "Induced EMF", false},
            {"\\Delta t", {0, 1, 0, 0, 0, 0, 0}, "Time interval", false},
            {"L", {2, -2, 1, -2, 0, 0, 0}, "Inductance", false}
        },
        "Induction",
        "Inductance EMF",
        "\\Delta I"
    });
    
    formulas.push_back({
        "Inductance EMF (solve for Delta_t)",
        "\\Delta t = \\frac{L \\Delta I}{\\varepsilon}",
        {
            {"\\Delta t", {0, 1, 0, 0, 0, 0, 0}, "Time interval", false},
            {"L", {2, -2, 1, -2, 0, 0, 0}, "Inductance", false},
            {"\\Delta I", {0, 0, 0, 1, 0, 0, 0}, "Change in current", false},
            {"\\varepsilon", {2, -3, 1, -1, 0, 0, 0}, "Induced EMF", false}
        },
        "Induction",
        "Inductance EMF",
        "\\Delta t"
    });
    
    // ========================================================================
    // INDUCTOR ENERGY: U = (1/2) * L * I^2
    // ========================================================================
    
    formulas.push_back({
        "Inductor Energy (solve for U)",
        "U = \\frac{1}{2} L I^2",
        {
            {"U", {2, -2, 1, 0, 0, 0, 0}, "Energy", false},
            {"L", {2, -2, 1, -2, 0, 0, 0}, "Inductance", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false}
        },
        "Induction",
        "Inductor Energy",
        "U"
    });
    
    formulas.push_back({
        "Inductor Energy (solve for L)",
        "L = \\frac{2U}{I^2}",
        {
            {"L", {2, -2, 1, -2, 0, 0, 0}, "Inductance", false},
            {"U", {2, -2, 1, 0, 0, 0, 0}, "Energy", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false}
        },
        "Induction",
        "Inductor Energy",
        "L"
    });
    
    formulas.push_back({
        "Inductor Energy (solve for I)",
        "I = \\sqrt{\\frac{2U}{L}}",
        {
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"U", {2, -2, 1, 0, 0, 0, 0}, "Energy", false},
            {"L", {2, -2, 1, -2, 0, 0, 0}, "Inductance", false}
        },
        "Induction",
        "Inductor Energy",
        "I"
    });
    
    // ========================================================================
    // LR TIME CONSTANT: tau = L / R
    // ========================================================================
    
    formulas.push_back({
        "LR Time Constant (solve for tau)",
        "\\tau = \\frac{L}{R}",
        {
            {"\\tau", {0, 1, 0, 0, 0, 0, 0}, "Time constant", false},
            {"L", {2, -2, 1, -2, 0, 0, 0}, "Inductance", false},
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false}
        },
        "Induction",
        "LR Time Constant",
        "\\tau"
    });
    
    formulas.push_back({
        "LR Time Constant (solve for L)",
        "L = \\tau R",
        {
            {"L", {2, -2, 1, -2, 0, 0, 0}, "Inductance", false},
            {"\\tau", {0, 1, 0, 0, 0, 0, 0}, "Time constant", false},
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false}
        },
        "Induction",
        "LR Time Constant",
        "L"
    });
    
    formulas.push_back({
        "LR Time Constant (solve for R)",
        "R = \\frac{L}{\\tau}",
        {
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false},
            {"L", {2, -2, 1, -2, 0, 0, 0}, "Inductance", false},
            {"\\tau", {0, 1, 0, 0, 0, 0, 0}, "Time constant", false}
        },
        "Induction",
        "LR Time Constant",
        "R"
    });
    
    // ========================================================================
    // SOLENOID INDUCTANCE: L = mu_0 * n^2 * A * l
    // ========================================================================
    
    formulas.push_back({
        "Solenoid Inductance (solve for L)",
        "L = \\mu_0 n^2 A l",
        {
            {"L", {2, -2, 1, -2, 0, 0, 0}, "Inductance", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true},
            {"n", {-1, 0, 0, 0, 0, 0, 0}, "Turns per unit length", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Cross-sectional area", false},
            {"l", {1, 0, 0, 0, 0, 0, 0}, "Length", false}
        },
        "Induction",
        "Solenoid Inductance",
        "L"
    });
    
    formulas.push_back({
        "Solenoid Inductance (solve for n)",
        "n = \\sqrt{\\frac{L}{\\mu_0 A l}}",
        {
            {"n", {-1, 0, 0, 0, 0, 0, 0}, "Turns per unit length", false},
            {"L", {2, -2, 1, -2, 0, 0, 0}, "Inductance", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Cross-sectional area", false},
            {"l", {1, 0, 0, 0, 0, 0, 0}, "Length", false}
        },
        "Induction",
        "Solenoid Inductance",
        "n"
    });
    
    formulas.push_back({
        "Solenoid Inductance (solve for A)",
        "A = \\frac{L}{\\mu_0 n^2 l}",
        {
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Cross-sectional area", false},
            {"L", {2, -2, 1, -2, 0, 0, 0}, "Inductance", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true},
            {"n", {-1, 0, 0, 0, 0, 0, 0}, "Turns per unit length", false},
            {"l", {1, 0, 0, 0, 0, 0, 0}, "Length", false}
        },
        "Induction",
        "Solenoid Inductance",
        "A"
    });
    
    formulas.push_back({
        "Solenoid Inductance (solve for l)",
        "l = \\frac{L}{\\mu_0 n^2 A}",
        {
            {"l", {1, 0, 0, 0, 0, 0, 0}, "Length", false},
            {"L", {2, -2, 1, -2, 0, 0, 0}, "Inductance", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true},
            {"n", {-1, 0, 0, 0, 0, 0, 0}, "Turns per unit length", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Cross-sectional area", false}
        },
        "Induction",
        "Solenoid Inductance",
        "l"
    });
    
    // ========================================================================
    // LC CIRCUIT FREQUENCY: omega = 1 / sqrt(L * C)
    // ========================================================================
    
    formulas.push_back({
        "LC Circuit Angular Frequency (solve for omega)",
        "\\omega = \\frac{1}{\\sqrt{LC}}",
        {
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular frequency", false},
            {"L", {2, -2, 1, -2, 0, 0, 0}, "Inductance", false},
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false}
        },
        "Induction",
        "LC Circuit Angular Frequency",
        "\\omega"
    });
    
    formulas.push_back({
        "LC Circuit Angular Frequency (solve for L)",
        "L = \\frac{1}{\\omega^2 C}",
        {
            {"L", {2, -2, 1, -2, 0, 0, 0}, "Inductance", false},
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular frequency", false},
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false}
        },
        "Induction",
        "LC Circuit Angular Frequency",
        "L"
    });
    
    formulas.push_back({
        "LC Circuit Angular Frequency (solve for C)",
        "C = \\frac{1}{\\omega^2 L}",
        {
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false},
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular frequency", false},
            {"L", {2, -2, 1, -2, 0, 0, 0}, "Inductance", false}
        },
        "Induction",
        "LC Circuit Angular Frequency",
        "C"
    });
}

} // namespace Physics
