#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_rotational_mechanics() {
    
    // ========================================================================
    // TORQUE: tau = r * F
    // ========================================================================
    
    formulas.push_back({
        "Torque (solve for tau)",
        "\\tau = rF",
        {
            {"\\tau", {2, -2, 1, 0, 0, 0, 0}, "Torque", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false}
        },
        "Rotational Mechanics",
        "Torque",
        "\\tau"
    });
    
    formulas.push_back({
        "Torque (solve for r)",
        "r = \\frac{\\tau}{F}",
        {
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false},
            {"\\tau", {2, -2, 1, 0, 0, 0, 0}, "Torque", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false}
        },
        "Rotational Mechanics",
        "Torque",
        "r"
    });
    
    formulas.push_back({
        "Torque (solve for F)",
        "F = \\frac{\\tau}{r}",
        {
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"\\tau", {2, -2, 1, 0, 0, 0, 0}, "Torque", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false}
        },
        "Rotational Mechanics",
        "Torque",
        "F"
    });
    
    // ========================================================================
    // ROTATIONAL NEWTON'S SECOND: tau = I * alpha
    // ========================================================================
    
    formulas.push_back({
        "Rotational Second Law (solve for tau)",
        "\\tau = I\\alpha",
        {
            {"\\tau", {2, -2, 1, 0, 0, 0, 0}, "Torque", false},
            {"I", {2, 0, 1, 0, 0, 0, 0}, "Moment of inertia", false},
            {"\\alpha", {0, -2, 0, 0, 0, 0, 0}, "Angular acceleration", false}
        },
        "Rotational Mechanics",
        "Rotational Second Law",
        "\\tau"
    });
    
    formulas.push_back({
        "Rotational Second Law (solve for I)",
        "I = \\frac{\\tau}{\\alpha}",
        {
            {"I", {2, 0, 1, 0, 0, 0, 0}, "Moment of inertia", false},
            {"\\tau", {2, -2, 1, 0, 0, 0, 0}, "Torque", false},
            {"\\alpha", {0, -2, 0, 0, 0, 0, 0}, "Angular acceleration", false}
        },
        "Rotational Mechanics",
        "Rotational Second Law",
        "I"
    });
    
    formulas.push_back({
        "Rotational Second Law (solve for alpha)",
        "\\alpha = \\frac{\\tau}{I}",
        {
            {"\\alpha", {0, -2, 0, 0, 0, 0, 0}, "Angular acceleration", false},
            {"\\tau", {2, -2, 1, 0, 0, 0, 0}, "Torque", false},
            {"I", {2, 0, 1, 0, 0, 0, 0}, "Moment of inertia", false}
        },
        "Rotational Mechanics",
        "Rotational Second Law",
        "\\alpha"
    });
    
    // ========================================================================
    // ROTATIONAL KINETIC ENERGY: KE_rot = (1/2) * I * omega^2
    // ========================================================================
    
    formulas.push_back({
        "Rotational Kinetic Energy (solve for KE)",
        "KE = \\frac{1}{2}I\\omega^2",
        {
            {"KE", {2, -2, 1, 0, 0, 0, 0}, "Kinetic energy", false},
            {"I", {2, 0, 1, 0, 0, 0, 0}, "Moment of inertia", false},
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular velocity", false}
        },
        "Rotational Mechanics",
        "Rotational Kinetic Energy",
        "KE"
    });
    
    formulas.push_back({
        "Rotational Kinetic Energy (solve for I)",
        "I = \\frac{2KE}{\\omega^2}",
        {
            {"I", {2, 0, 1, 0, 0, 0, 0}, "Moment of inertia", false},
            {"KE", {2, -2, 1, 0, 0, 0, 0}, "Kinetic energy", false},
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular velocity", false}
        },
        "Rotational Mechanics",
        "Rotational Kinetic Energy",
        "I"
    });
    
    formulas.push_back({
        "Rotational Kinetic Energy (solve for omega)",
        "\\omega = \\sqrt{\\frac{2KE}{I}}",
        {
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular velocity", false},
            {"KE", {2, -2, 1, 0, 0, 0, 0}, "Kinetic energy", false},
            {"I", {2, 0, 1, 0, 0, 0, 0}, "Moment of inertia", false}
        },
        "Rotational Mechanics",
        "Rotational Kinetic Energy",
        "\\omega"
    });
    
    // ========================================================================
    // ANGULAR MOMENTUM: L = I * omega
    // ========================================================================
    
    formulas.push_back({
        "Angular Momentum (solve for L)",
        "L = I\\omega",
        {
            {"L", {2, -1, 1, 0, 0, 0, 0}, "Angular momentum", false},
            {"I", {2, 0, 1, 0, 0, 0, 0}, "Moment of inertia", false},
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular velocity", false}
        },
        "Rotational Mechanics",
        "Angular Momentum",
        "L"
    });
    
    formulas.push_back({
        "Angular Momentum (solve for I)",
        "I = \\frac{L}{\\omega}",
        {
            {"I", {2, 0, 1, 0, 0, 0, 0}, "Moment of inertia", false},
            {"L", {2, -1, 1, 0, 0, 0, 0}, "Angular momentum", false},
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular velocity", false}
        },
        "Rotational Mechanics",
        "Angular Momentum",
        "I"
    });
    
    formulas.push_back({
        "Angular Momentum (solve for omega)",
        "\\omega = \\frac{L}{I}",
        {
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular velocity", false},
            {"L", {2, -1, 1, 0, 0, 0, 0}, "Angular momentum", false},
            {"I", {2, 0, 1, 0, 0, 0, 0}, "Moment of inertia", false}
        },
        "Rotational Mechanics",
        "Angular Momentum",
        "\\omega"
    });
    
    // ========================================================================
    // LINEAR-ANGULAR VELOCITY: v = r * omega
    // ========================================================================
    
    formulas.push_back({
        "Linear-Angular Velocity (solve for v)",
        "v = r\\omega",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Linear velocity", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false},
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular velocity", false}
        },
        "Rotational Mechanics",
        "Linear-Angular Velocity",
        "v"
    });
    
    formulas.push_back({
        "Linear-Angular Velocity (solve for r)",
        "r = \\frac{v}{\\omega}",
        {
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Linear velocity", false},
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular velocity", false}
        },
        "Rotational Mechanics",
        "Linear-Angular Velocity",
        "r"
    });
    
    formulas.push_back({
        "Linear-Angular Velocity (solve for omega)",
        "\\omega = \\frac{v}{r}",
        {
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular velocity", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Linear velocity", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false}
        },
        "Rotational Mechanics",
        "Linear-Angular Velocity",
        "\\omega"
    });
    
    // ========================================================================
    // MOMENT OF INERTIA POINT MASS: I = m * r^2
    // ========================================================================
    
    formulas.push_back({
        "Moment of Inertia Point Mass (solve for I)",
        "I = mr^2",
        {
            {"I", {2, 0, 1, 0, 0, 0, 0}, "Moment of inertia", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false}
        },
        "Rotational Mechanics",
        "Moment of Inertia Point Mass",
        "I"
    });
    
    formulas.push_back({
        "Moment of Inertia Point Mass (solve for m)",
        "m = \\frac{I}{r^2}",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"I", {2, 0, 1, 0, 0, 0, 0}, "Moment of inertia", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false}
        },
        "Rotational Mechanics",
        "Moment of Inertia Point Mass",
        "m"
    });
    
    formulas.push_back({
        "Moment of Inertia Point Mass (solve for r)",
        "r = \\sqrt{\\frac{I}{m}}",
        {
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false},
            {"I", {2, 0, 1, 0, 0, 0, 0}, "Moment of inertia", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false}
        },
        "Rotational Mechanics",
        "Moment of Inertia Point Mass",
        "r"
    });
}

} // namespace Physics
