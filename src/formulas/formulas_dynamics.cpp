#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_dynamics() {
    
    // ========================================================================
    // NEWTON'S SECOND LAW: F = m * a
    // ========================================================================
    
    formulas.push_back({
        "Newton's Second Law (solve for F)",
        "F = ma",
        {
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"a", {1, -2, 0, 0, 0, 0, 0}, "Acceleration", false}
        },
        "Dynamics",
        "Newton's Second Law",
        "F"
    });
    
    formulas.push_back({
        "Newton's Second Law (solve for m)",
        "m = \\frac{F}{a}",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"a", {1, -2, 0, 0, 0, 0, 0}, "Acceleration", false}
        },
        "Dynamics",
        "Newton's Second Law",
        "m"
    });
    
    formulas.push_back({
        "Newton's Second Law (solve for a)",
        "a = \\frac{F}{m}",
        {
            {"a", {1, -2, 0, 0, 0, 0, 0}, "Acceleration", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false}
        },
        "Dynamics",
        "Newton's Second Law",
        "a"
    });
    
    // ========================================================================
    // WEIGHT: W = m * g
    // ========================================================================
    
    formulas.push_back({
        "Weight (solve for W)",
        "W = mg",
        {
            {"W", {1, -2, 1, 0, 0, 0, 0}, "Weight", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"g", {1, -2, 0, 0, 0, 0, 0}, "Gravitational acceleration", true}
        },
        "Dynamics",
        "Weight",
        "W"
    });
    
    formulas.push_back({
        "Weight (solve for m)",
        "m = \\frac{W}{g}",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"W", {1, -2, 1, 0, 0, 0, 0}, "Weight", false},
            {"g", {1, -2, 0, 0, 0, 0, 0}, "Gravitational acceleration", true}
        },
        "Dynamics",
        "Weight",
        "m"
    });
    
    // ========================================================================
    // FRICTION FORCE: F_f = mu * N
    // ========================================================================
    
    formulas.push_back({
        "Friction Force (solve for F_f)",
        "F_f = \\mu N",
        {
            {"F_f", {1, -2, 1, 0, 0, 0, 0}, "Friction force", false},
            {"\\mu", {0, 0, 0, 0, 0, 0, 0}, "Coefficient of friction", false},
            {"N", {1, -2, 1, 0, 0, 0, 0}, "Normal force", false}
        },
        "Dynamics",
        "Friction Force",
        "F_f"
    });
    
    formulas.push_back({
        "Friction Force (solve for mu)",
        "\\mu = \\frac{F_f}{N}",
        {
            {"\\mu", {0, 0, 0, 0, 0, 0, 0}, "Coefficient of friction", false},
            {"F_f", {1, -2, 1, 0, 0, 0, 0}, "Friction force", false},
            {"N", {1, -2, 1, 0, 0, 0, 0}, "Normal force", false}
        },
        "Dynamics",
        "Friction Force",
        "\\mu"
    });
    
    formulas.push_back({
        "Friction Force (solve for N)",
        "N = \\frac{F_f}{\\mu}",
        {
            {"N", {1, -2, 1, 0, 0, 0, 0}, "Normal force", false},
            {"F_f", {1, -2, 1, 0, 0, 0, 0}, "Friction force", false},
            {"\\mu", {0, 0, 0, 0, 0, 0, 0}, "Coefficient of friction", false}
        },
        "Dynamics",
        "Friction Force",
        "N"
    });
    
    // ========================================================================
    // HOOKE'S LAW: F = k * x
    // ========================================================================
    
    formulas.push_back({
        "Hooke's Law (solve for F)",
        "F = kx",
        {
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Spring force", false},
            {"k", {0, -2, 1, 0, 0, 0, 0}, "Spring constant", false},
            {"x", {1, 0, 0, 0, 0, 0, 0}, "Displacement", false}
        },
        "Dynamics",
        "Hooke's Law",
        "F"
    });
    
    formulas.push_back({
        "Hooke's Law (solve for k)",
        "k = \\frac{F}{x}",
        {
            {"k", {0, -2, 1, 0, 0, 0, 0}, "Spring constant", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Spring force", false},
            {"x", {1, 0, 0, 0, 0, 0, 0}, "Displacement", false}
        },
        "Dynamics",
        "Hooke's Law",
        "k"
    });
    
    formulas.push_back({
        "Hooke's Law (solve for x)",
        "x = \\frac{F}{k}",
        {
            {"x", {1, 0, 0, 0, 0, 0, 0}, "Displacement", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Spring force", false},
            {"k", {0, -2, 1, 0, 0, 0, 0}, "Spring constant", false}
        },
        "Dynamics",
        "Hooke's Law",
        "x"
    });
    
    // ========================================================================
    // WORK: W = F * d * cos(theta) (for theta = 0: W = F * d)
    // ========================================================================
    
    formulas.push_back({
        "Work (solve for W)",
        "W = Fd",
        {
            {"W", {2, -2, 1, 0, 0, 0, 0}, "Work", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"d", {1, 0, 0, 0, 0, 0, 0}, "Displacement", false}
        },
        "Dynamics",
        "Work",
        "W"
    });
    
    formulas.push_back({
        "Work (solve for F)",
        "F = \\frac{W}{d}",
        {
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"W", {2, -2, 1, 0, 0, 0, 0}, "Work", false},
            {"d", {1, 0, 0, 0, 0, 0, 0}, "Displacement", false}
        },
        "Dynamics",
        "Work",
        "F"
    });
    
    formulas.push_back({
        "Work (solve for d)",
        "d = \\frac{W}{F}",
        {
            {"d", {1, 0, 0, 0, 0, 0, 0}, "Displacement", false},
            {"W", {2, -2, 1, 0, 0, 0, 0}, "Work", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false}
        },
        "Dynamics",
        "Work",
        "d"
    });
    
    // ========================================================================
    // CENTRIPETAL FORCE: F_c = m * v^2 / r
    // ========================================================================
    
    formulas.push_back({
        "Centripetal Force (solve for F_c)",
        "F_c = \\frac{mv^2}{r}",
        {
            {"F_c", {1, -2, 1, 0, 0, 0, 0}, "Centripetal force", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false}
        },
        "Dynamics",
        "Centripetal Force",
        "F_c"
    });
    
    formulas.push_back({
        "Centripetal Force (solve for m)",
        "m = \\frac{F_c r}{v^2}",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"F_c", {1, -2, 1, 0, 0, 0, 0}, "Centripetal force", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false}
        },
        "Dynamics",
        "Centripetal Force",
        "m"
    });
    
    formulas.push_back({
        "Centripetal Force (solve for v)",
        "v = \\sqrt{\\frac{F_c r}{m}}",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"F_c", {1, -2, 1, 0, 0, 0, 0}, "Centripetal force", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false}
        },
        "Dynamics",
        "Centripetal Force",
        "v"
    });
    
    formulas.push_back({
        "Centripetal Force (solve for r)",
        "r = \\frac{mv^2}{F_c}",
        {
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"F_c", {1, -2, 1, 0, 0, 0, 0}, "Centripetal force", false}
        },
        "Dynamics",
        "Centripetal Force",
        "r"
    });
    
    // ========================================================================
    // CENTRIPETAL ACCELERATION: a_c = v^2 / r
    // ========================================================================
    
    formulas.push_back({
        "Centripetal Acceleration (solve for a_c)",
        "a_c = \\frac{v^2}{r}",
        {
            {"a_c", {1, -2, 0, 0, 0, 0, 0}, "Centripetal acceleration", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false}
        },
        "Dynamics",
        "Centripetal Acceleration",
        "a_c"
    });
    
    formulas.push_back({
        "Centripetal Acceleration (solve for v)",
        "v = \\sqrt{a_c r}",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"a_c", {1, -2, 0, 0, 0, 0, 0}, "Centripetal acceleration", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false}
        },
        "Dynamics",
        "Centripetal Acceleration",
        "v"
    });
    
    formulas.push_back({
        "Centripetal Acceleration (solve for r)",
        "r = \\frac{v^2}{a_c}",
        {
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"a_c", {1, -2, 0, 0, 0, 0, 0}, "Centripetal acceleration", false}
        },
        "Dynamics",
        "Centripetal Acceleration",
        "r"
    });
    
    // ========================================================================
    // CENTRIPETAL FORCE (ANGULAR): F_c = m * omega^2 * r
    // ========================================================================
    
    formulas.push_back({
        "Centripetal Force Angular (solve for F_c)",
        "F_c = m\\omega^2 r",
        {
            {"F_c", {1, -2, 1, 0, 0, 0, 0}, "Centripetal force", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular velocity", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false}
        },
        "Dynamics",
        "Centripetal Force Angular",
        "F_c"
    });
    
    formulas.push_back({
        "Centripetal Force Angular (solve for m)",
        "m = \\frac{F_c}{\\omega^2 r}",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"F_c", {1, -2, 1, 0, 0, 0, 0}, "Centripetal force", false},
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular velocity", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false}
        },
        "Dynamics",
        "Centripetal Force Angular",
        "m"
    });
    
    formulas.push_back({
        "Centripetal Force Angular (solve for omega)",
        "\\omega = \\sqrt{\\frac{F_c}{mr}}",
        {
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular velocity", false},
            {"F_c", {1, -2, 1, 0, 0, 0, 0}, "Centripetal force", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false}
        },
        "Dynamics",
        "Centripetal Force Angular",
        "\\omega"
    });
    
    formulas.push_back({
        "Centripetal Force Angular (solve for r)",
        "r = \\frac{F_c}{m\\omega^2}",
        {
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false},
            {"F_c", {1, -2, 1, 0, 0, 0, 0}, "Centripetal force", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"\\omega", {0, -1, 0, 0, 0, 0, 0}, "Angular velocity", false}
        },
        "Dynamics",
        "Centripetal Force Angular",
        "r"
    });
    
    // ========================================================================
    // IMPULSE: J = F * Delta_t
    // ========================================================================
    
    formulas.push_back({
        "Impulse (solve for J)",
        "J = F\\Delta t",
        {
            {"J", {1, -1, 1, 0, 0, 0, 0}, "Impulse", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"\\Delta t", {0, 1, 0, 0, 0, 0, 0}, "Time interval", false}
        },
        "Dynamics",
        "Impulse",
        "J"
    });
    
    formulas.push_back({
        "Impulse (solve for F)",
        "F = \\frac{J}{\\Delta t}",
        {
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"J", {1, -1, 1, 0, 0, 0, 0}, "Impulse", false},
            {"\\Delta t", {0, 1, 0, 0, 0, 0, 0}, "Time interval", false}
        },
        "Dynamics",
        "Impulse",
        "F"
    });
    
    formulas.push_back({
        "Impulse (solve for Delta_t)",
        "\\Delta t = \\frac{J}{F}",
        {
            {"\\Delta t", {0, 1, 0, 0, 0, 0, 0}, "Time interval", false},
            {"J", {1, -1, 1, 0, 0, 0, 0}, "Impulse", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false}
        },
        "Dynamics",
        "Impulse",
        "\\Delta t"
    });
}

} // namespace Physics
