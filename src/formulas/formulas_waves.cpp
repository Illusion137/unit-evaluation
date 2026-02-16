#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_waves() {
    
    // ========================================================================
    // WAVE VELOCITY: v = f * lambda
    // ========================================================================
    
    formulas.push_back({
        "Wave Velocity (solve for v)",
        "v = f\\lambda",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Wave velocity", false},
            {"f", {0, -1, 0, 0, 0, 0, 0}, "Frequency", false},
            {"\\lambda", {1, 0, 0, 0, 0, 0, 0}, "Wavelength", false}
        },
        "Waves",
        "Wave Velocity",
        "v"
    });
    
    formulas.push_back({
        "Wave Velocity (solve for f)",
        "f = \\frac{v}{\\lambda}",
        {
            {"f", {0, -1, 0, 0, 0, 0, 0}, "Frequency", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Wave velocity", false},
            {"\\lambda", {1, 0, 0, 0, 0, 0, 0}, "Wavelength", false}
        },
        "Waves",
        "Wave Velocity",
        "f"
    });
    
    formulas.push_back({
        "Wave Velocity (solve for lambda)",
        "\\lambda = \\frac{v}{f}",
        {
            {"\\lambda", {1, 0, 0, 0, 0, 0, 0}, "Wavelength", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Wave velocity", false},
            {"f", {0, -1, 0, 0, 0, 0, 0}, "Frequency", false}
        },
        "Waves",
        "Wave Velocity",
        "\\lambda"
    });
    
    // ========================================================================
    // WAVE SPEED ON STRING: v = sqrt(T/mu)
    // ========================================================================
    
    formulas.push_back({
        "Wave Speed on String (solve for v)",
        "v = \\sqrt{\\frac{T}{\\mu}}",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Wave velocity", false},
            {"T", {1, -2, 1, 0, 0, 0, 0}, "Tension", false},
            {"\\mu", {-1, 0, 1, 0, 0, 0, 0}, "Linear mass density", false}
        },
        "Waves",
        "Wave Speed on String",
        "v"
    });
    
    formulas.push_back({
        "Wave Speed on String (solve for T)",
        "T = \\mu v^2",
        {
            {"T", {1, -2, 1, 0, 0, 0, 0}, "Tension", false},
            {"\\mu", {-1, 0, 1, 0, 0, 0, 0}, "Linear mass density", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Wave velocity", false}
        },
        "Waves",
        "Wave Speed on String",
        "T"
    });
    
    formulas.push_back({
        "Wave Speed on String (solve for mu)",
        "\\mu = \\frac{T}{v^2}",
        {
            {"\\mu", {-1, 0, 1, 0, 0, 0, 0}, "Linear mass density", false},
            {"T", {1, -2, 1, 0, 0, 0, 0}, "Tension", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Wave velocity", false}
        },
        "Waves",
        "Wave Speed on String",
        "\\mu"
    });
    
    // ========================================================================
    // DOPPLER EFFECT (SOUND): f_obs = f_source * (v +/- v_obs) / (v -/+ v_source)
    // Simplified for stationary observer
    // ========================================================================
    
    formulas.push_back({
        "Doppler Effect Moving Source (solve for f_obs)",
        "f_{obs} = f_s \\frac{v}{v \\mp v_s}",
        {
            {"f_{obs}", {0, -1, 0, 0, 0, 0, 0}, "Observed frequency", false},
            {"f_s", {0, -1, 0, 0, 0, 0, 0}, "Source frequency", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Wave velocity", false},
            {"v_s", {1, -1, 0, 0, 0, 0, 0}, "Source velocity", false}
        },
        "Waves",
        "Doppler Effect Moving Source",
        "f_{obs}"
    });
}

} // namespace Physics
