#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_circular_motion() {
    
    // Already covered in Dynamics (centripetal force/acceleration)
    // Adding additional circular motion formulas
    
    // ========================================================================
    // ANGULAR DISPLACEMENT: theta = omega * t
    // ========================================================================
    
    formulas.push_back({
        "Angular Displacement (solve for theta)",
        "\\theta = \\omega t",
        {
            {"\\theta", {0, 0, 0, 0, 0, 0, 0}, "Angular displacement", false},
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular velocity", false},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false}
        },
        "Circular Motion",
        "Angular Displacement",
        "\\theta"
    });
    
    formulas.push_back({
        "Angular Displacement (solve for omega)",
        "\\omega = \\frac{\\theta}{t}",
        {
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular velocity", false},
            {"\\theta", {0, 0, 0, 0, 0, 0, 0}, "Angular displacement", false},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false}
        },
        "Circular Motion",
        "Angular Displacement",
        "\\omega"
    });
    
    formulas.push_back({
        "Angular Displacement (solve for t)",
        "t = \\frac{\\theta}{\\omega}",
        {
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false},
            {"\\theta", {0, 0, 0, 0, 0, 0, 0}, "Angular displacement", false},
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular velocity", false}
        },
        "Circular Motion",
        "Angular Displacement",
        "t"
    });
    
    // ========================================================================
    // PERIOD AND ANGULAR VELOCITY: T = 2*pi / omega
    // ========================================================================
    
    formulas.push_back({
        "Period from Angular Velocity (solve for T)",
        "T = \\frac{2\\pi}{\\omega}",
        {
            {"T", {0, 1, 0, 0, 0, 0, 0}, "Period", false},
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular velocity", false}
        },
        "Circular Motion",
        "Period from Angular Velocity",
        "T"
    });
    
    formulas.push_back({
        "Period from Angular Velocity (solve for omega)",
        "\\omega = \\frac{2\\pi}{T}",
        {
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular velocity", false},
            {"T", {0, 1, 0, 0, 0, 0, 0}, "Period", false}
        },
        "Circular Motion",
        "Period from Angular Velocity",
        "\\omega"
    });
}

} // namespace Physics
