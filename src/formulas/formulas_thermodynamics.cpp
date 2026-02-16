#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_thermodynamics() {
    
    // ========================================================================
    // HEAT TRANSFER: Q = m * c * Delta_T
    // ========================================================================
    
    formulas.push_back({
        "Heat Transfer (solve for Q)",
        "Q = mc\\Delta T",
        {
            {"Q", {2, -2, 1, 0, 0, 0, 0}, "Heat", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"c", {2, -2, 0, 0, -1, 0, 0}, "Specific heat capacity", false},
            {"\\Delta T", {0, 0, 0, 0, 1, 0, 0}, "Temperature change", false}
        },
        "Thermodynamics",
        "Heat Transfer",
        "Q"
    });
    
    formulas.push_back({
        "Heat Transfer (solve for m)",
        "m = \\frac{Q}{c\\Delta T}",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"Q", {2, -2, 1, 0, 0, 0, 0}, "Heat", false},
            {"c", {2, -2, 0, 0, -1, 0, 0}, "Specific heat capacity", false},
            {"\\Delta T", {0, 0, 0, 0, 1, 0, 0}, "Temperature change", false}
        },
        "Thermodynamics",
        "Heat Transfer",
        "m"
    });
    
    formulas.push_back({
        "Heat Transfer (solve for c)",
        "c = \\frac{Q}{m\\Delta T}",
        {
            {"c", {2, -2, 0, 0, -1, 0, 0}, "Specific heat capacity", false},
            {"Q", {2, -2, 1, 0, 0, 0, 0}, "Heat", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"\\Delta T", {0, 0, 0, 0, 1, 0, 0}, "Temperature change", false}
        },
        "Thermodynamics",
        "Heat Transfer",
        "c"
    });
    
    formulas.push_back({
        "Heat Transfer (solve for Delta_T)",
        "\\Delta T = \\frac{Q}{mc}",
        {
            {"\\Delta T", {0, 0, 0, 0, 1, 0, 0}, "Temperature change", false},
            {"Q", {2, -2, 1, 0, 0, 0, 0}, "Heat", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"c", {2, -2, 0, 0, -1, 0, 0}, "Specific heat capacity", false}
        },
        "Thermodynamics",
        "Heat Transfer",
        "\\Delta T"
    });
    
    // ========================================================================
    // LATENT HEAT: Q = m * L
    // ========================================================================
    
    formulas.push_back({
        "Latent Heat (solve for Q)",
        "Q = mL",
        {
            {"Q", {2, -2, 1, 0, 0, 0, 0}, "Heat", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"L", {2, -2, 0, 0, 0, 0, 0}, "Latent heat", false}
        },
        "Thermodynamics",
        "Latent Heat",
        "Q"
    });
    
    formulas.push_back({
        "Latent Heat (solve for m)",
        "m = \\frac{Q}{L}",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"Q", {2, -2, 1, 0, 0, 0, 0}, "Heat", false},
            {"L", {2, -2, 0, 0, 0, 0, 0}, "Latent heat", false}
        },
        "Thermodynamics",
        "Latent Heat",
        "m"
    });
    
    formulas.push_back({
        "Latent Heat (solve for L)",
        "L = \\frac{Q}{m}",
        {
            {"L", {2, -2, 0, 0, 0, 0, 0}, "Latent heat", false},
            {"Q", {2, -2, 1, 0, 0, 0, 0}, "Heat", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false}
        },
        "Thermodynamics",
        "Latent Heat",
        "L"
    });
    
    // ========================================================================
    // THERMAL EXPANSION (LINEAR): Delta_L = alpha * L_0 * Delta_T
    // ========================================================================
    
    formulas.push_back({
        "Linear Thermal Expansion (solve for Delta_L)",
        "\\Delta L = \\alpha L_0 \\Delta T",
        {
            {"\\Delta L", {1, 0, 0, 0, 0, 0, 0}, "Change in length", false},
            {"\\alpha", {0, 0, 0, 0, -1, 0, 0}, "Coefficient of linear expansion", false},
            {"L_0", {1, 0, 0, 0, 0, 0, 0}, "Initial length", false},
            {"\\Delta T", {0, 0, 0, 0, 1, 0, 0}, "Temperature change", false}
        },
        "Thermodynamics",
        "Linear Thermal Expansion",
        "\\Delta L"
    });
    
    formulas.push_back({
        "Linear Thermal Expansion (solve for alpha)",
        "\\alpha = \\frac{\\Delta L}{L_0 \\Delta T}",
        {
            {"\\alpha", {0, 0, 0, 0, -1, 0, 0}, "Coefficient of linear expansion", false},
            {"\\Delta L", {1, 0, 0, 0, 0, 0, 0}, "Change in length", false},
            {"L_0", {1, 0, 0, 0, 0, 0, 0}, "Initial length", false},
            {"\\Delta T", {0, 0, 0, 0, 1, 0, 0}, "Temperature change", false}
        },
        "Thermodynamics",
        "Linear Thermal Expansion",
        "\\alpha"
    });
    
    // ========================================================================
    // FIRST LAW OF THERMODYNAMICS: Delta_U = Q - W
    // ========================================================================
    
    formulas.push_back({
        "First Law of Thermodynamics (solve for Delta_U)",
        "\\Delta U = Q - W",
        {
            {"\\Delta U", {2, -2, 1, 0, 0, 0, 0}, "Change in internal energy", false},
            {"Q", {2, -2, 1, 0, 0, 0, 0}, "Heat added", false},
            {"W", {2, -2, 1, 0, 0, 0, 0}, "Work done by system", false}
        },
        "Thermodynamics",
        "First Law of Thermodynamics",
        "\\Delta U"
    });
    
    formulas.push_back({
        "First Law of Thermodynamics (solve for Q)",
        "Q = \\Delta U + W",
        {
            {"Q", {2, -2, 1, 0, 0, 0, 0}, "Heat added", false},
            {"\\Delta U", {2, -2, 1, 0, 0, 0, 0}, "Change in internal energy", false},
            {"W", {2, -2, 1, 0, 0, 0, 0}, "Work done by system", false}
        },
        "Thermodynamics",
        "First Law of Thermodynamics",
        "Q"
    });
    
    formulas.push_back({
        "First Law of Thermodynamics (solve for W)",
        "W = Q - \\Delta U",
        {
            {"W", {2, -2, 1, 0, 0, 0, 0}, "Work done by system", false},
            {"Q", {2, -2, 1, 0, 0, 0, 0}, "Heat added", false},
            {"\\Delta U", {2, -2, 1, 0, 0, 0, 0}, "Change in internal energy", false}
        },
        "Thermodynamics",
        "First Law of Thermodynamics",
        "W"
    });
    
    // ========================================================================
    // CARNOT EFFICIENCY: eta = 1 - T_c / T_h
    // ========================================================================
    
    formulas.push_back({
        "Carnot Efficiency (solve for eta)",
        "\\eta = 1 - \\frac{T_c}{T_h}",
        {
            {"\\eta", {0, 0, 0, 0, 0, 0, 0}, "Efficiency", false},
            {"T_c", {0, 0, 0, 0, 1, 0, 0}, "Cold reservoir temperature", false},
            {"T_h", {0, 0, 0, 0, 1, 0, 0}, "Hot reservoir temperature", false}
        },
        "Thermodynamics",
        "Carnot Efficiency",
        "\\eta"
    });
    
    formulas.push_back({
        "Carnot Efficiency (solve for T_c)",
        "T_c = T_h(1 - \\eta)",
        {
            {"T_c", {0, 0, 0, 0, 1, 0, 0}, "Cold reservoir temperature", false},
            {"T_h", {0, 0, 0, 0, 1, 0, 0}, "Hot reservoir temperature", false},
            {"\\eta", {0, 0, 0, 0, 0, 0, 0}, "Efficiency", false}
        },
        "Thermodynamics",
        "Carnot Efficiency",
        "T_c"
    });
    
    formulas.push_back({
        "Carnot Efficiency (solve for T_h)",
        "T_h = \\frac{T_c}{1 - \\eta}",
        {
            {"T_h", {0, 0, 0, 0, 1, 0, 0}, "Hot reservoir temperature", false},
            {"T_c", {0, 0, 0, 0, 1, 0, 0}, "Cold reservoir temperature", false},
            {"\\eta", {0, 0, 0, 0, 0, 0, 0}, "Efficiency", false}
        },
        "Thermodynamics",
        "Carnot Efficiency",
        "T_h"
    });
}

} // namespace Physics
