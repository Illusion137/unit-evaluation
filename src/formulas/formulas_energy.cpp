#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_energy() {
    
    // ========================================================================
    // KINETIC ENERGY: KE = (1/2) * m * v^2
    // ========================================================================
    
    formulas.push_back({
        "Kinetic Energy (solve for KE)",
        "KE = \\frac{1}{2}mv^2",
        {
            {"KE", {2, -2, 1, 0, 0, 0, 0}, "Kinetic energy", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false}
        },
        "Energy",
        "Kinetic Energy",
        "KE"
    });
    
    formulas.push_back({
        "Kinetic Energy (solve for m)",
        "m = \\frac{2KE}{v^2}",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"KE", {2, -2, 1, 0, 0, 0, 0}, "Kinetic energy", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false}
        },
        "Energy",
        "Kinetic Energy",
        "m"
    });
    
    formulas.push_back({
        "Kinetic Energy (solve for v)",
        "v = \\sqrt{\\frac{2KE}{m}}",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"KE", {2, -2, 1, 0, 0, 0, 0}, "Kinetic energy", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false}
        },
        "Energy",
        "Kinetic Energy",
        "v"
    });
    
    // ========================================================================
    // GRAVITATIONAL POTENTIAL ENERGY: PE = m * g * h
    // ========================================================================
    
    formulas.push_back({
        "Gravitational Potential Energy (solve for PE)",
        "PE = mgh",
        {
            {"PE", {2, -2, 1, 0, 0, 0, 0}, "Potential energy", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"g", {1, -2, 0, 0, 0, 0, 0}, "Gravitational acceleration", true},
            {"h", {1, 0, 0, 0, 0, 0, 0}, "Height", false}
        },
        "Energy",
        "Gravitational Potential Energy",
        "PE"
    });
    
    formulas.push_back({
        "Gravitational Potential Energy (solve for m)",
        "m = \\frac{PE}{gh}",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"PE", {2, -2, 1, 0, 0, 0, 0}, "Potential energy", false},
            {"g", {1, -2, 0, 0, 0, 0, 0}, "Gravitational acceleration", true},
            {"h", {1, 0, 0, 0, 0, 0, 0}, "Height", false}
        },
        "Energy",
        "Gravitational Potential Energy",
        "m"
    });
    
    formulas.push_back({
        "Gravitational Potential Energy (solve for h)",
        "h = \\frac{PE}{mg}",
        {
            {"h", {1, 0, 0, 0, 0, 0, 0}, "Height", false},
            {"PE", {2, -2, 1, 0, 0, 0, 0}, "Potential energy", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"g", {1, -2, 0, 0, 0, 0, 0}, "Gravitational acceleration", true}
        },
        "Energy",
        "Gravitational Potential Energy",
        "h"
    });
    
    // ========================================================================
    // ELASTIC POTENTIAL ENERGY: PE_spring = (1/2) * k * x^2
    // ========================================================================
    
    formulas.push_back({
        "Elastic Potential Energy (solve for PE)",
        "PE = \\frac{1}{2}kx^2",
        {
            {"PE", {2, -2, 1, 0, 0, 0, 0}, "Potential energy", false},
            {"k", {0, -2, 1, 0, 0, 0, 0}, "Spring constant", false},
            {"x", {1, 0, 0, 0, 0, 0, 0}, "Displacement", false}
        },
        "Energy",
        "Elastic Potential Energy",
        "PE"
    });
    
    formulas.push_back({
        "Elastic Potential Energy (solve for k)",
        "k = \\frac{2PE}{x^2}",
        {
            {"k", {0, -2, 1, 0, 0, 0, 0}, "Spring constant", false},
            {"PE", {2, -2, 1, 0, 0, 0, 0}, "Potential energy", false},
            {"x", {1, 0, 0, 0, 0, 0, 0}, "Displacement", false}
        },
        "Energy",
        "Elastic Potential Energy",
        "k"
    });
    
    formulas.push_back({
        "Elastic Potential Energy (solve for x)",
        "x = \\sqrt{\\frac{2PE}{k}}",
        {
            {"x", {1, 0, 0, 0, 0, 0, 0}, "Displacement", false},
            {"PE", {2, -2, 1, 0, 0, 0, 0}, "Potential energy", false},
            {"k", {0, -2, 1, 0, 0, 0, 0}, "Spring constant", false}
        },
        "Energy",
        "Elastic Potential Energy",
        "x"
    });
    
    // ========================================================================
    // WORK-ENERGY THEOREM: W = Delta_KE
    // ========================================================================
    
    formulas.push_back({
        "Work-Energy Theorem (solve for W)",
        "W = \\Delta KE",
        {
            {"W", {2, -2, 1, 0, 0, 0, 0}, "Work", false},
            {"\\Delta KE", {2, -2, 1, 0, 0, 0, 0}, "Change in kinetic energy", false}
        },
        "Energy",
        "Work-Energy Theorem",
        "W"
    });
    
    formulas.push_back({
        "Work-Energy Theorem (solve for Delta_KE)",
        "\\Delta KE = W",
        {
            {"\\Delta KE", {2, -2, 1, 0, 0, 0, 0}, "Change in kinetic energy", false},
            {"W", {2, -2, 1, 0, 0, 0, 0}, "Work", false}
        },
        "Energy",
        "Work-Energy Theorem",
        "\\Delta KE"
    });
    
    // ========================================================================
    // MECHANICAL ENERGY CONSERVATION: E = KE + PE
    // ========================================================================
    
    formulas.push_back({
        "Mechanical Energy (solve for E)",
        "E = KE + PE",
        {
            {"E", {2, -2, 1, 0, 0, 0, 0}, "Total mechanical energy", false},
            {"KE", {2, -2, 1, 0, 0, 0, 0}, "Kinetic energy", false},
            {"PE", {2, -2, 1, 0, 0, 0, 0}, "Potential energy", false}
        },
        "Energy",
        "Mechanical Energy",
        "E"
    });
    
    formulas.push_back({
        "Mechanical Energy (solve for KE)",
        "KE = E - PE",
        {
            {"KE", {2, -2, 1, 0, 0, 0, 0}, "Kinetic energy", false},
            {"E", {2, -2, 1, 0, 0, 0, 0}, "Total mechanical energy", false},
            {"PE", {2, -2, 1, 0, 0, 0, 0}, "Potential energy", false}
        },
        "Energy",
        "Mechanical Energy",
        "KE"
    });
    
    formulas.push_back({
        "Mechanical Energy (solve for PE)",
        "PE = E - KE",
        {
            {"PE", {2, -2, 1, 0, 0, 0, 0}, "Potential energy", false},
            {"E", {2, -2, 1, 0, 0, 0, 0}, "Total mechanical energy", false},
            {"KE", {2, -2, 1, 0, 0, 0, 0}, "Kinetic energy", false}
        },
        "Energy",
        "Mechanical Energy",
        "PE"
    });
    
    // ========================================================================
    // POWER: P = W / t
    // ========================================================================
    
    formulas.push_back({
        "Power from Work (solve for P)",
        "P = \\frac{W}{t}",
        {
            {"P", {2, -3, 1, 0, 0, 0, 0}, "Power", false},
            {"W", {2, -2, 1, 0, 0, 0, 0}, "Work", false},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false}
        },
        "Energy",
        "Power from Work",
        "P"
    });
    
    formulas.push_back({
        "Power from Work (solve for W)",
        "W = Pt",
        {
            {"W", {2, -2, 1, 0, 0, 0, 0}, "Work", false},
            {"P", {2, -3, 1, 0, 0, 0, 0}, "Power", false},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false}
        },
        "Energy",
        "Power from Work",
        "W"
    });
    
    formulas.push_back({
        "Power from Work (solve for t)",
        "t = \\frac{W}{P}",
        {
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false},
            {"W", {2, -2, 1, 0, 0, 0, 0}, "Work", false},
            {"P", {2, -3, 1, 0, 0, 0, 0}, "Power", false}
        },
        "Energy",
        "Power from Work",
        "t"
    });
    
    // ========================================================================
    // POWER: P = F * v
    // ========================================================================
    
    formulas.push_back({
        "Power from Force (solve for P)",
        "P = Fv",
        {
            {"P", {2, -3, 1, 0, 0, 0, 0}, "Power", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false}
        },
        "Energy",
        "Power from Force",
        "P"
    });
    
    formulas.push_back({
        "Power from Force (solve for F)",
        "F = \\frac{P}{v}",
        {
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"P", {2, -3, 1, 0, 0, 0, 0}, "Power", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false}
        },
        "Energy",
        "Power from Force",
        "F"
    });
    
    formulas.push_back({
        "Power from Force (solve for v)",
        "v = \\frac{P}{F}",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"P", {2, -3, 1, 0, 0, 0, 0}, "Power", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false}
        },
        "Energy",
        "Power from Force",
        "v"
    });
    
    // ========================================================================
    // EFFICIENCY: eta = W_out / W_in
    // ========================================================================
    
    formulas.push_back({
        "Efficiency (solve for eta)",
        "\\eta = \\frac{W_{out}}{W_{in}}",
        {
            {"\\eta", {0, 0, 0, 0, 0, 0, 0}, "Efficiency", false},
            {"W_{out}", {2, -2, 1, 0, 0, 0, 0}, "Work output", false},
            {"W_{in}", {2, -2, 1, 0, 0, 0, 0}, "Work input", false}
        },
        "Energy",
        "Efficiency",
        "\\eta"
    });
    
    formulas.push_back({
        "Efficiency (solve for W_out)",
        "W_{out} = \\eta W_{in}",
        {
            {"W_{out}", {2, -2, 1, 0, 0, 0, 0}, "Work output", false},
            {"\\eta", {0, 0, 0, 0, 0, 0, 0}, "Efficiency", false},
            {"W_{in}", {2, -2, 1, 0, 0, 0, 0}, "Work input", false}
        },
        "Energy",
        "Efficiency",
        "W_{out}"
    });
    
    formulas.push_back({
        "Efficiency (solve for W_in)",
        "W_{in} = \\frac{W_{out}}{\\eta}",
        {
            {"W_{in}", {2, -2, 1, 0, 0, 0, 0}, "Work input", false},
            {"W_{out}", {2, -2, 1, 0, 0, 0, 0}, "Work output", false},
            {"\\eta", {0, 0, 0, 0, 0, 0, 0}, "Efficiency", false}
        },
        "Energy",
        "Efficiency",
        "W_{in}"
    });
}

} // namespace Physics
