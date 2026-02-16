#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_oscillations() {
    
    // ========================================================================
    // SIMPLE HARMONIC MOTION ANGULAR FREQUENCY: omega = sqrt(k/m)
    // ========================================================================
    
    formulas.push_back({
        "SHM Angular Frequency (solve for omega)",
        "\\omega = \\sqrt{\\frac{k}{m}}",
        {
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular frequency", false},
            {"k", {0, -2, 1, 0, 0, 0, 0}, "Spring constant", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false}
        },
        "Oscillations",
        "SHM Angular Frequency",
        "\\omega"
    });
    
    formulas.push_back({
        "SHM Angular Frequency (solve for k)",
        "k = m\\omega^2",
        {
            {"k", {0, -2, 1, 0, 0, 0, 0}, "Spring constant", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular frequency", false}
        },
        "Oscillations",
        "SHM Angular Frequency",
        "k"
    });
    
    formulas.push_back({
        "SHM Angular Frequency (solve for m)",
        "m = \\frac{k}{\\omega^2}",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"k", {0, -2, 1, 0, 0, 0, 0}, "Spring constant", false},
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular frequency", false}
        },
        "Oscillations",
        "SHM Angular Frequency",
        "m"
    });
    
    // ========================================================================
    // PERIOD OF MASS-SPRING: T = 2*pi*sqrt(m/k)
    // ========================================================================
    
    formulas.push_back({
        "Mass-Spring Period (solve for T)",
        "T = 2\\pi\\sqrt{\\frac{m}{k}}",
        {
            {"T", {0, 1, 0, 0, 0, 0, 0}, "Period", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"k", {0, -2, 1, 0, 0, 0, 0}, "Spring constant", false}
        },
        "Oscillations",
        "Mass-Spring Period",
        "T"
    });
    
    formulas.push_back({
        "Mass-Spring Period (solve for m)",
        "m = \\frac{kT^2}{4\\pi^2}",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"k", {0, -2, 1, 0, 0, 0, 0}, "Spring constant", false},
            {"T", {0, 1, 0, 0, 0, 0, 0}, "Period", false}
        },
        "Oscillations",
        "Mass-Spring Period",
        "m"
    });
    
    formulas.push_back({
        "Mass-Spring Period (solve for k)",
        "k = \\frac{4\\pi^2 m}{T^2}",
        {
            {"k", {0, -2, 1, 0, 0, 0, 0}, "Spring constant", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"T", {0, 1, 0, 0, 0, 0, 0}, "Period", false}
        },
        "Oscillations",
        "Mass-Spring Period",
        "k"
    });
    
    // ========================================================================
    // SIMPLE PENDULUM PERIOD: T = 2*pi*sqrt(L/g)
    // ========================================================================
    
    formulas.push_back({
        "Simple Pendulum Period (solve for T)",
        "T = 2\\pi\\sqrt{\\frac{L}{g}}",
        {
            {"T", {0, 1, 0, 0, 0, 0, 0}, "Period", false},
            {"L", {1, 0, 0, 0, 0, 0, 0}, "Length", false},
            {"g", {1, -2, 0, 0, 0, 0, 0}, "Gravitational acceleration", true}
        },
        "Oscillations",
        "Simple Pendulum Period",
        "T"
    });
    
    formulas.push_back({
        "Simple Pendulum Period (solve for L)",
        "L = \\frac{gT^2}{4\\pi^2}",
        {
            {"L", {1, 0, 0, 0, 0, 0, 0}, "Length", false},
            {"g", {1, -2, 0, 0, 0, 0, 0}, "Gravitational acceleration", true},
            {"T", {0, 1, 0, 0, 0, 0, 0}, "Period", false}
        },
        "Oscillations",
        "Simple Pendulum Period",
        "L"
    });
    
    // ========================================================================
    // FREQUENCY: f = 1/T
    // ========================================================================
    
    formulas.push_back({
        "Frequency (solve for f)",
        "f = \\frac{1}{T}",
        {
            {"f", {0, -1, 0, 0, 0, 0, 0}, "Frequency", false},
            {"T", {0, 1, 0, 0, 0, 0, 0}, "Period", false}
        },
        "Oscillations",
        "Frequency",
        "f"
    });
    
    formulas.push_back({
        "Frequency (solve for T)",
        "T = \\frac{1}{f}",
        {
            {"T", {0, 1, 0, 0, 0, 0, 0}, "Period", false},
            {"f", {0, -1, 0, 0, 0, 0, 0}, "Frequency", false}
        },
        "Oscillations",
        "Frequency",
        "T"
    });
    
    // ========================================================================
    // ANGULAR FREQUENCY: omega = 2*pi*f
    // ========================================================================
    
    formulas.push_back({
        "Angular Frequency (solve for omega)",
        "\\omega = 2\\pi f",
        {
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular frequency", false},
            {"f", {0, -1, 0, 0, 0, 0, 0}, "Frequency", false}
        },
        "Oscillations",
        "Angular Frequency",
        "\\omega"
    });
    
    formulas.push_back({
        "Angular Frequency (solve for f)",
        "f = \\frac{\\omega}{2\\pi}",
        {
            {"f", {0, -1, 0, 0, 0, 0, 0}, "Frequency", false},
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular frequency", false}
        },
        "Oscillations",
        "Angular Frequency",
        "f"
    });
}

} // namespace Physics
