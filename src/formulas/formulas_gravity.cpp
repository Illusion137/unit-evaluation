#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_gravity() {
    
    // ========================================================================
    // NEWTON'S LAW OF UNIVERSAL GRAVITATION: F = G * m1 * m2 / r^2
    // ========================================================================
    
    formulas.push_back({
        "Universal Gravitation (solve for F)",
        "F = G\\frac{m_1 m_2}{r^2}",
        {
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Gravitational force", false},
            {"G", {3, -2, -1, 0, 0, 0, 0}, "Gravitational constant", true},
            {"m_1", {0, 0, 1, 0, 0, 0, 0}, "Mass 1", false},
            {"m_2", {0, 0, 1, 0, 0, 0, 0}, "Mass 2", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false}
        },
        "Gravity",
        "Universal Gravitation",
        "F"
    });
    
    formulas.push_back({
        "Universal Gravitation (solve for m_1)",
        "m_1 = \\frac{Fr^2}{Gm_2}",
        {
            {"m_1", {0, 0, 1, 0, 0, 0, 0}, "Mass 1", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Gravitational force", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false},
            {"G", {3, -2, -1, 0, 0, 0, 0}, "Gravitational constant", true},
            {"m_2", {0, 0, 1, 0, 0, 0, 0}, "Mass 2", false}
        },
        "Gravity",
        "Universal Gravitation",
        "m_1"
    });
    
    formulas.push_back({
        "Universal Gravitation (solve for r)",
        "r = \\sqrt{\\frac{Gm_1 m_2}{F}}",
        {
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false},
            {"G", {3, -2, -1, 0, 0, 0, 0}, "Gravitational constant", true},
            {"m_1", {0, 0, 1, 0, 0, 0, 0}, "Mass 1", false},
            {"m_2", {0, 0, 1, 0, 0, 0, 0}, "Mass 2", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Gravitational force", false}
        },
        "Gravity",
        "Universal Gravitation",
        "r"
    });
    
    // ========================================================================
    // GRAVITATIONAL POTENTIAL ENERGY: U = -G * m1 * m2 / r
    // ========================================================================
    
    formulas.push_back({
        "Gravitational Potential Energy (solve for U)",
        "U = -G\\frac{m_1 m_2}{r}",
        {
            {"U", {2, -2, 1, 0, 0, 0, 0}, "Potential energy", false},
            {"G", {3, -2, -1, 0, 0, 0, 0}, "Gravitational constant", true},
            {"m_1", {0, 0, 1, 0, 0, 0, 0}, "Mass 1", false},
            {"m_2", {0, 0, 1, 0, 0, 0, 0}, "Mass 2", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false}
        },
        "Gravity",
        "Gravitational Potential Energy",
        "U"
    });
    
    formulas.push_back({
        "Gravitational Potential Energy (solve for r)",
        "r = -G\\frac{m_1 m_2}{U}",
        {
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false},
            {"G", {3, -2, -1, 0, 0, 0, 0}, "Gravitational constant", true},
            {"m_1", {0, 0, 1, 0, 0, 0, 0}, "Mass 1", false},
            {"m_2", {0, 0, 1, 0, 0, 0, 0}, "Mass 2", false},
            {"U", {2, -2, 1, 0, 0, 0, 0}, "Potential energy", false}
        },
        "Gravity",
        "Gravitational Potential Energy",
        "r"
    });
    
    // ========================================================================
    // ORBITAL VELOCITY: v = sqrt(G * M / r)
    // ========================================================================
    
    formulas.push_back({
        "Orbital Velocity (solve for v)",
        "v = \\sqrt{\\frac{GM}{r}}",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Orbital velocity", false},
            {"G", {3, -2, -1, 0, 0, 0, 0}, "Gravitational constant", true},
            {"M", {0, 0, 1, 0, 0, 0, 0}, "Central mass", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Orbital radius", false}
        },
        "Gravity",
        "Orbital Velocity",
        "v"
    });
    
    formulas.push_back({
        "Orbital Velocity (solve for M)",
        "M = \\frac{v^2 r}{G}",
        {
            {"M", {0, 0, 1, 0, 0, 0, 0}, "Central mass", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Orbital velocity", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Orbital radius", false},
            {"G", {3, -2, -1, 0, 0, 0, 0}, "Gravitational constant", true}
        },
        "Gravity",
        "Orbital Velocity",
        "M"
    });
    
    formulas.push_back({
        "Orbital Velocity (solve for r)",
        "r = \\frac{GM}{v^2}",
        {
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Orbital radius", false},
            {"G", {3, -2, -1, 0, 0, 0, 0}, "Gravitational constant", true},
            {"M", {0, 0, 1, 0, 0, 0, 0}, "Central mass", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Orbital velocity", false}
        },
        "Gravity",
        "Orbital Velocity",
        "r"
    });
    
    // ========================================================================
    // ESCAPE VELOCITY: v_esc = sqrt(2 * G * M / r)
    // ========================================================================
    
    formulas.push_back({
        "Escape Velocity (solve for v_esc)",
        "v_{esc} = \\sqrt{\\frac{2GM}{r}}",
        {
            {"v_{esc}", {1, -1, 0, 0, 0, 0, 0}, "Escape velocity", false},
            {"G", {3, -2, -1, 0, 0, 0, 0}, "Gravitational constant", true},
            {"M", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false}
        },
        "Gravity",
        "Escape Velocity",
        "v_{esc}"
    });
    
    formulas.push_back({
        "Escape Velocity (solve for M)",
        "M = \\frac{v_{esc}^2 r}{2G}",
        {
            {"M", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"v_{esc}", {1, -1, 0, 0, 0, 0, 0}, "Escape velocity", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false},
            {"G", {3, -2, -1, 0, 0, 0, 0}, "Gravitational constant", true}
        },
        "Gravity",
        "Escape Velocity",
        "M"
    });
    
    formulas.push_back({
        "Escape Velocity (solve for r)",
        "r = \\frac{2GM}{v_{esc}^2}",
        {
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false},
            {"G", {3, -2, -1, 0, 0, 0, 0}, "Gravitational constant", true},
            {"M", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"v_{esc}", {1, -1, 0, 0, 0, 0, 0}, "Escape velocity", false}
        },
        "Gravity",
        "Escape Velocity",
        "r"
    });
}

} // namespace Physics
