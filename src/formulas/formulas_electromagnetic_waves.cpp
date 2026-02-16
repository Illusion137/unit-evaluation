#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_electromagnetic_waves() {
    
    // ========================================================================
    // SPEED OF LIGHT: c = f * lambda
    // ========================================================================
    
    formulas.push_back({
        "Speed of Light (solve for c)",
        "c = f\\lambda",
        {
            {"c", {1, -1, 0, 0, 0, 0, 0}, "Speed of light", true},
            {"f", {0, -1, 0, 0, 0, 0, 0}, "Frequency", false},
            {"\\lambda", {1, 0, 0, 0, 0, 0, 0}, "Wavelength", false}
        },
        "Electromagnetic Waves",
        "Speed of Light",
        "c"
    });
    
    formulas.push_back({
        "Speed of Light (solve for f)",
        "f = \\frac{c}{\\lambda}",
        {
            {"f", {0, -1, 0, 0, 0, 0, 0}, "Frequency", false},
            {"c", {1, -1, 0, 0, 0, 0, 0}, "Speed of light", true},
            {"\\lambda", {1, 0, 0, 0, 0, 0, 0}, "Wavelength", false}
        },
        "Electromagnetic Waves",
        "Speed of Light",
        "f"
    });
    
    formulas.push_back({
        "Speed of Light (solve for lambda)",
        "\\lambda = \\frac{c}{f}",
        {
            {"\\lambda", {1, 0, 0, 0, 0, 0, 0}, "Wavelength", false},
            {"c", {1, -1, 0, 0, 0, 0, 0}, "Speed of light", true},
            {"f", {0, -1, 0, 0, 0, 0, 0}, "Frequency", false}
        },
        "Electromagnetic Waves",
        "Speed of Light",
        "\\lambda"
    });
    
    // ========================================================================
    // ELECTROMAGNETIC WAVE SPEED IN MEDIUM: v = c / n
    // ========================================================================
    
    formulas.push_back({
        "EM Wave Speed in Medium (solve for v)",
        "v = \\frac{c}{n}",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Wave speed in medium", false},
            {"c", {1, -1, 0, 0, 0, 0, 0}, "Speed of light in vacuum", true},
            {"n", {0, 0, 0, 0, 0, 0, 0}, "Index of refraction", false}
        },
        "Electromagnetic Waves",
        "EM Wave Speed in Medium",
        "v"
    });
    
    formulas.push_back({
        "EM Wave Speed in Medium (solve for n)",
        "n = \\frac{c}{v}",
        {
            {"n", {0, 0, 0, 0, 0, 0, 0}, "Index of refraction", false},
            {"c", {1, -1, 0, 0, 0, 0, 0}, "Speed of light in vacuum", true},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Wave speed in medium", false}
        },
        "Electromagnetic Waves",
        "EM Wave Speed in Medium",
        "n"
    });
}

} // namespace Physics
