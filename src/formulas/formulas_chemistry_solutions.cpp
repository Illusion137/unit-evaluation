#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_chemistry_solutions() {
    
    // ========================================================================
    // MOLARITY: M = n / V
    // ========================================================================
    
    formulas.push_back({
        "Molarity (solve for M)",
        "M = \\frac{n}{V}",
        {
            {"M", {-3, 0, 0, 0, 0, 1, 0}, "Molarity", false},
            {"n", {0, 0, 0, 0, 0, 1, 0}, "Moles of solute", false},
            {"V", {3, 0, 0, 0, 0, 0, 0}, "Volume of solution", false}
        },
        "Chemistry - Solutions",
        "Molarity",
        "M"
    });
    
    formulas.push_back({
        "Molarity (solve for n)",
        "n = MV",
        {
            {"n", {0, 0, 0, 0, 0, 1, 0}, "Moles of solute", false},
            {"M", {-3, 0, 0, 0, 0, 1, 0}, "Molarity", false},
            {"V", {3, 0, 0, 0, 0, 0, 0}, "Volume of solution", false}
        },
        "Chemistry - Solutions",
        "Molarity",
        "n"
    });
    
    formulas.push_back({
        "Molarity (solve for V)",
        "V = \\frac{n}{M}",
        {
            {"V", {3, 0, 0, 0, 0, 0, 0}, "Volume of solution", false},
            {"n", {0, 0, 0, 0, 0, 1, 0}, "Moles of solute", false},
            {"M", {-3, 0, 0, 0, 0, 1, 0}, "Molarity", false}
        },
        "Chemistry - Solutions",
        "Molarity",
        "V"
    });
    
    // ========================================================================
    // DILUTION: M_1 * V_1 = M_2 * V_2
    // ========================================================================
    
    formulas.push_back({
        "Dilution (solve for M_2)",
        "M_2 = \\frac{M_1 V_1}{V_2}",
        {
            {"M_2", {-3, 0, 0, 0, 0, 1, 0}, "Final molarity", false},
            {"M_1", {-3, 0, 0, 0, 0, 1, 0}, "Initial molarity", false},
            {"V_1", {3, 0, 0, 0, 0, 0, 0}, "Initial volume", false},
            {"V_2", {3, 0, 0, 0, 0, 0, 0}, "Final volume", false}
        },
        "Chemistry - Solutions",
        "Dilution",
        "M_2"
    });
    
    formulas.push_back({
        "Dilution (solve for V_2)",
        "V_2 = \\frac{M_1 V_1}{M_2}",
        {
            {"V_2", {3, 0, 0, 0, 0, 0, 0}, "Final volume", false},
            {"M_1", {-3, 0, 0, 0, 0, 1, 0}, "Initial molarity", false},
            {"V_1", {3, 0, 0, 0, 0, 0, 0}, "Initial volume", false},
            {"M_2", {-3, 0, 0, 0, 0, 1, 0}, "Final molarity", false}
        },
        "Chemistry - Solutions",
        "Dilution",
        "V_2"
    });
    
    formulas.push_back({
        "Dilution (solve for M_1)",
        "M_1 = \\frac{M_2 V_2}{V_1}",
        {
            {"M_1", {-3, 0, 0, 0, 0, 1, 0}, "Initial molarity", false},
            {"M_2", {-3, 0, 0, 0, 0, 1, 0}, "Final molarity", false},
            {"V_2", {3, 0, 0, 0, 0, 0, 0}, "Final volume", false},
            {"V_1", {3, 0, 0, 0, 0, 0, 0}, "Initial volume", false}
        },
        "Chemistry - Solutions",
        "Dilution",
        "M_1"
    });
    
    formulas.push_back({
        "Dilution (solve for V_1)",
        "V_1 = \\frac{M_2 V_2}{M_1}",
        {
            {"V_1", {3, 0, 0, 0, 0, 0, 0}, "Initial volume", false},
            {"M_2", {-3, 0, 0, 0, 0, 1, 0}, "Final molarity", false},
            {"V_2", {3, 0, 0, 0, 0, 0, 0}, "Final volume", false},
            {"M_1", {-3, 0, 0, 0, 0, 1, 0}, "Initial molarity", false}
        },
        "Chemistry - Solutions",
        "Dilution",
        "V_1"
    });
    
    // ========================================================================
    // MASS PERCENT: mass_percent = (mass_solute / mass_solution) * 100
    // ========================================================================
    
    formulas.push_back({
        "Mass Percent (solve for mass_percent)",
        "\\text{mass\\%} = \\frac{m_{solute}}{m_{solution}} \\times 100",
        {
            {"\\text{mass\\%}", {0, 0, 0, 0, 0, 0, 0}, "Mass percent", false},
            {"m_{solute}", {0, 0, 1, 0, 0, 0, 0}, "Mass of solute", false},
            {"m_{solution}", {0, 0, 1, 0, 0, 0, 0}, "Mass of solution", false}
        },
        "Chemistry - Solutions",
        "Mass Percent",
        "\\text{mass\\%}"
    });
    
    formulas.push_back({
        "Mass Percent (solve for m_solute)",
        "m_{solute} = \\frac{\\text{mass\\%} \\times m_{solution}}{100}",
        {
            {"m_{solute}", {0, 0, 1, 0, 0, 0, 0}, "Mass of solute", false},
            {"\\text{mass\\%}", {0, 0, 0, 0, 0, 0, 0}, "Mass percent", false},
            {"m_{solution}", {0, 0, 1, 0, 0, 0, 0}, "Mass of solution", false}
        },
        "Chemistry - Solutions",
        "Mass Percent",
        "m_{solute}"
    });
    
    formulas.push_back({
        "Mass Percent (solve for m_solution)",
        "m_{solution} = \\frac{100 \\times m_{solute}}{\\text{mass\\%}}",
        {
            {"m_{solution}", {0, 0, 1, 0, 0, 0, 0}, "Mass of solution", false},
            {"m_{solute}", {0, 0, 1, 0, 0, 0, 0}, "Mass of solute", false},
            {"\\text{mass\\%}", {0, 0, 0, 0, 0, 0, 0}, "Mass percent", false}
        },
        "Chemistry - Solutions",
        "Mass Percent",
        "m_{solution}"
    });
    
    // ========================================================================
    // MOLE FRACTION: X_A = n_A / n_total
    // ========================================================================
    
    formulas.push_back({
        "Mole Fraction (solve for X_A)",
        "X_A = \\frac{n_A}{n_{total}}",
        {
            {"X_A", {0, 0, 0, 0, 0, 0, 0}, "Mole fraction of A", false},
            {"n_A", {0, 0, 0, 0, 0, 1, 0}, "Moles of A", false},
            {"n_{total}", {0, 0, 0, 0, 0, 1, 0}, "Total moles", false}
        },
        "Chemistry - Solutions",
        "Mole Fraction",
        "X_A"
    });
    
    formulas.push_back({
        "Mole Fraction (solve for n_A)",
        "n_A = X_A n_{total}",
        {
            {"n_A", {0, 0, 0, 0, 0, 1, 0}, "Moles of A", false},
            {"X_A", {0, 0, 0, 0, 0, 0, 0}, "Mole fraction of A", false},
            {"n_{total}", {0, 0, 0, 0, 0, 1, 0}, "Total moles", false}
        },
        "Chemistry - Solutions",
        "Mole Fraction",
        "n_A"
    });
    
    formulas.push_back({
        "Mole Fraction (solve for n_total)",
        "n_{total} = \\frac{n_A}{X_A}",
        {
            {"n_{total}", {0, 0, 0, 0, 0, 1, 0}, "Total moles", false},
            {"n_A", {0, 0, 0, 0, 0, 1, 0}, "Moles of A", false},
            {"X_A", {0, 0, 0, 0, 0, 0, 0}, "Mole fraction of A", false}
        },
        "Chemistry - Solutions",
        "Mole Fraction",
        "n_{total}"
    });
}

} // namespace Physics
