#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_modern_physics() {
    
    // ========================================================================
    // PHOTOELECTRIC EFFECT: KE_max = h * f - phi
    // ========================================================================
    
    formulas.push_back({
        "Photoelectric Effect (solve for KE_max)",
        "KE_{max} = hf - \\phi",
        {
            {"KE_{max}", {2, -2, 1, 0, 0, 0, 0}, "Maximum kinetic energy", false},
            {"h", {2, -1, 1, 0, 0, 0, 0}, "Planck's constant", true},
            {"f", {0, -1, 0, 0, 0, 0, 0}, "Frequency", false},
            {"\\phi", {2, -2, 1, 0, 0, 0, 0}, "Work function", false}
        },
        "Modern Physics",
        "Photoelectric Effect",
        "KE_{max}"
    });
    
    formulas.push_back({
        "Photoelectric Effect (solve for f)",
        "f = \\frac{KE_{max} + \\phi}{h}",
        {
            {"f", {0, -1, 0, 0, 0, 0, 0}, "Frequency", false},
            {"KE_{max}", {2, -2, 1, 0, 0, 0, 0}, "Maximum kinetic energy", false},
            {"\\phi", {2, -2, 1, 0, 0, 0, 0}, "Work function", false},
            {"h", {2, -1, 1, 0, 0, 0, 0}, "Planck's constant", true}
        },
        "Modern Physics",
        "Photoelectric Effect",
        "f"
    });
    
    formulas.push_back({
        "Photoelectric Effect (solve for phi)",
        "\\phi = hf - KE_{max}",
        {
            {"\\phi", {2, -2, 1, 0, 0, 0, 0}, "Work function", false},
            {"h", {2, -1, 1, 0, 0, 0, 0}, "Planck's constant", true},
            {"f", {0, -1, 0, 0, 0, 0, 0}, "Frequency", false},
            {"KE_{max}", {2, -2, 1, 0, 0, 0, 0}, "Maximum kinetic energy", false}
        },
        "Modern Physics",
        "Photoelectric Effect",
        "\\phi"
    });
    
    // ========================================================================
    // PHOTON ENERGY: E = h * f
    // ========================================================================
    
    formulas.push_back({
        "Photon Energy (solve for E)",
        "E = hf",
        {
            {"E", {2, -2, 1, 0, 0, 0, 0}, "Energy", false},
            {"h", {2, -1, 1, 0, 0, 0, 0}, "Planck's constant", true},
            {"f", {0, -1, 0, 0, 0, 0, 0}, "Frequency", false}
        },
        "Modern Physics",
        "Photon Energy",
        "E"
    });
    
    formulas.push_back({
        "Photon Energy (solve for f)",
        "f = \\frac{E}{h}",
        {
            {"f", {0, -1, 0, 0, 0, 0, 0}, "Frequency", false},
            {"E", {2, -2, 1, 0, 0, 0, 0}, "Energy", false},
            {"h", {2, -1, 1, 0, 0, 0, 0}, "Planck's constant", true}
        },
        "Modern Physics",
        "Photon Energy",
        "f"
    });
    
    // ========================================================================
    // DE BROGLIE WAVELENGTH: lambda = h / p
    // ========================================================================
    
    formulas.push_back({
        "de Broglie Wavelength (solve for lambda)",
        "\\lambda = \\frac{h}{p}",
        {
            {"\\lambda", {1, 0, 0, 0, 0, 0, 0}, "Wavelength", false},
            {"h", {2, -1, 1, 0, 0, 0, 0}, "Planck's constant", true},
            {"p", {1, -1, 1, 0, 0, 0, 0}, "Momentum", false}
        },
        "Modern Physics",
        "de Broglie Wavelength",
        "\\lambda"
    });
    
    formulas.push_back({
        "de Broglie Wavelength (solve for p)",
        "p = \\frac{h}{\\lambda}",
        {
            {"p", {1, -1, 1, 0, 0, 0, 0}, "Momentum", false},
            {"h", {2, -1, 1, 0, 0, 0, 0}, "Planck's constant", true},
            {"\\lambda", {1, 0, 0, 0, 0, 0, 0}, "Wavelength", false}
        },
        "Modern Physics",
        "de Broglie Wavelength",
        "p"
    });
    
    // ========================================================================
    // MASS-ENERGY EQUIVALENCE: E = m * c^2
    // ========================================================================
    
    formulas.push_back({
        "Mass-Energy Equivalence (solve for E)",
        "E = mc^2",
        {
            {"E", {2, -2, 1, 0, 0, 0, 0}, "Energy", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"c", {1, -1, 0, 0, 0, 0, 0}, "Speed of light", true}
        },
        "Modern Physics",
        "Mass-Energy Equivalence",
        "E"
    });
    
    formulas.push_back({
        "Mass-Energy Equivalence (solve for m)",
        "m = \\frac{E}{c^2}",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"E", {2, -2, 1, 0, 0, 0, 0}, "Energy", false},
            {"c", {1, -1, 0, 0, 0, 0, 0}, "Speed of light", true}
        },
        "Modern Physics",
        "Mass-Energy Equivalence",
        "m"
    });
}

} // namespace Physics
