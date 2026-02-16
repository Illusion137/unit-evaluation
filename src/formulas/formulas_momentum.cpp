#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_momentum() {
    
    // ========================================================================
    // MOMENTUM: p = m * v
    // ========================================================================
    
    formulas.push_back({
        "Momentum (solve for p)",
        "p = mv",
        {
            {"p", {1, -1, 1, 0, 0, 0, 0}, "Momentum", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false}
        },
        "Momentum",
        "Momentum",
        "p"
    });
    
    formulas.push_back({
        "Momentum (solve for m)",
        "m = \\frac{p}{v}",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"p", {1, -1, 1, 0, 0, 0, 0}, "Momentum", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false}
        },
        "Momentum",
        "Momentum",
        "m"
    });
    
    formulas.push_back({
        "Momentum (solve for v)",
        "v = \\frac{p}{m}",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"p", {1, -1, 1, 0, 0, 0, 0}, "Momentum", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false}
        },
        "Momentum",
        "Momentum",
        "v"
    });
    
    // ========================================================================
    // IMPULSE-MOMENTUM THEOREM: J = Delta_p
    // ========================================================================
    
    formulas.push_back({
        "Impulse-Momentum Theorem (solve for J)",
        "J = \\Delta p",
        {
            {"J", {1, -1, 1, 0, 0, 0, 0}, "Impulse", false},
            {"\\Delta p", {1, -1, 1, 0, 0, 0, 0}, "Change in momentum", false}
        },
        "Momentum",
        "Impulse-Momentum Theorem",
        "J"
    });
    
    formulas.push_back({
        "Impulse-Momentum Theorem (solve for Delta_p)",
        "\\Delta p = J",
        {
            {"\\Delta p", {1, -1, 1, 0, 0, 0, 0}, "Change in momentum", false},
            {"J", {1, -1, 1, 0, 0, 0, 0}, "Impulse", false}
        },
        "Momentum",
        "Impulse-Momentum Theorem",
        "\\Delta p"
    });
    
    // ========================================================================
    // CHANGE IN MOMENTUM: Delta_p = m * Delta_v
    // ========================================================================
    
    formulas.push_back({
        "Change in Momentum (solve for Delta_p)",
        "\\Delta p = m\\Delta v",
        {
            {"\\Delta p", {1, -1, 1, 0, 0, 0, 0}, "Change in momentum", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"\\Delta v", {1, -1, 0, 0, 0, 0, 0}, "Change in velocity", false}
        },
        "Momentum",
        "Change in Momentum",
        "\\Delta p"
    });
    
    formulas.push_back({
        "Change in Momentum (solve for m)",
        "m = \\frac{\\Delta p}{\\Delta v}",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"\\Delta p", {1, -1, 1, 0, 0, 0, 0}, "Change in momentum", false},
            {"\\Delta v", {1, -1, 0, 0, 0, 0, 0}, "Change in velocity", false}
        },
        "Momentum",
        "Change in Momentum",
        "m"
    });
    
    formulas.push_back({
        "Change in Momentum (solve for Delta_v)",
        "\\Delta v = \\frac{\\Delta p}{m}",
        {
            {"\\Delta v", {1, -1, 0, 0, 0, 0, 0}, "Change in velocity", false},
            {"\\Delta p", {1, -1, 1, 0, 0, 0, 0}, "Change in momentum", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false}
        },
        "Momentum",
        "Change in Momentum",
        "\\Delta v"
    });
    
    // ========================================================================
    // ELASTIC COLLISION (1D): v_1f = ((m_1-m_2)/(m_1+m_2)) * v_1i + ((2*m_2)/(m_1+m_2)) * v_2i
    // Conservation formulas only
    // ========================================================================
    
    formulas.push_back({
        "Conservation of Momentum (solve for total p_f)",
        "p_f = p_i",
        {
            {"p_f", {1, -1, 1, 0, 0, 0, 0}, "Final momentum", false},
            {"p_i", {1, -1, 1, 0, 0, 0, 0}, "Initial momentum", false}
        },
        "Momentum",
        "Conservation of Momentum",
        "p_f"
    });
    
    // ========================================================================
    // INELASTIC COLLISION: m_1*v_1i + m_2*v_2i = (m_1+m_2)*v_f
    // ========================================================================
    
    formulas.push_back({
        "Perfectly Inelastic Collision (solve for v_f)",
        "v_f = \\frac{m_1 v_{1i} + m_2 v_{2i}}{m_1 + m_2}",
        {
            {"v_f", {1, -1, 0, 0, 0, 0, 0}, "Final velocity", false},
            {"m_1", {0, 0, 1, 0, 0, 0, 0}, "Mass 1", false},
            {"v_{1i}", {1, -1, 0, 0, 0, 0, 0}, "Initial velocity 1", false},
            {"m_2", {0, 0, 1, 0, 0, 0, 0}, "Mass 2", false},
            {"v_{2i}", {1, -1, 0, 0, 0, 0, 0}, "Initial velocity 2", false}
        },
        "Momentum",
        "Perfectly Inelastic Collision",
        "v_f"
    });
}

} // namespace Physics
