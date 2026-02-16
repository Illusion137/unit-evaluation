#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_fluids() {
    
    // ========================================================================
    // PRESSURE: P = F / A
    // ========================================================================
    
    formulas.push_back({
        "Pressure (solve for P)",
        "P = \\frac{F}{A}",
        {
            {"P", {-1, -2, 1, 0, 0, 0, 0}, "Pressure", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area", false}
        },
        "Fluids",
        "Pressure",
        "P"
    });
    
    formulas.push_back({
        "Pressure (solve for F)",
        "F = PA",
        {
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"P", {-1, -2, 1, 0, 0, 0, 0}, "Pressure", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area", false}
        },
        "Fluids",
        "Pressure",
        "F"
    });
    
    formulas.push_back({
        "Pressure (solve for A)",
        "A = \\frac{F}{P}",
        {
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"P", {-1, -2, 1, 0, 0, 0, 0}, "Pressure", false}
        },
        "Fluids",
        "Pressure",
        "A"
    });
    
    // ========================================================================
    // HYDROSTATIC PRESSURE: P = rho * g * h
    // ========================================================================
    
    formulas.push_back({
        "Hydrostatic Pressure (solve for P)",
        "P = \\rho g h",
        {
            {"P", {-1, -2, 1, 0, 0, 0, 0}, "Pressure", false},
            {"\\rho", {-3, 0, 1, 0, 0, 0, 0}, "Density", false},
            {"g", {1, -2, 0, 0, 0, 0, 0}, "Gravitational acceleration", true},
            {"h", {1, 0, 0, 0, 0, 0, 0}, "Height", false}
        },
        "Fluids",
        "Hydrostatic Pressure",
        "P"
    });
    
    formulas.push_back({
        "Hydrostatic Pressure (solve for rho)",
        "\\rho = \\frac{P}{gh}",
        {
            {"\\rho", {-3, 0, 1, 0, 0, 0, 0}, "Density", false},
            {"P", {-1, -2, 1, 0, 0, 0, 0}, "Pressure", false},
            {"g", {1, -2, 0, 0, 0, 0, 0}, "Gravitational acceleration", true},
            {"h", {1, 0, 0, 0, 0, 0, 0}, "Height", false}
        },
        "Fluids",
        "Hydrostatic Pressure",
        "\\rho"
    });
    
    formulas.push_back({
        "Hydrostatic Pressure (solve for h)",
        "h = \\frac{P}{\\rho g}",
        {
            {"h", {1, 0, 0, 0, 0, 0, 0}, "Height", false},
            {"P", {-1, -2, 1, 0, 0, 0, 0}, "Pressure", false},
            {"\\rho", {-3, 0, 1, 0, 0, 0, 0}, "Density", false},
            {"g", {1, -2, 0, 0, 0, 0, 0}, "Gravitational acceleration", true}
        },
        "Fluids",
        "Hydrostatic Pressure",
        "h"
    });
    
    // ========================================================================
    // BUOYANCY: F_b = rho * V * g
    // ========================================================================
    
    formulas.push_back({
        "Buoyancy (solve for F_b)",
        "F_b = \\rho V g",
        {
            {"F_b", {1, -2, 1, 0, 0, 0, 0}, "Buoyant force", false},
            {"\\rho", {-3, 0, 1, 0, 0, 0, 0}, "Fluid density", false},
            {"V", {3, 0, 0, 0, 0, 0, 0}, "Volume", false},
            {"g", {1, -2, 0, 0, 0, 0, 0}, "Gravitational acceleration", true}
        },
        "Fluids",
        "Buoyancy",
        "F_b"
    });
    
    formulas.push_back({
        "Buoyancy (solve for rho)",
        "\\rho = \\frac{F_b}{Vg}",
        {
            {"\\rho", {-3, 0, 1, 0, 0, 0, 0}, "Fluid density", false},
            {"F_b", {1, -2, 1, 0, 0, 0, 0}, "Buoyant force", false},
            {"V", {3, 0, 0, 0, 0, 0, 0}, "Volume", false},
            {"g", {1, -2, 0, 0, 0, 0, 0}, "Gravitational acceleration", true}
        },
        "Fluids",
        "Buoyancy",
        "\\rho"
    });
    
    formulas.push_back({
        "Buoyancy (solve for V)",
        "V = \\frac{F_b}{\\rho g}",
        {
            {"V", {3, 0, 0, 0, 0, 0, 0}, "Volume", false},
            {"F_b", {1, -2, 1, 0, 0, 0, 0}, "Buoyant force", false},
            {"\\rho", {-3, 0, 1, 0, 0, 0, 0}, "Fluid density", false},
            {"g", {1, -2, 0, 0, 0, 0, 0}, "Gravitational acceleration", true}
        },
        "Fluids",
        "Buoyancy",
        "V"
    });
    
    // ========================================================================
    // CONTINUITY EQUATION: A_1 * v_1 = A_2 * v_2
    // ========================================================================
    
    formulas.push_back({
        "Continuity Equation (solve for v_2)",
        "v_2 = \\frac{A_1 v_1}{A_2}",
        {
            {"v_2", {1, -1, 0, 0, 0, 0, 0}, "Velocity 2", false},
            {"A_1", {2, 0, 0, 0, 0, 0, 0}, "Area 1", false},
            {"v_1", {1, -1, 0, 0, 0, 0, 0}, "Velocity 1", false},
            {"A_2", {2, 0, 0, 0, 0, 0, 0}, "Area 2", false}
        },
        "Fluids",
        "Continuity Equation",
        "v_2"
    });
    
    formulas.push_back({
        "Continuity Equation (solve for A_2)",
        "A_2 = \\frac{A_1 v_1}{v_2}",
        {
            {"A_2", {2, 0, 0, 0, 0, 0, 0}, "Area 2", false},
            {"A_1", {2, 0, 0, 0, 0, 0, 0}, "Area 1", false},
            {"v_1", {1, -1, 0, 0, 0, 0, 0}, "Velocity 1", false},
            {"v_2", {1, -1, 0, 0, 0, 0, 0}, "Velocity 2", false}
        },
        "Fluids",
        "Continuity Equation",
        "A_2"
    });
    
    // ========================================================================
    // DENSITY: rho = m / V
    // ========================================================================
    
    formulas.push_back({
        "Density (solve for rho)",
        "\\rho = \\frac{m}{V}",
        {
            {"\\rho", {-3, 0, 1, 0, 0, 0, 0}, "Density", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"V", {3, 0, 0, 0, 0, 0, 0}, "Volume", false}
        },
        "Fluids",
        "Density",
        "\\rho"
    });
    
    formulas.push_back({
        "Density (solve for m)",
        "m = \\rho V",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"\\rho", {-3, 0, 1, 0, 0, 0, 0}, "Density", false},
            {"V", {3, 0, 0, 0, 0, 0, 0}, "Volume", false}
        },
        "Fluids",
        "Density",
        "m"
    });
    
    formulas.push_back({
        "Density (solve for V)",
        "V = \\frac{m}{\\rho}",
        {
            {"V", {3, 0, 0, 0, 0, 0, 0}, "Volume", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"\\rho", {-3, 0, 1, 0, 0, 0, 0}, "Density", false}
        },
        "Fluids",
        "Density",
        "V"
    });
    
    // ========================================================================
    // FLOW RATE: Q = A * v
    // ========================================================================
    
    formulas.push_back({
        "Flow Rate (solve for Q)",
        "Q = Av",
        {
            {"Q", {3, -1, 0, 0, 0, 0, 0}, "Volume flow rate", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false}
        },
        "Fluids",
        "Flow Rate",
        "Q"
    });
    
    formulas.push_back({
        "Flow Rate (solve for A)",
        "A = \\frac{Q}{v}",
        {
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area", false},
            {"Q", {3, -1, 0, 0, 0, 0, 0}, "Volume flow rate", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false}
        },
        "Fluids",
        "Flow Rate",
        "A"
    });
    
    formulas.push_back({
        "Flow Rate (solve for v)",
        "v = \\frac{Q}{A}",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"Q", {3, -1, 0, 0, 0, 0, 0}, "Volume flow rate", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area", false}
        },
        "Fluids",
        "Flow Rate",
        "v"
    });
}

} // namespace Physics
