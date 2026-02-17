#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_electrostatics() {
    
    // ========================================================================
    // COULOMB'S LAW: F = k * q1 * q2 / r^2
    // ========================================================================
    
    formulas.push_back({
        "Coulomb's Law (solve for F)",
        "F = k \\frac{q_1 q_2}{r^2}",
        {
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"k", {3, -4, 1, -2, 0, 0, 0}, "Coulomb's constant", true},
            {"q_1", {0, 1, 0, 1, 0, 0, 0}, "Charge 1", false},
            {"q_2", {0, 1, 0, 1, 0, 0, 0}, "Charge 2", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false}
        },
        "Electrostatics",
        "Coulomb's Law",
        "F"
    });
    
    formulas.push_back({
        "Coulomb's Law (solve for q_1)",
        "q_1 = \\frac{F r^2}{k q_2}",
        {
            {"q_1", {0, 1, 0, 1, 0, 0, 0}, "Charge 1", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false},
            {"k", {3, -4, 1, -2, 0, 0, 0}, "Coulomb's constant", true},
            {"q_2", {0, 1, 0, 1, 0, 0, 0}, "Charge 2", false}
        },
        "Electrostatics",
        "Coulomb's Law",
        "q_1"
    });
    
    formulas.push_back({
        "Coulomb's Law (solve for q_2)",
        "q_2 = \\frac{F r^2}{k q_1}",
        {
            {"q_2", {0, 1, 0, 1, 0, 0, 0}, "Charge 2", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false},
            {"k", {3, -4, 1, -2, 0, 0, 0}, "Coulomb's constant", true},
            {"q_1", {0, 1, 0, 1, 0, 0, 0}, "Charge 1", false}
        },
        "Electrostatics",
        "Coulomb's Law",
        "q_2"
    });
    
    formulas.push_back({
        "Coulomb's Law (solve for r)",
        "r = \\sqrt{\\frac{k q_1 q_2}{F}}",
        {
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false},
            {"k", {3, -4, 1, -2, 0, 0, 0}, "Coulomb's constant", true},
            {"q_1", {0, 1, 0, 1, 0, 0, 0}, "Charge 1", false},
            {"q_2", {0, 1, 0, 1, 0, 0, 0}, "Charge 2", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false}
        },
        "Electrostatics",
        "Coulomb's Law",
        "r"
    });
    
    // ========================================================================
    // ELECTRIC FIELD FROM FORCE: E = F / q
    // ========================================================================
    
    formulas.push_back({
        "Electric Field from Force (solve for E)",
        "E = \\frac{F}{q}",
        {
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false}
        },
        "Electrostatics",
        "Electric Field from Force",
        "E"
    });
    
    formulas.push_back({
        "Electric Field from Force (solve for F)",
        "F = Eq",
        {
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false}
        },
        "Electrostatics",
        "Electric Field from Force",
        "F"
    });
    
    formulas.push_back({
        "Electric Field from Force (solve for q)",
        "q = \\frac{F}{E}",
        {
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field", false}
        },
        "Electrostatics",
        "Electric Field from Force",
        "q"
    });
    
    // ========================================================================
    // ELECTRIC FIELD FROM POINT CHARGE: E = k * q / r^2
    // ========================================================================
    
    formulas.push_back({
        "Electric Field Point Charge (solve for E)",
        "E = k \\frac{q}{r^2}",
        {
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field", false},
            {"k", {3, -4, 1, -2, 0, 0, 0}, "Coulomb's constant", true},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false}
        },
        "Electrostatics",
        "Electric Field Point Charge",
        "E"
    });
    
    formulas.push_back({
        "Electric Field Point Charge (solve for q)",
        "q = \\frac{E r^2}{k}",
        {
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false},
            {"k", {3, -4, 1, -2, 0, 0, 0}, "Coulomb's constant", true}
        },
        "Electrostatics",
        "Electric Field Point Charge",
        "q"
    });
    
    formulas.push_back({
        "Electric Field Point Charge (solve for r)",
        "r = \\sqrt{\\frac{kq}{E}}",
        {
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false},
            {"k", {3, -4, 1, -2, 0, 0, 0}, "Coulomb's constant", true},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field", false}
        },
        "Electrostatics",
        "Electric Field Point Charge",
        "r"
    });
    
    // ========================================================================
    // ELECTRIC POTENTIAL: V = k * q / r
    // ========================================================================
    
    formulas.push_back({
        "Electric Potential Point Charge (solve for V)",
        "V = k \\frac{q}{r}",
        {
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Electric potential", false},
            {"k", {3, -4, 1, -2, 0, 0, 0}, "Coulomb's constant", true},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false}
        },
        "Electrostatics",
        "Electric Potential Point Charge",
        "V"
    });
    
    formulas.push_back({
        "Electric Potential Point Charge (solve for q)",
        "q = \\frac{Vr}{k}",
        {
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Electric potential", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false},
            {"k", {3, -4, 1, -2, 0, 0, 0}, "Coulomb's constant", true}
        },
        "Electrostatics",
        "Electric Potential Point Charge",
        "q"
    });
    
    formulas.push_back({
        "Electric Potential Point Charge (solve for r)",
        "r = \\frac{kq}{V}",
        {
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false},
            {"k", {3, -4, 1, -2, 0, 0, 0}, "Coulomb's constant", true},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Electric potential", false}
        },
        "Electrostatics",
        "Electric Potential Point Charge",
        "r"
    });
    
    // ========================================================================
    // ELECTRIC FIELD FROM POTENTIAL: E = V / d
    // ========================================================================
    
    formulas.push_back({
        "Electric Field from Potential (solve for E)",
        "E = \\frac{V}{d}",
        {
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Potential difference", false},
            {"d", {1, 0, 0, 0, 0, 0, 0}, "Distance", false}
        },
        "Electrostatics",
        "Electric Field from Potential",
        "E"
    });
    
    formulas.push_back({
        "Electric Field from Potential (solve for V)",
        "V = Ed",
        {
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Potential difference", false},
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field", false},
            {"d", {1, 0, 0, 0, 0, 0, 0}, "Distance", false}
        },
        "Electrostatics",
        "Electric Field from Potential",
        "V"
    });
    
    formulas.push_back({
        "Electric Field from Potential (solve for d)",
        "d = \\frac{V}{E}",
        {
            {"d", {1, 0, 0, 0, 0, 0, 0}, "Distance", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Potential difference", false},
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field", false}
        },
        "Electrostatics",
        "Electric Field from Potential",
        "d"
    });
    
    // ========================================================================
    // ELECTRIC POTENTIAL ENERGY: U = k * q1 * q2 / r
    // ========================================================================
    
    formulas.push_back({
        "Electric Potential Energy (solve for U)",
        "U = k \\frac{q_1 q_2}{r}",
        {
            {"U", {2, -2, 1, 0, 0, 0, 0}, "Potential energy", false},
            {"k", {3, -4, 1, -2, 0, 0, 0}, "Coulomb's constant", true},
            {"q_1", {0, 1, 0, 1, 0, 0, 0}, "Charge 1", false},
            {"q_2", {0, 1, 0, 1, 0, 0, 0}, "Charge 2", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false}
        },
        "Electrostatics",
        "Electric Potential Energy",
        "U"
    });
    
    formulas.push_back({
        "Electric Potential Energy (solve for q_1)",
        "q_1 = \\frac{Ur}{k q_2}",
        {
            {"q_1", {0, 1, 0, 1, 0, 0, 0}, "Charge 1", false},
            {"U", {2, -2, 1, 0, 0, 0, 0}, "Potential energy", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false},
            {"k", {3, -4, 1, -2, 0, 0, 0}, "Coulomb's constant", true},
            {"q_2", {0, 1, 0, 1, 0, 0, 0}, "Charge 2", false}
        },
        "Electrostatics",
        "Electric Potential Energy",
        "q_1"
    });
    
    formulas.push_back({
        "Electric Potential Energy (solve for r)",
        "r = k \\frac{q_1 q_2}{U}",
        {
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false},
            {"k", {3, -4, 1, -2, 0, 0, 0}, "Coulomb's constant", true},
            {"q_1", {0, 1, 0, 1, 0, 0, 0}, "Charge 1", false},
            {"q_2", {0, 1, 0, 1, 0, 0, 0}, "Charge 2", false},
            {"U", {2, -2, 1, 0, 0, 0, 0}, "Potential energy", false}
        },
        "Electrostatics",
        "Electric Potential Energy",
        "r"
    });
    
    // ========================================================================
    // CAPACITANCE: C = Q / V
    // ========================================================================
    
    formulas.push_back({
        "Capacitance (solve for C)",
        "C = \\frac{Q}{V}",
        {
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false},
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Voltage", false}
        },
        "Electrostatics",
        "Capacitance",
        "C"
    });
    
    formulas.push_back({
        "Capacitance (solve for Q)",
        "Q = CV",
        {
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Voltage", false}
        },
        "Electrostatics",
        "Capacitance",
        "Q"
    });
    
    formulas.push_back({
        "Capacitance (solve for V)",
        "V = \\frac{Q}{C}",
        {
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Voltage", false},
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false}
        },
        "Electrostatics",
        "Capacitance",
        "V"
    });
    
    // ========================================================================
    // PARALLEL PLATE CAPACITOR: C = epsilon_0 * A / d
    // ========================================================================
    
    formulas.push_back({
        "Parallel Plate Capacitor (solve for C)",
        "C = \\epsilon_0 \\frac{A}{d}",
        {
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false},
            {"\\epsilon_0", {-3, 4, -1, 2, 0, 0, 0}, "Permittivity of free space", true},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area", false},
            {"d", {1, 0, 0, 0, 0, 0, 0}, "Distance", false}
        },
        "Electrostatics",
        "Parallel Plate Capacitor",
        "C"
    });
    
    formulas.push_back({
        "Parallel Plate Capacitor (solve for A)",
        "A = \\frac{Cd}{\\epsilon_0}",
        {
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area", false},
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false},
            {"d", {1, 0, 0, 0, 0, 0, 0}, "Distance", false},
            {"\\epsilon_0", {-3, 4, -1, 2, 0, 0, 0}, "Permittivity of free space", true}
        },
        "Electrostatics",
        "Parallel Plate Capacitor",
        "A"
    });
    
    formulas.push_back({
        "Parallel Plate Capacitor (solve for d)",
        "d = \\epsilon_0 \\frac{A}{C}",
        {
            {"d", {1, 0, 0, 0, 0, 0, 0}, "Distance", false},
            {"\\epsilon_0", {-3, 4, -1, 2, 0, 0, 0}, "Permittivity of free space", true},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area", false},
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false}
        },
        "Electrostatics",
        "Parallel Plate Capacitor",
        "d"
    });
    
    // ========================================================================
    // CAPACITOR ENERGY: U = (1/2) * C * V^2
    // ========================================================================
    
    formulas.push_back({
        "Capacitor Energy (solve for U)",
        "U = \\frac{1}{2} C V^2",
        {
            {"U", {2, -2, 1, 0, 0, 0, 0}, "Energy", false},
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Voltage", false}
        },
        "Electrostatics",
        "Capacitor Energy",
        "U"
    });
    
    formulas.push_back({
        "Capacitor Energy (solve for C)",
        "C = \\frac{2U}{V^2}",
        {
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false},
            {"U", {2, -2, 1, 0, 0, 0, 0}, "Energy", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Voltage", false}
        },
        "Electrostatics",
        "Capacitor Energy",
        "C"
    });
    
    formulas.push_back({
        "Capacitor Energy (solve for V)",
        "V = \\sqrt{\\frac{2U}{C}}",
        {
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Voltage", false},
            {"U", {2, -2, 1, 0, 0, 0, 0}, "Energy", false},
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false}
        },
        "Electrostatics",
        "Capacitor Energy",
        "V"
    });
    
    // ========================================================================
    // CAPACITOR ENERGY FROM CHARGE: U = Q^2 / (2C)
    // ========================================================================
    
    formulas.push_back({
        "Capacitor Energy from Charge (solve for U)",
        "U = \\frac{Q^2}{2C}",
        {
            {"U", {2, -2, 1, 0, 0, 0, 0}, "Energy", false},
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false}
        },
        "Electrostatics",
        "Capacitor Energy from Charge",
        "U"
    });
    
    formulas.push_back({
        "Capacitor Energy from Charge (solve for Q)",
        "Q = \\sqrt{2UC}",
        {
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"U", {2, -2, 1, 0, 0, 0, 0}, "Energy", false},
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false}
        },
        "Electrostatics",
        "Capacitor Energy from Charge",
        "Q"
    });
    
    formulas.push_back({
        "Capacitor Energy from Charge (solve for C)",
        "C = \\frac{Q^2}{2U}",
        {
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false},
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"U", {2, -2, 1, 0, 0, 0, 0}, "Energy", false}
        },
        "Electrostatics",
        "Capacitor Energy from Charge",
        "C"
    });
    
    // ========================================================================
    // CAPACITORS IN PARALLEL: C_total = C_1 + C_2
    // ========================================================================
    
    formulas.push_back({
        "Capacitors in Parallel (solve for C_total)",
        "C_{total} = C_1 + C_2",
        {
            {"C_{total}", {-2, 4, -1, 2, 0, 0, 0}, "Total capacitance", false},
            {"C_1", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance 1", false},
            {"C_2", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance 2", false}
        },
        "Electrostatics",
        "Capacitors in Parallel",
        "C_{total}"
    });
    
    formulas.push_back({
        "Capacitors in Parallel (solve for C_1)",
        "C_1 = C_{total} - C_2",
        {
            {"C_1", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance 1", false},
            {"C_{total}", {-2, 4, -1, 2, 0, 0, 0}, "Total capacitance", false},
            {"C_2", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance 2", false}
        },
        "Electrostatics",
        "Capacitors in Parallel",
        "C_1"
    });
    // ========================================================================
    // CAPACITANCE WITH DIELECTRIC: C = kappa * C_0
    // ========================================================================
    
    formulas.push_back({
        "Capacitance with Dielectric (solve for C)",
        "C = \\kappa C_0",
        {
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance with dielectric", false},
            {"\\kappa", {0, 0, 0, 0, 0, 0, 0}, "Dielectric constant", false},
            {"C_0", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance without dielectric", false}
        },
        "Electrostatics",
        "Capacitance with Dielectric",
        "C"
    });
    
    formulas.push_back({
        "Capacitance with Dielectric (solve for kappa)",
        "\\kappa = \\frac{C}{C_0}",
        {
            {"\\kappa", {0, 0, 0, 0, 0, 0, 0}, "Dielectric constant", false},
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance with dielectric", false},
            {"C_0", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance without dielectric", false}
        },
        "Electrostatics",
        "Capacitance with Dielectric",
        "\\kappa"
    });
    
    formulas.push_back({
        "Capacitance with Dielectric (solve for C_0)",
        "C_0 = \\frac{C}{\\kappa}",
        {
            {"C_0", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance without dielectric", false},
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance with dielectric", false},
            {"\\kappa", {0, 0, 0, 0, 0, 0, 0}, "Dielectric constant", false}
        },
        "Electrostatics",
        "Capacitance with Dielectric",
        "C_0"
    });
    
    // ========================================================================
    // ELECTRIC FIELD IN DIELECTRIC: E = E_0 / kappa
    // ========================================================================
    
    formulas.push_back({
        "Electric Field in Dielectric (solve for E)",
        "E = \\frac{E_0}{\\kappa}",
        {
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field in dielectric", false},
            {"E_0", {1, -3, 1, -1, 0, 0, 0}, "Electric field in vacuum", false},
            {"\\kappa", {0, 0, 0, 0, 0, 0, 0}, "Dielectric constant", false}
        },
        "Electrostatics",
        "Electric Field in Dielectric",
        "E"
    });
    
    formulas.push_back({
        "Electric Field in Dielectric (solve for E_0)",
        "E_0 = \\kappa E",
        {
            {"E_0", {1, -3, 1, -1, 0, 0, 0}, "Electric field in vacuum", false},
            {"\\kappa", {0, 0, 0, 0, 0, 0, 0}, "Dielectric constant", false},
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field in dielectric", false}
        },
        "Electrostatics",
        "Electric Field in Dielectric",
        "E_0"
    });
    
    formulas.push_back({
        "Electric Field in Dielectric (solve for kappa)",
        "\\kappa = \\frac{E_0}{E}",
        {
            {"\\kappa", {0, 0, 0, 0, 0, 0, 0}, "Dielectric constant", false},
            {"E_0", {1, -3, 1, -1, 0, 0, 0}, "Electric field in vacuum", false},
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field in dielectric", false}
        },
        "Electrostatics",
        "Electric Field in Dielectric",
        "\\kappa"
    });
    
    // ========================================================================
    // ENERGY DENSITY IN ELECTRIC FIELD: u = (1/2) * epsilon_0 * E^2
    // ========================================================================
    
    formulas.push_back({
        "Electric Energy Density (solve for u)",
        "u = \\frac{1}{2}\\epsilon_0 E^2",
        {
            {"u", {-1, -2, 1, 0, 0, 0, 0}, "Energy density", false},
            {"\\epsilon_0", {-3, 4, -1, 2, 0, 0, 0}, "Permittivity of free space", true},
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field", false}
        },
        "Electrostatics",
        "Electric Energy Density",
        "u"
    });
    
    formulas.push_back({
        "Electric Energy Density (solve for E)",
        "E = \\sqrt{\\frac{2u}{\\epsilon_0}}",
        {
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field", false},
            {"u", {-1, -2, 1, 0, 0, 0, 0}, "Energy density", false},
            {"\\epsilon_0", {-3, 4, -1, 2, 0, 0, 0}, "Permittivity of free space", true}
        },
        "Electrostatics",
        "Electric Energy Density",
        "E"
    });
    
    // ========================================================================
    // ELECTRIC DIPOLE MOMENT: p = q * d
    // ========================================================================
    
    formulas.push_back({
        "Electric Dipole Moment (solve for p)",
        "p = qd",
        {
            {"p", {1, 1, 0, 1, 0, 0, 0}, "Dipole moment", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"d", {1, 0, 0, 0, 0, 0, 0}, "Separation distance", false}
        },
        "Electrostatics",
        "Electric Dipole Moment",
        "p"
    });
    
    formulas.push_back({
        "Electric Dipole Moment (solve for q)",
        "q = \\frac{p}{d}",
        {
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"p", {1, 1, 0, 1, 0, 0, 0}, "Dipole moment", false},
            {"d", {1, 0, 0, 0, 0, 0, 0}, "Separation distance", false}
        },
        "Electrostatics",
        "Electric Dipole Moment",
        "q"
    });
    
    formulas.push_back({
        "Electric Dipole Moment (solve for d)",
        "d = \\frac{p}{q}",
        {
            {"d", {1, 0, 0, 0, 0, 0, 0}, "Separation distance", false},
            {"p", {1, 1, 0, 1, 0, 0, 0}, "Dipole moment", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false}
        },
        "Electrostatics",
        "Electric Dipole Moment",
        "d"
    });
    
    // ========================================================================
    // ELECTRIC FLUX: Phi = E * A (for uniform field perpendicular to surface)
    // ========================================================================
    
    formulas.push_back({
        "Electric Flux (solve for Phi)",
        "\\Phi_E = EA",
        {
            {"\\Phi_E", {3, -3, 1, -1, 0, 0, 0}, "Electric flux", false},
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area", false}
        },
        "Electrostatics",
        "Electric Flux",
        "\\Phi_E"
    });
    
    formulas.push_back({
        "Electric Flux (solve for E)",
        "E = \\frac{\\Phi_E}{A}",
        {
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field", false},
            {"\\Phi_E", {3, -3, 1, -1, 0, 0, 0}, "Electric flux", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area", false}
        },
        "Electrostatics",
        "Electric Flux",
        "E"
    });
    
    formulas.push_back({
        "Electric Flux (solve for A)",
        "A = \\frac{\\Phi_E}{E}",
        {
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area", false},
            {"\\Phi_E", {3, -3, 1, -1, 0, 0, 0}, "Electric flux", false},
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field", false}
        },
        "Electrostatics",
        "Electric Flux",
        "A"
    });
    
    // ========================================================================
    // GAUSS'S LAW: Phi = Q_enclosed / epsilon_0
    // ========================================================================
    
    formulas.push_back({
        "Gauss's Law (solve for Phi)",
        "\\Phi_E = \\frac{Q_{enc}}{\\epsilon_0}",
        {
            {"\\Phi_E", {3, -3, 1, -1, 0, 0, 0}, "Electric flux", false},
            {"Q_{enc}", {0, 1, 0, 1, 0, 0, 0}, "Enclosed charge", false},
            {"\\epsilon_0", {-3, 4, -1, 2, 0, 0, 0}, "Permittivity of free space", true}
        },
        "Electrostatics",
        "Gauss's Law",
        "\\Phi_E"
    });
    
    formulas.push_back({
        "Gauss's Law (solve for Q_enc)",
        "Q_{enc} = \\epsilon_0 \\Phi_E",
        {
            {"Q_{enc}", {0, 1, 0, 1, 0, 0, 0}, "Enclosed charge", false},
            {"\\epsilon_0", {-3, 4, -1, 2, 0, 0, 0}, "Permittivity of free space", true},
            {"\\Phi_E", {3, -3, 1, -1, 0, 0, 0}, "Electric flux", false}
        },
        "Electrostatics",
        "Gauss's Law",
        "Q_{enc}"
    });
    
    // ========================================================================
    // SURFACE CHARGE DENSITY: sigma = Q / A
    // ========================================================================
    
    formulas.push_back({
        "Surface Charge Density (solve for sigma)",
        "\\sigma = \\frac{Q}{A}",
        {
            {"\\sigma", {-2, 1, 0, 1, 0, 0, 0}, "Surface charge density", false},
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area", false}
        },
        "Electrostatics",
        "Surface Charge Density",
        "\\sigma"
    });
    
    formulas.push_back({
        "Surface Charge Density (solve for Q)",
        "Q = \\sigma A",
        {
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"\\sigma", {-2, 1, 0, 1, 0, 0, 0}, "Surface charge density", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area", false}
        },
        "Electrostatics",
        "Surface Charge Density",
        "Q"
    });
    
    formulas.push_back({
        "Surface Charge Density (solve for A)",
        "A = \\frac{Q}{\\sigma}",
        {
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area", false},
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"\\sigma", {-2, 1, 0, 1, 0, 0, 0}, "Surface charge density", false}
        },
        "Electrostatics",
        "Surface Charge Density",
        "A"
    });
    
    // ========================================================================
    // LINEAR CHARGE DENSITY: lambda = Q / L
    // ========================================================================
    
    formulas.push_back({
        "Linear Charge Density (solve for lambda)",
        "\\lambda = \\frac{Q}{L}",
        {
            {"\\lambda", {-1, 1, 0, 1, 0, 0, 0}, "Linear charge density", false},
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"L", {1, 0, 0, 0, 0, 0, 0}, "Length", false}
        },
        "Electrostatics",
        "Linear Charge Density",
        "\\lambda"
    });
    
    formulas.push_back({
        "Linear Charge Density (solve for Q)",
        "Q = \\lambda L",
        {
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"\\lambda", {-1, 1, 0, 1, 0, 0, 0}, "Linear charge density", false},
            {"L", {1, 0, 0, 0, 0, 0, 0}, "Length", false}
        },
        "Electrostatics",
        "Linear Charge Density",
        "Q"
    });
    
    formulas.push_back({
        "Linear Charge Density (solve for L)",
        "L = \\frac{Q}{\\lambda}",
        {
            {"L", {1, 0, 0, 0, 0, 0, 0}, "Length", false},
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"\\lambda", {-1, 1, 0, 1, 0, 0, 0}, "Linear charge density", false}
        },
        "Electrostatics",
        "Linear Charge Density",
        "L"
    });
    
    // ========================================================================
    // VOLUME CHARGE DENSITY: rho = Q / V
    // ========================================================================
    
    formulas.push_back({
        "Volume Charge Density (solve for rho)",
        "\\rho_q = \\frac{Q}{V}",
        {
            {"\\rho_q", {-3, 1, 0, 1, 0, 0, 0}, "Volume charge density", false},
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"V", {3, 0, 0, 0, 0, 0, 0}, "Volume", false}
        },
        "Electrostatics",
        "Volume Charge Density",
        "\\rho_q"
    });
    
    formulas.push_back({
        "Volume Charge Density (solve for Q)",
        "Q = \\rho_q V",
        {
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"\\rho_q", {-3, 1, 0, 1, 0, 0, 0}, "Volume charge density", false},
            {"V", {3, 0, 0, 0, 0, 0, 0}, "Volume", false}
        },
        "Electrostatics",
        "Volume Charge Density",
        "Q"
    });
    
    formulas.push_back({
        "Volume Charge Density (solve for V)",
        "V = \\frac{Q}{\\rho_q}",
        {
            {"V", {3, 0, 0, 0, 0, 0, 0}, "Volume", false},
            {"Q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"\\rho_q", {-3, 1, 0, 1, 0, 0, 0}, "Volume charge density", false}
        },
        "Electrostatics",
        "Volume Charge Density",
        "V"
    });
    
    // ========================================================================
    // ELECTRIC FIELD OF INFINITE PLANE: E = sigma / (2 * epsilon_0)
    // ========================================================================
    
    formulas.push_back({
        "Electric Field of Infinite Plane (solve for E)",
        "E = \\frac{\\sigma}{2\\epsilon_0}",
        {
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field", false},
            {"\\sigma", {-2, 1, 0, 1, 0, 0, 0}, "Surface charge density", false},
            {"\\epsilon_0", {-3, 4, -1, 2, 0, 0, 0}, "Permittivity of free space", true}
        },
        "Electrostatics",
        "Electric Field of Infinite Plane",
        "E"
    });
    
    formulas.push_back({
        "Electric Field of Infinite Plane (solve for sigma)",
        "\\sigma = 2\\epsilon_0 E",
        {
            {"\\sigma", {-2, 1, 0, 1, 0, 0, 0}, "Surface charge density", false},
            {"\\epsilon_0", {-3, 4, -1, 2, 0, 0, 0}, "Permittivity of free space", true},
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field", false}
        },
        "Electrostatics",
        "Electric Field of Infinite Plane",
        "\\sigma"
    });
    
    // ========================================================================
    // SPHERICAL CAPACITOR: C = 4 * pi * epsilon_0 * (r_a * r_b) / (r_b - r_a)
    // ========================================================================
    
    formulas.push_back({
        "Spherical Capacitor (solve for C)",
        "C = 4\\pi\\epsilon_0 \\frac{r_a r_b}{r_b - r_a}",
        {
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false},
            {"\\epsilon_0", {-3, 4, -1, 2, 0, 0, 0}, "Permittivity of free space", true},
            {"r_a", {1, 0, 0, 0, 0, 0, 0}, "Inner radius", false},
            {"r_b", {1, 0, 0, 0, 0, 0, 0}, "Outer radius", false}
        },
        "Electrostatics",
        "Spherical Capacitor",
        "C"
    });
    
    // ========================================================================
    // CYLINDRICAL CAPACITOR: C = 2 * pi * epsilon_0 * L / ln(r_b / r_a)
    // ========================================================================
    
    formulas.push_back({
        "Cylindrical Capacitor (solve for C)",
        "C = \\frac{2\\pi\\epsilon_0 L}{\\ln(r_b/r_a)}",
        {
            {"C", {-2, 4, -1, 2, 0, 0, 0}, "Capacitance", false},
            {"\\epsilon_0", {-3, 4, -1, 2, 0, 0, 0}, "Permittivity of free space", true},
            {"L", {1, 0, 0, 0, 0, 0, 0}, "Length", false},
            {"r_a", {1, 0, 0, 0, 0, 0, 0}, "Inner radius", false},
            {"r_b", {1, 0, 0, 0, 0, 0, 0}, "Outer radius", false}
        },
        "Electrostatics",
        "Cylindrical Capacitor",
        "C"
    });
}

} // namespace Physics
    
