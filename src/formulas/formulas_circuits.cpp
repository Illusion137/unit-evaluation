#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_circuits() {
    
    // ========================================================================
    // OHM'S LAW: V = I * R
    // ========================================================================
    
    formulas.push_back({
        "Ohm's Law (solve for V)",
        "V = IR",
        {
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Voltage", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false}
        },
        "Circuits",
        "Ohm's Law",
        "V"
    });
    
    formulas.push_back({
        "Ohm's Law (solve for I)",
        "I = \\frac{V}{R}",
        {
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Voltage", false},
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false}
        },
        "Circuits",
        "Ohm's Law",
        "I"
    });
    
    formulas.push_back({
        "Ohm's Law (solve for R)",
        "R = \\frac{V}{I}",
        {
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Voltage", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false}
        },
        "Circuits",
        "Ohm's Law",
        "R"
    });
    
    // ========================================================================
    // ELECTRIC POWER: P = I * V
    // ========================================================================
    
    formulas.push_back({
        "Electric Power (solve for P)",
        "P = IV",
        {
            {"P", {2, -3, 1, 0, 0, 0, 0}, "Power", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Voltage", false}
        },
        "Circuits",
        "Electric Power",
        "P"
    });
    
    formulas.push_back({
        "Electric Power (solve for I)",
        "I = \\frac{P}{V}",
        {
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"P", {2, -3, 1, 0, 0, 0, 0}, "Power", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Voltage", false}
        },
        "Circuits",
        "Electric Power",
        "I"
    });
    
    formulas.push_back({
        "Electric Power (solve for V)",
        "V = \\frac{P}{I}",
        {
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Voltage", false},
            {"P", {2, -3, 1, 0, 0, 0, 0}, "Power", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false}
        },
        "Circuits",
        "Electric Power",
        "V"
    });
    
    // ========================================================================
    // POWER FROM CURRENT: P = I^2 * R
    // ========================================================================
    
    formulas.push_back({
        "Power from Current (solve for P)",
        "P = I^2 R",
        {
            {"P", {2, -3, 1, 0, 0, 0, 0}, "Power", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false}
        },
        "Circuits",
        "Power from Current",
        "P"
    });
    
    formulas.push_back({
        "Power from Current (solve for I)",
        "I = \\sqrt{\\frac{P}{R}}",
        {
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"P", {2, -3, 1, 0, 0, 0, 0}, "Power", false},
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false}
        },
        "Circuits",
        "Power from Current",
        "I"
    });
    
    formulas.push_back({
        "Power from Current (solve for R)",
        "R = \\frac{P}{I^2}",
        {
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false},
            {"P", {2, -3, 1, 0, 0, 0, 0}, "Power", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false}
        },
        "Circuits",
        "Power from Current",
        "R"
    });
    
    // ========================================================================
    // POWER FROM VOLTAGE: P = V^2 / R
    // ========================================================================
    
    formulas.push_back({
        "Power from Voltage (solve for P)",
        "P = \\frac{V^2}{R}",
        {
            {"P", {2, -3, 1, 0, 0, 0, 0}, "Power", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Voltage", false},
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false}
        },
        "Circuits",
        "Power from Voltage",
        "P"
    });
    
    formulas.push_back({
        "Power from Voltage (solve for V)",
        "V = \\sqrt{PR}",
        {
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Voltage", false},
            {"P", {2, -3, 1, 0, 0, 0, 0}, "Power", false},
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false}
        },
        "Circuits",
        "Power from Voltage",
        "V"
    });
    
    formulas.push_back({
        "Power from Voltage (solve for R)",
        "R = \\frac{V^2}{P}",
        {
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Voltage", false},
            {"P", {2, -3, 1, 0, 0, 0, 0}, "Power", false}
        },
        "Circuits",
        "Power from Voltage",
        "R"
    });
    
    // ========================================================================
    // RESISTORS IN SERIES: R_total = R_1 + R_2
    // ========================================================================
    
    formulas.push_back({
        "Resistors in Series (solve for R_total)",
        "R_{total} = R_1 + R_2",
        {
            {"R_{total}", {2, -3, 1, -2, 0, 0, 0}, "Total resistance", false},
            {"R_1", {2, -3, 1, -2, 0, 0, 0}, "Resistance 1", false},
            {"R_2", {2, -3, 1, -2, 0, 0, 0}, "Resistance 2", false}
        },
        "Circuits",
        "Resistors in Series",
        "R_{total}"
    });
    
    formulas.push_back({
        "Resistors in Series (solve for R_1)",
        "R_1 = R_{total} - R_2",
        {
            {"R_1", {2, -3, 1, -2, 0, 0, 0}, "Resistance 1", false},
            {"R_{total}", {2, -3, 1, -2, 0, 0, 0}, "Total resistance", false},
            {"R_2", {2, -3, 1, -2, 0, 0, 0}, "Resistance 2", false}
        },
        "Circuits",
        "Resistors in Series",
        "R_1"
    });
    
    formulas.push_back({
        "Resistors in Series (solve for R_2)",
        "R_2 = R_{total} - R_1",
        {
            {"R_2", {2, -3, 1, -2, 0, 0, 0}, "Resistance 2", false},
            {"R_{total}", {2, -3, 1, -2, 0, 0, 0}, "Total resistance", false},
            {"R_1", {2, -3, 1, -2, 0, 0, 0}, "Resistance 1", false}
        },
        "Circuits",
        "Resistors in Series",
        "R_2"
    });
    
    // ========================================================================
    // RESISTORS IN PARALLEL (TWO): 1/R_total = 1/R_1 + 1/R_2
    // ========================================================================
    
    formulas.push_back({
        "Resistors in Parallel (solve for R_total)",
        "\\frac{1}{R_{total}} = \\frac{1}{R_1} + \\frac{1}{R_2}",
        {
            {"R_{total}", {2, -3, 1, -2, 0, 0, 0}, "Total resistance", false},
            {"R_1", {2, -3, 1, -2, 0, 0, 0}, "Resistance 1", false},
            {"R_2", {2, -3, 1, -2, 0, 0, 0}, "Resistance 2", false}
        },
        "Circuits",
        "Resistors in Parallel",
        "R_{total}"
    });
    
    formulas.push_back({
        "Resistors in Parallel Simplified (solve for R_total)",
        "R_{total} = \\frac{R_1 R_2}{R_1 + R_2}",
        {
            {"R_{total}", {2, -3, 1, -2, 0, 0, 0}, "Total resistance", false},
            {"R_1", {2, -3, 1, -2, 0, 0, 0}, "Resistance 1", false},
            {"R_2", {2, -3, 1, -2, 0, 0, 0}, "Resistance 2", false}
        },
        "Circuits",
        "Resistors in Parallel Simplified",
        "R_{total}"
    });
    
    // ========================================================================
    // RESISTANCE FROM RESISTIVITY: R = rho * L / A
    // ========================================================================
    
    formulas.push_back({
        "Resistance from Resistivity (solve for R)",
        "R = \\rho \\frac{L}{A}",
        {
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false},
            {"\\rho", {3, -3, 1, -2, 0, 0, 0}, "Resistivity", false},
            {"L", {1, 0, 0, 0, 0, 0, 0}, "Length", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Cross-sectional area", false}
        },
        "Circuits",
        "Resistance from Resistivity",
        "R"
    });
    
    formulas.push_back({
        "Resistance from Resistivity (solve for rho)",
        "\\rho = R \\frac{A}{L}",
        {
            {"\\rho", {3, -3, 1, -2, 0, 0, 0}, "Resistivity", false},
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Cross-sectional area", false},
            {"L", {1, 0, 0, 0, 0, 0, 0}, "Length", false}
        },
        "Circuits",
        "Resistance from Resistivity",
        "\\rho"
    });
    
    formulas.push_back({
        "Resistance from Resistivity (solve for L)",
        "L = R \\frac{A}{\\rho}",
        {
            {"L", {1, 0, 0, 0, 0, 0, 0}, "Length", false},
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Cross-sectional area", false},
            {"\\rho", {3, -3, 1, -2, 0, 0, 0}, "Resistivity", false}
        },
        "Circuits",
        "Resistance from Resistivity",
        "L"
    });
    
    formulas.push_back({
        "Resistance from Resistivity (solve for A)",
        "A = \\rho \\frac{L}{R}",
        {
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Cross-sectional area", false},
            {"\\rho", {3, -3, 1, -2, 0, 0, 0}, "Resistivity", false},
            {"L", {1, 0, 0, 0, 0, 0, 0}, "Length", false},
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false}
        },
        "Circuits",
        "Resistance from Resistivity",
        "A"
    });
    
    // ========================================================================
    // CURRENT DENSITY: J = I / A
    // ========================================================================
    
    formulas.push_back({
        "Current Density (solve for J)",
        "J = \\frac{I}{A}",
        {
            {"J", {-2, 0, 0, 1, 0, 0, 0}, "Current density", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Cross-sectional area", false}
        },
        "Circuits",
        "Current Density",
        "J"
    });
    
    formulas.push_back({
        "Current Density (solve for I)",
        "I = JA",
        {
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"J", {-2, 0, 0, 1, 0, 0, 0}, "Current density", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Cross-sectional area", false}
        },
        "Circuits",
        "Current Density",
        "I"
    });
    
    formulas.push_back({
        "Current Density (solve for A)",
        "A = \\frac{I}{J}",
        {
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Cross-sectional area", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"J", {-2, 0, 0, 1, 0, 0, 0}, "Current density", false}
        },
        "Circuits",
        "Current Density",
        "A"
    });
    
    // ========================================================================
    // RC TIME CONSTANT: tau = R * C
    // ========================================================================
    
    formulas.push_back({
        "RC Time Constant (solve for tau)",
        "\\tau = RC",
        {
            {"\\tau", {0, 1, 0, 0, 0, 0, 0}, "Time constant", false},
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false},
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false}
        },
        "Circuits",
        "RC Time Constant",
        "\\tau"
    });
    
    formulas.push_back({
        "RC Time Constant (solve for R)",
        "R = \\frac{\\tau}{C}",
        {
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false},
            {"\\tau", {0, 1, 0, 0, 0, 0, 0}, "Time constant", false},
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false}
        },
        "Circuits",
        "RC Time Constant",
        "R"
    });
    
    formulas.push_back({
        "RC Time Constant (solve for C)",
        "C = \\frac{\\tau}{R}",
        {
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false},
            {"\\tau", {0, 1, 0, 0, 0, 0, 0}, "Time constant", false},
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false}
        },
        "Circuits",
        "RC Time Constant",
        "C"
    });
    
    // ========================================================================
    // ENERGY DISSIPATED: E = P * t
    // ========================================================================
    
    formulas.push_back({
        "Energy Dissipated (solve for E)",
        "E = Pt",
        {
            {"E", {2, -2, 1, 0, 0, 0, 0}, "Energy", false},
            {"P", {2, -3, 1, 0, 0, 0, 0}, "Power", false},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false}
        },
        "Circuits",
        "Energy Dissipated",
        "E"
    });
    
    formulas.push_back({
        "Energy Dissipated (solve for P)",
        "P = \\frac{E}{t}",
        {
            {"P", {2, -3, 1, 0, 0, 0, 0}, "Power", false},
            {"E", {2, -2, 1, 0, 0, 0, 0}, "Energy", false},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false}
        },
        "Circuits",
        "Energy Dissipated",
        "P"
    });
    
    formulas.push_back({
        "Energy Dissipated (solve for t)",
        "t = \\frac{E}{P}",
        {
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false},
            {"E", {2, -2, 1, 0, 0, 0, 0}, "Energy", false},
            {"P", {2, -3, 1, 0, 0, 0, 0}, "Power", false}
        },
        "Circuits",
        "Energy Dissipated",
        "t"
    });
    // ========================================================================
    // DRIFT VELOCITY: I = n * q * v_d * A
    // ========================================================================
    
    formulas.push_back({
        "Drift Velocity (solve for I)",
        "I = nqv_d A",
        {
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"n", {-3, 0, 0, 0, 0, 0, 0}, "Charge carrier density", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge per carrier", false},
            {"v_d", {1, -1, 0, 0, 0, 0, 0}, "Drift velocity", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Cross-sectional area", false}
        },
        "Circuits",
        "Drift Velocity",
        "I"
    });
    
    formulas.push_back({
        "Drift Velocity (solve for v_d)",
        "v_d = \\frac{I}{nqA}",
        {
            {"v_d", {1, -1, 0, 0, 0, 0, 0}, "Drift velocity", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"n", {-3, 0, 0, 0, 0, 0, 0}, "Charge carrier density", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge per carrier", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Cross-sectional area", false}
        },
        "Circuits",
        "Drift Velocity",
        "v_d"
    });
    
    formulas.push_back({
        "Drift Velocity (solve for n)",
        "n = \\frac{I}{qv_d A}",
        {
            {"n", {-3, 0, 0, 0, 0, 0, 0}, "Charge carrier density", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge per carrier", false},
            {"v_d", {1, -1, 0, 0, 0, 0, 0}, "Drift velocity", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Cross-sectional area", false}
        },
        "Circuits",
        "Drift Velocity",
        "n"
    });
    
    formulas.push_back({
        "Drift Velocity (solve for A)",
        "A = \\frac{I}{nqv_d}",
        {
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Cross-sectional area", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"n", {-3, 0, 0, 0, 0, 0, 0}, "Charge carrier density", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge per carrier", false},
            {"v_d", {1, -1, 0, 0, 0, 0, 0}, "Drift velocity", false}
        },
        "Circuits",
        "Drift Velocity",
        "A"
    });
    
    // ========================================================================
    // RESISTIVITY AND CONDUCTIVITY: sigma = 1 / rho
    // ========================================================================
    
    formulas.push_back({
        "Conductivity (solve for sigma)",
        "\\sigma = \\frac{1}{\\rho}",
        {
            {"\\sigma", {-3, 3, -1, 2, 0, 0, 0}, "Conductivity", false},
            {"\\rho", {3, -3, 1, -2, 0, 0, 0}, "Resistivity", false}
        },
        "Circuits",
        "Conductivity",
        "\\sigma"
    });
    
    formulas.push_back({
        "Conductivity (solve for rho)",
        "\\rho = \\frac{1}{\\sigma}",
        {
            {"\\rho", {3, -3, 1, -2, 0, 0, 0}, "Resistivity", false},
            {"\\sigma", {-3, 3, -1, 2, 0, 0, 0}, "Conductivity", false}
        },
        "Circuits",
        "Conductivity",
        "\\rho"
    });
    
    // ========================================================================
    // CONDUCTANCE: G = 1 / R
    // ========================================================================
    
    formulas.push_back({
        "Conductance (solve for G)",
        "G = \\frac{1}{R}",
        {
            {"G", {-2, 3, -1, 2, 0, 0, 0}, "Conductance", false},
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false}
        },
        "Circuits",
        "Conductance",
        "G"
    });
    
    formulas.push_back({
        "Conductance (solve for R)",
        "R = \\frac{1}{G}",
        {
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false},
            {"G", {-2, 3, -1, 2, 0, 0, 0}, "Conductance", false}
        },
        "Circuits",
        "Conductance",
        "R"
    });
    
    // ========================================================================
    // TEMPERATURE DEPENDENCE OF RESISTANCE: R = R_0 * (1 + alpha * Delta_T)
    // ========================================================================
    
    formulas.push_back({
        "Temperature Dependence of Resistance (solve for R)",
        "R = R_0(1 + \\alpha\\Delta T)",
        {
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance at temperature T", false},
            {"R_0", {2, -3, 1, -2, 0, 0, 0}, "Resistance at reference temperature", false},
            {"\\alpha", {0, 0, 0, 0, -1, 0, 0}, "Temperature coefficient", false},
            {"\\Delta T", {0, 0, 0, 0, 1, 0, 0}, "Temperature change", false}
        },
        "Circuits",
        "Temperature Dependence of Resistance",
        "R"
    });
    
    formulas.push_back({
        "Temperature Dependence of Resistance (solve for alpha)",
        "\\alpha = \\frac{R - R_0}{R_0 \\Delta T}",
        {
            {"\\alpha", {0, 0, 0, 0, -1, 0, 0}, "Temperature coefficient", false},
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance at temperature T", false},
            {"R_0", {2, -3, 1, -2, 0, 0, 0}, "Resistance at reference temperature", false},
            {"\\Delta T", {0, 0, 0, 0, 1, 0, 0}, "Temperature change", false}
        },
        "Circuits",
        "Temperature Dependence of Resistance",
        "\\alpha"
    });
    
    // ========================================================================
    // KIRCHHOFF'S CURRENT LAW (Junction Rule): Sum of currents = 0
    // ========================================================================
    
    formulas.push_back({
        "Kirchhoff's Current Law (conceptual)",
        "\\sum I_{in} = \\sum I_{out}",
        {
            {"\\sum I_{in}", {0, 0, 0, 1, 0, 0, 0}, "Sum of currents entering", false},
            {"\\sum I_{out}", {0, 0, 0, 1, 0, 0, 0}, "Sum of currents leaving", false}
        },
        "Circuits",
        "Kirchhoff's Current Law",
        "relationship"
    });
    
    // ========================================================================
    // KIRCHHOFF'S VOLTAGE LAW (Loop Rule): Sum of voltages = 0
    // ========================================================================
    
    formulas.push_back({
        "Kirchhoff's Voltage Law (conceptual)",
        "\\sum V = 0",
        {
            {"\\sum V", {2, -3, 1, -1, 0, 0, 0}, "Sum of voltage changes around loop", false}
        },
        "Circuits",
        "Kirchhoff's Voltage Law",
        "relationship"
    });
    
    // ========================================================================
    // EMF AND INTERNAL RESISTANCE: V = EMF - I * r
    // ========================================================================
    
    formulas.push_back({
        "EMF with Internal Resistance (solve for V)",
        "V = \\varepsilon - Ir",
        {
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Terminal voltage", false},
            {"\\varepsilon", {2, -3, 1, -1, 0, 0, 0}, "EMF", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"r", {2, -3, 1, -2, 0, 0, 0}, "Internal resistance", false}
        },
        "Circuits",
        "EMF with Internal Resistance",
        "V"
    });
    
    formulas.push_back({
        "EMF with Internal Resistance (solve for EMF)",
        "\\varepsilon = V + Ir",
        {
            {"\\varepsilon", {2, -3, 1, -1, 0, 0, 0}, "EMF", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Terminal voltage", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"r", {2, -3, 1, -2, 0, 0, 0}, "Internal resistance", false}
        },
        "Circuits",
        "EMF with Internal Resistance",
        "\\varepsilon"
    });
    
    formulas.push_back({
        "EMF with Internal Resistance (solve for I)",
        "I = \\frac{\\varepsilon - V}{r}",
        {
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"\\varepsilon", {2, -3, 1, -1, 0, 0, 0}, "EMF", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Terminal voltage", false},
            {"r", {2, -3, 1, -2, 0, 0, 0}, "Internal resistance", false}
        },
        "Circuits",
        "EMF with Internal Resistance",
        "I"
    });
    
    formulas.push_back({
        "EMF with Internal Resistance (solve for r)",
        "r = \\frac{\\varepsilon - V}{I}",
        {
            {"r", {2, -3, 1, -2, 0, 0, 0}, "Internal resistance", false},
            {"\\varepsilon", {2, -3, 1, -1, 0, 0, 0}, "EMF", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Terminal voltage", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false}
        },
        "Circuits",
        "EMF with Internal Resistance",
        "r"
    });
    
    // ========================================================================
    // RC CIRCUIT CHARGING: Q = Q_max * (1 - e^(-t/RC))
    // ========================================================================
    
    formulas.push_back({
        "RC Charging (conceptual)",
        "Q(t) = Q_{max}(1 - e^{-t/RC})",
        {
            {"Q(t)", {0, 1, 0, 1, 0, 0, 0}, "Charge at time t", false},
            {"Q_{max}", {0, 1, 0, 1, 0, 0, 0}, "Maximum charge", false},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false},
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false},
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false}
        },
        "Circuits",
        "RC Charging",
        "Q(t)"
    });
    
    // ========================================================================
    // RC CIRCUIT DISCHARGING: Q = Q_0 * e^(-t/RC)
    // ========================================================================
    
    formulas.push_back({
        "RC Discharging (conceptual)",
        "Q(t) = Q_0 e^{-t/RC}",
        {
            {"Q(t)", {0, 1, 0, 1, 0, 0, 0}, "Charge at time t", false},
            {"Q_0", {0, 1, 0, 1, 0, 0, 0}, "Initial charge", false},
            {"t", {0, 1, 0, 0, 0, 0, 0}, "Time", false},
            {"R", {2, -3, 1, -2, 0, 0, 0}, "Resistance", false},
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false}
        },
        "Circuits",
        "RC Discharging",
        "Q(t)"
    });
    
    // ========================================================================
    // EQUIVALENT RESISTANCE (3 RESISTORS IN SERIES)
    // ========================================================================
    
    formulas.push_back({
        "Three Resistors in Series (solve for R_total)",
        "R_{total} = R_1 + R_2 + R_3",
        {
            {"R_{total}", {2, -3, 1, -2, 0, 0, 0}, "Total resistance", false},
            {"R_1", {2, -3, 1, -2, 0, 0, 0}, "Resistance 1", false},
            {"R_2", {2, -3, 1, -2, 0, 0, 0}, "Resistance 2", false},
            {"R_3", {2, -3, 1, -2, 0, 0, 0}, "Resistance 3", false}
        },
        "Circuits",
        "Three Resistors in Series",
        "R_{total}"
    });
    
    // ========================================================================
    // EQUIVALENT RESISTANCE (3 RESISTORS IN PARALLEL)
    // ========================================================================
    
    formulas.push_back({
        "Three Resistors in Parallel (relationship)",
        "\\frac{1}{R_{total}} = \\frac{1}{R_1} + \\frac{1}{R_2} + \\frac{1}{R_3}",
        {
            {"R_{total}", {2, -3, 1, -2, 0, 0, 0}, "Total resistance", false},
            {"R_1", {2, -3, 1, -2, 0, 0, 0}, "Resistance 1", false},
            {"R_2", {2, -3, 1, -2, 0, 0, 0}, "Resistance 2", false},
            {"R_3", {2, -3, 1, -2, 0, 0, 0}, "Resistance 3", false}
        },
        "Circuits",
        "Three Resistors in Parallel",
        "R_{total}"
    });
    
    // ========================================================================
    // WHEATSTONE BRIDGE (BALANCED): R_1 / R_2 = R_3 / R_4
    // ========================================================================
    
    formulas.push_back({
        "Wheatstone Bridge Balanced (solve for R_4)",
        "R_4 = \\frac{R_2 R_3}{R_1}",
        {
            {"R_4", {2, -3, 1, -2, 0, 0, 0}, "Unknown resistance", false},
            {"R_1", {2, -3, 1, -2, 0, 0, 0}, "Resistance 1", false},
            {"R_2", {2, -3, 1, -2, 0, 0, 0}, "Resistance 2", false},
            {"R_3", {2, -3, 1, -2, 0, 0, 0}, "Resistance 3", false}
        },
        "Circuits",
        "Wheatstone Bridge Balanced",
        "R_4"
    });
}

} // namespace Physics
    
