#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_chemistry_basic() {
    
    // ========================================================================
    // IDEAL GAS LAW: PV = nRT
    // ========================================================================
    
    formulas.push_back({
        "Ideal Gas Law (solve for P)",
        "P = \\frac{nRT}{V}",
        {
            {"P", {-1, -2, 1, 0, 0, 0, 0}, "Pressure", false},
            {"n", {0, 0, 0, 0, 0, 1, 0}, "Moles", false},
            {"R", {2, -2, 1, 0, -1, -1, 0}, "Gas constant", true},
            {"T", {0, 0, 0, 0, 1, 0, 0}, "Temperature", false},
            {"V", {3, 0, 0, 0, 0, 0, 0}, "Volume", false}
        },
        "Chemistry - Basic",
        "Ideal Gas Law",
        "P"
    });
    
    formulas.push_back({
        "Ideal Gas Law (solve for V)",
        "V = \\frac{nRT}{P}",
        {
            {"V", {3, 0, 0, 0, 0, 0, 0}, "Volume", false},
            {"n", {0, 0, 0, 0, 0, 1, 0}, "Moles", false},
            {"R", {2, -2, 1, 0, -1, -1, 0}, "Gas constant", true},
            {"T", {0, 0, 0, 0, 1, 0, 0}, "Temperature", false},
            {"P", {-1, -2, 1, 0, 0, 0, 0}, "Pressure", false}
        },
        "Chemistry - Basic",
        "Ideal Gas Law",
        "V"
    });
    
    formulas.push_back({
        "Ideal Gas Law (solve for n)",
        "n = \\frac{PV}{RT}",
        {
            {"n", {0, 0, 0, 0, 0, 1, 0}, "Moles", false},
            {"P", {-1, -2, 1, 0, 0, 0, 0}, "Pressure", false},
            {"V", {3, 0, 0, 0, 0, 0, 0}, "Volume", false},
            {"R", {2, -2, 1, 0, -1, -1, 0}, "Gas constant", true},
            {"T", {0, 0, 0, 0, 1, 0, 0}, "Temperature", false}
        },
        "Chemistry - Basic",
        "Ideal Gas Law",
        "n"
    });
    
    formulas.push_back({
        "Ideal Gas Law (solve for T)",
        "T = \\frac{PV}{nR}",
        {
            {"T", {0, 0, 0, 0, 1, 0, 0}, "Temperature", false},
            {"P", {-1, -2, 1, 0, 0, 0, 0}, "Pressure", false},
            {"V", {3, 0, 0, 0, 0, 0, 0}, "Volume", false},
            {"n", {0, 0, 0, 0, 0, 1, 0}, "Moles", false},
            {"R", {2, -2, 1, 0, -1, -1, 0}, "Gas constant", true}
        },
        "Chemistry - Basic",
        "Ideal Gas Law",
        "T"
    });
    
    // ========================================================================
    // MOLAR MASS: M = m / n
    // ========================================================================
    
    formulas.push_back({
        "Molar Mass (solve for M)",
        "M = \\frac{m}{n}",
        {
            {"M", {0, 0, 1, 0, 0, -1, 0}, "Molar mass", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"n", {0, 0, 0, 0, 0, 1, 0}, "Moles", false}
        },
        "Chemistry - Basic",
        "Molar Mass",
        "M"
    });
    
    formulas.push_back({
        "Molar Mass (solve for m)",
        "m = Mn",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"M", {0, 0, 1, 0, 0, -1, 0}, "Molar mass", false},
            {"n", {0, 0, 0, 0, 0, 1, 0}, "Moles", false}
        },
        "Chemistry - Basic",
        "Molar Mass",
        "m"
    });
    
    formulas.push_back({
        "Molar Mass (solve for n)",
        "n = \\frac{m}{M}",
        {
            {"n", {0, 0, 0, 0, 0, 1, 0}, "Moles", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"M", {0, 0, 1, 0, 0, -1, 0}, "Molar mass", false}
        },
        "Chemistry - Basic",
        "Molar Mass",
        "n"
    });
    
    // ========================================================================
    // DENSITY: rho = m / V (already in fluids, but repeated for chemistry)
    // ========================================================================
    
    formulas.push_back({
        "Density (solve for rho)",
        "\\rho = \\frac{m}{V}",
        {
            {"\\rho", {-3, 0, 1, 0, 0, 0, 0}, "Density", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"V", {3, 0, 0, 0, 0, 0, 0}, "Volume", false}
        },
        "Chemistry - Basic",
        "Density",
        "\\rho"
    });
    
    formulas.push_back({
        "Density (solve for m)",
        "m = \\rho V",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"\\rho", {-3, 0, 1, 0, 0, 0, 0}, "Density", false},
            {"V", {3, 0, 0, 0, 0, 0, 0}, "Volume", false}
        },
        "Chemistry - Basic",
        "Density",
        "m"
    });
    
    formulas.push_back({
        "Density (solve for V)",
        "V = \\frac{m}{\\rho}",
        {
            {"V", {3, 0, 0, 0, 0, 0, 0}, "Volume", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"\\rho", {-3, 0, 1, 0, 0, 0, 0}, "Density", false}
        },
        "Chemistry - Basic",
        "Density",
        "V"
    });
    
    // ========================================================================
    // PERCENT COMPOSITION: percent = (mass_component / mass_total) * 100
    // ========================================================================
    
    formulas.push_back({
        "Percent Composition (solve for percent)",
        "\\% = \\frac{m_{component}}{m_{total}} \\times 100",
        {
            {"\\%", {0, 0, 0, 0, 0, 0, 0}, "Percent", false},
            {"m_{component}", {0, 0, 1, 0, 0, 0, 0}, "Component mass", false},
            {"m_{total}", {0, 0, 1, 0, 0, 0, 0}, "Total mass", false}
        },
        "Chemistry - Basic",
        "Percent Composition",
        "\\%"
    });
    
    formulas.push_back({
        "Percent Composition (solve for m_component)",
        "m_{component} = \\frac{\\% \\times m_{total}}{100}",
        {
            {"m_{component}", {0, 0, 1, 0, 0, 0, 0}, "Component mass", false},
            {"\\%", {0, 0, 0, 0, 0, 0, 0}, "Percent", false},
            {"m_{total}", {0, 0, 1, 0, 0, 0, 0}, "Total mass", false}
        },
        "Chemistry - Basic",
        "Percent Composition",
        "m_{component}"
    });
    
    formulas.push_back({
        "Percent Composition (solve for m_total)",
        "m_{total} = \\frac{100 \\times m_{component}}{\\%}",
        {
            {"m_{total}", {0, 0, 1, 0, 0, 0, 0}, "Total mass", false},
            {"m_{component}", {0, 0, 1, 0, 0, 0, 0}, "Component mass", false},
            {"\\%", {0, 0, 0, 0, 0, 0, 0}, "Percent", false}
        },
        "Chemistry - Basic",
        "Percent Composition",
        "m_{total}"
    });
}

} // namespace Physics
