#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_kinematics() {
    
    // ========================================================================
    // VELOCITY WITH ACCELERATION: v = v_0 + a * t
    // ========================================================================
    
    formulas.push_back({
        "Velocity with Acceleration (solve for v)",
        "v = v_0 + at",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Final velocity", false},
            {"v_0", {1, -1, 0, 0, 0, 0, 0}, "Initial velocity", false},
            {"a", {1, -2, 0, 0, 0, 0, 0}, "Acceleration", false},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false}
        },
        "Kinematics",
        "Velocity with Acceleration",
        "v"
    });
    
    formulas.push_back({
        "Velocity with Acceleration (solve for v_0)",
        "v_0 = v - at",
        {
            {"v_0", {1, -1, 0, 0, 0, 0, 0}, "Initial velocity", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Final velocity", false},
            {"a", {1, -2, 0, 0, 0, 0, 0}, "Acceleration", false},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false}
        },
        "Kinematics",
        "Velocity with Acceleration",
        "v_0"
    });
    
    formulas.push_back({
        "Velocity with Acceleration (solve for a)",
        "a = \\frac{v - v_0}{t}",
        {
            {"a", {1, -2, 0, 0, 0, 0, 0}, "Acceleration", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Final velocity", false},
            {"v_0", {1, -1, 0, 0, 0, 0, 0}, "Initial velocity", false},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false}
        },
        "Kinematics",
        "Velocity with Acceleration",
        "a"
    });
    
    formulas.push_back({
        "Velocity with Acceleration (solve for t)",
        "t = \\frac{v - v_0}{a}",
        {
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Final velocity", false},
            {"v_0", {1, -1, 0, 0, 0, 0, 0}, "Initial velocity", false},
            {"a", {1, -2, 0, 0, 0, 0, 0}, "Acceleration", false}
        },
        "Kinematics",
        "Velocity with Acceleration",
        "t"
    });
    
    // ========================================================================
    // POSITION WITH ACCELERATION: x = x_0 + v_0*t + (1/2)*a*t^2
    // ========================================================================
    
    formulas.push_back({
        "Position with Acceleration (solve for x)",
        "x = x_0 + v_0 t + \\frac{1}{2}at^2",
        {
            {"x", {1, 0, 0, 0, 0, 0, 0}, "Final position", false},
            {"x_0", {1, 0, 0, 0, 0, 0, 0}, "Initial position", false},
            {"v_0", {1, -1, 0, 0, 0, 0, 0}, "Initial velocity", false},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false},
            {"a", {1, -2, 0, 0, 0, 0, 0}, "Acceleration", false}
        },
        "Kinematics",
        "Position with Acceleration",
        "x"
    });
    
    formulas.push_back({
        "Position with Acceleration (solve for x_0)",
        "x_0 = x - v_0 t - \\frac{1}{2}at^2",
        {
            {"x_0", {1, 0, 0, 0, 0, 0, 0}, "Initial position", false},
            {"x", {1, 0, 0, 0, 0, 0, 0}, "Final position", false},
            {"v_0", {1, -1, 0, 0, 0, 0, 0}, "Initial velocity", false},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false},
            {"a", {1, -2, 0, 0, 0, 0, 0}, "Acceleration", false}
        },
        "Kinematics",
        "Position with Acceleration",
        "x_0"
    });
    
    formulas.push_back({
        "Position with Acceleration (solve for a)",
        "a = \\frac{2(x - x_0 - v_0 t)}{t^2}",
        {
            {"a", {1, -2, 0, 0, 0, 0, 0}, "Acceleration", false},
            {"x", {1, 0, 0, 0, 0, 0, 0}, "Final position", false},
            {"x_0", {1, 0, 0, 0, 0, 0, 0}, "Initial position", false},
            {"v_0", {1, -1, 0, 0, 0, 0, 0}, "Initial velocity", false},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false}
        },
        "Kinematics",
        "Position with Acceleration",
        "a"
    });
    
    // ========================================================================
    // VELOCITY-POSITION RELATION: v^2 = v_0^2 + 2*a*(x - x_0)
    // ========================================================================
    
    formulas.push_back({
        "Velocity-Position Relation (solve for v)",
        "v^2 = v_0^2 + 2a(x - x_0)",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Final velocity", false},
            {"v_0", {1, -1, 0, 0, 0, 0, 0}, "Initial velocity", false},
            {"a", {1, -2, 0, 0, 0, 0, 0}, "Acceleration", false},
            {"x", {1, 0, 0, 0, 0, 0, 0}, "Final position", false},
            {"x_0", {1, 0, 0, 0, 0, 0, 0}, "Initial position", false}
        },
        "Kinematics",
        "Velocity-Position Relation",
        "v"
    });
    
    formulas.push_back({
        "Velocity-Position Relation (solve for v_0)",
        "v_0 = \\sqrt{v^2 - 2a(x - x_0)}",
        {
            {"v_0", {1, -1, 0, 0, 0, 0, 0}, "Initial velocity", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Final velocity", false},
            {"a", {1, -2, 0, 0, 0, 0, 0}, "Acceleration", false},
            {"x", {1, 0, 0, 0, 0, 0, 0}, "Final position", false},
            {"x_0", {1, 0, 0, 0, 0, 0, 0}, "Initial position", false}
        },
        "Kinematics",
        "Velocity-Position Relation",
        "v_0"
    });
    
    formulas.push_back({
        "Velocity-Position Relation (solve for a)",
        "a = \\frac{v^2 - v_0^2}{2(x - x_0)}",
        {
            {"a", {1, -2, 0, 0, 0, 0, 0}, "Acceleration", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Final velocity", false},
            {"v_0", {1, -1, 0, 0, 0, 0, 0}, "Initial velocity", false},
            {"x", {1, 0, 0, 0, 0, 0, 0}, "Final position", false},
            {"x_0", {1, 0, 0, 0, 0, 0, 0}, "Initial position", false}
        },
        "Kinematics",
        "Velocity-Position Relation",
        "a"
    });
    
    formulas.push_back({
        "Velocity-Position Relation (solve for x)",
        "x = x_0 + \\frac{v^2 - v_0^2}{2a}",
        {
            {"x", {1, 0, 0, 0, 0, 0, 0}, "Final position", false},
            {"x_0", {1, 0, 0, 0, 0, 0, 0}, "Initial position", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Final velocity", false},
            {"v_0", {1, -1, 0, 0, 0, 0, 0}, "Initial velocity", false},
            {"a", {1, -2, 0, 0, 0, 0, 0}, "Acceleration", false}
        },
        "Kinematics",
        "Velocity-Position Relation",
        "x"
    });
    
    // ========================================================================
    // AVERAGE VELOCITY: v_avg = (x - x_0) / t
    // ========================================================================
    
    formulas.push_back({
        "Average Velocity (solve for v_avg)",
        "v_{avg} = \\frac{x - x_0}{t}",
        {
            {"v_{avg}", {1, -1, 0, 0, 0, 0, 0}, "Average velocity", false},
            {"x", {1, 0, 0, 0, 0, 0, 0}, "Final position", false},
            {"x_0", {1, 0, 0, 0, 0, 0, 0}, "Initial position", false},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false}
        },
        "Kinematics",
        "Average Velocity",
        "v_{avg}"
    });
    
    formulas.push_back({
        "Average Velocity (solve for x)",
        "x = x_0 + v_{avg} t",
        {
            {"x", {1, 0, 0, 0, 0, 0, 0}, "Final position", false},
            {"x_0", {1, 0, 0, 0, 0, 0, 0}, "Initial position", false},
            {"v_{avg}", {1, -1, 0, 0, 0, 0, 0}, "Average velocity", false},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false}
        },
        "Kinematics",
        "Average Velocity",
        "x"
    });
    
    formulas.push_back({
        "Average Velocity (solve for t)",
        "t = \\frac{x - x_0}{v_{avg}}",
        {
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false},
            {"x", {1, 0, 0, 0, 0, 0, 0}, "Final position", false},
            {"x_0", {1, 0, 0, 0, 0, 0, 0}, "Initial position", false},
            {"v_{avg}", {1, -1, 0, 0, 0, 0, 0}, "Average velocity", false}
        },
        "Kinematics",
        "Average Velocity",
        "t"
    });
    
    // ========================================================================
    // AVERAGE VELOCITY FROM INITIAL AND FINAL: v_avg = (v_0 + v) / 2
    // ========================================================================
    
    formulas.push_back({
        "Average Velocity from Endpoints (solve for v_avg)",
        "v_{avg} = \\frac{v_0 + v}{2}",
        {
            {"v_{avg}", {1, -1, 0, 0, 0, 0, 0}, "Average velocity", false},
            {"v_0", {1, -1, 0, 0, 0, 0, 0}, "Initial velocity", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Final velocity", false}
        },
        "Kinematics",
        "Average Velocity from Endpoints",
        "v_{avg}"
    });
    
    formulas.push_back({
        "Average Velocity from Endpoints (solve for v_0)",
        "v_0 = 2v_{avg} - v",
        {
            {"v_0", {1, -1, 0, 0, 0, 0, 0}, "Initial velocity", false},
            {"v_{avg}", {1, -1, 0, 0, 0, 0, 0}, "Average velocity", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Final velocity", false}
        },
        "Kinematics",
        "Average Velocity from Endpoints",
        "v_0"
    });
    
    formulas.push_back({
        "Average Velocity from Endpoints (solve for v)",
        "v = 2v_{avg} - v_0",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Final velocity", false},
            {"v_{avg}", {1, -1, 0, 0, 0, 0, 0}, "Average velocity", false},
            {"v_0", {1, -1, 0, 0, 0, 0, 0}, "Initial velocity", false}
        },
        "Kinematics",
        "Average Velocity from Endpoints",
        "v"
    });
    
    // ========================================================================
    // FREE FALL: v = g * t (starting from rest, downward positive)
    // ========================================================================
    
    formulas.push_back({
        "Free Fall Velocity (solve for v)",
        "v = gt",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"g", {1, -2, 0, 0, 0, 0, 0}, "Gravitational acceleration", true},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false}
        },
        "Kinematics",
        "Free Fall Velocity",
        "v"
    });
    
    formulas.push_back({
        "Free Fall Velocity (solve for t)",
        "t = \\frac{v}{g}",
        {
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"g", {1, -2, 0, 0, 0, 0, 0}, "Gravitational acceleration", true}
        },
        "Kinematics",
        "Free Fall Velocity",
        "t"
    });
    
    // ========================================================================
    // FREE FALL DISTANCE: y = (1/2) * g * t^2
    // ========================================================================
    
    formulas.push_back({
        "Free Fall Distance (solve for y)",
        "y = \\frac{1}{2}gt^2",
        {
            {"y", {1, 0, 0, 0, 0, 0, 0}, "Distance fallen", false},
            {"g", {1, -2, 0, 0, 0, 0, 0}, "Gravitational acceleration", true},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false}
        },
        "Kinematics",
        "Free Fall Distance",
        "y"
    });
    
    formulas.push_back({
        "Free Fall Distance (solve for t)",
        "t = \\sqrt{\\frac{2y}{g}}",
        {
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false},
            {"y", {1, 0, 0, 0, 0, 0, 0}, "Distance fallen", false},
            {"g", {1, -2, 0, 0, 0, 0, 0}, "Gravitational acceleration", true}
        },
        "Kinematics",
        "Free Fall Distance",
        "t"
    });
    
    // ========================================================================
    // FREE FALL VELOCITY-DISTANCE: v^2 = 2 * g * y
    // ========================================================================
    
    formulas.push_back({
        "Free Fall Velocity-Distance (solve for v)",
        "v^2 = 2gy",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"g", {1, -2, 0, 0, 0, 0, 0}, "Gravitational acceleration", true},
            {"y", {1, 0, 0, 0, 0, 0, 0}, "Distance fallen", false}
        },
        "Kinematics",
        "Free Fall Velocity-Distance",
        "v"
    });
    
    formulas.push_back({
        "Free Fall Velocity-Distance (solve for y)",
        "y = \\frac{v^2}{2g}",
        {
            {"y", {1, 0, 0, 0, 0, 0, 0}, "Distance fallen", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"g", {1, -2, 0, 0, 0, 0, 0}, "Gravitational acceleration", true}
        },
        "Kinematics",
        "Free Fall Velocity-Distance",
        "y"
    });
}

} // namespace Physics
