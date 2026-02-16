#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_chemistry_acids_bases() {
    
    // ========================================================================
    // pH: pH = -log[H+]
    // ========================================================================
    
    formulas.push_back({
        "pH (solve for pH)",
        "\\text{pH} = -\\log[H^+]",
        {
            {"\\text{pH}", {0, 0, 0, 0, 0, 0, 0}, "pH", false},
            {"[H^+]", {-3, 0, 0, 0, 0, 1, 0}, "Hydrogen ion concentration", false}
        },
        "Chemistry - Acids & Bases",
        "pH",
        "\\text{pH}"
    });
    
    formulas.push_back({
        "pH (solve for H+)",
        "[H^+] = 10^{-\\text{pH}}",
        {
            {"[H^+]", {-3, 0, 0, 0, 0, 1, 0}, "Hydrogen ion concentration", false},
            {"\\text{pH}", {0, 0, 0, 0, 0, 0, 0}, "pH", false}
        },
        "Chemistry - Acids & Bases",
        "pH",
        "[H^+]"
    });
    
    // ========================================================================
    // pOH: pOH = -log[OH-]
    // ========================================================================
    
    formulas.push_back({
        "pOH (solve for pOH)",
        "\\text{pOH} = -\\log[OH^-]",
        {
            {"\\text{pOH}", {0, 0, 0, 0, 0, 0, 0}, "pOH", false},
            {"[OH^-]", {-3, 0, 0, 0, 0, 1, 0}, "Hydroxide ion concentration", false}
        },
        "Chemistry - Acids & Bases",
        "pOH",
        "\\text{pOH}"
    });
    
    formulas.push_back({
        "pOH (solve for OH-)",
        "[OH^-] = 10^{-\\text{pOH}}",
        {
            {"[OH^-]", {-3, 0, 0, 0, 0, 1, 0}, "Hydroxide ion concentration", false},
            {"\\text{pOH}", {0, 0, 0, 0, 0, 0, 0}, "pOH", false}
        },
        "Chemistry - Acids & Bases",
        "pOH",
        "[OH^-]"
    });
    
    // ========================================================================
    // pH + pOH = 14 (at 25°C)
    // ========================================================================
    
    formulas.push_back({
        "pH and pOH Relationship (solve for pH)",
        "\\text{pH} = 14 - \\text{pOH}",
        {
            {"\\text{pH}", {0, 0, 0, 0, 0, 0, 0}, "pH", false},
            {"\\text{pOH}", {0, 0, 0, 0, 0, 0, 0}, "pOH", false}
        },
        "Chemistry - Acids & Bases",
        "pH and pOH Relationship",
        "\\text{pH}"
    });
    
    formulas.push_back({
        "pH and pOH Relationship (solve for pOH)",
        "\\text{pOH} = 14 - \\text{pH}",
        {
            {"\\text{pOH}", {0, 0, 0, 0, 0, 0, 0}, "pOH", false},
            {"\\text{pH}", {0, 0, 0, 0, 0, 0, 0}, "pH", false}
        },
        "Chemistry - Acids & Bases",
        "pH and pOH Relationship",
        "\\text{pOH}"
    });
    
    // ========================================================================
    // pK_a: pK_a = -log(K_a)
    // ========================================================================
    
    formulas.push_back({
        "pKa (solve for pK_a)",
        "\\text{pK}_a = -\\log K_a",
        {
            {"\\text{pK}_a", {0, 0, 0, 0, 0, 0, 0}, "pKa", false},
            {"K_a", {0, 0, 0, 0, 0, 0, 0}, "Acid dissociation constant", false}
        },
        "Chemistry - Acids & Bases",
        "pKa",
        "\\text{pK}_a"
    });
    
    formulas.push_back({
        "pKa (solve for K_a)",
        "K_a = 10^{-\\text{pK}_a}",
        {
            {"K_a", {0, 0, 0, 0, 0, 0, 0}, "Acid dissociation constant", false},
            {"\\text{pK}_a", {0, 0, 0, 0, 0, 0, 0}, "pKa", false}
        },
        "Chemistry - Acids & Bases",
        "pKa",
        "K_a"
    });
    
    // ========================================================================
    // pK_b: pK_b = -log(K_b)
    // ========================================================================
    
    formulas.push_back({
        "pKb (solve for pK_b)",
        "\\text{pK}_b = -\\log K_b",
        {
            {"\\text{pK}_b", {0, 0, 0, 0, 0, 0, 0}, "pKb", false},
            {"K_b", {0, 0, 0, 0, 0, 0, 0}, "Base dissociation constant", false}
        },
        "Chemistry - Acids & Bases",
        "pKb",
        "\\text{pK}_b"
    });
    
    formulas.push_back({
        "pKb (solve for K_b)",
        "K_b = 10^{-\\text{pK}_b}",
        {
            {"K_b", {0, 0, 0, 0, 0, 0, 0}, "Base dissociation constant", false},
            {"\\text{pK}_b", {0, 0, 0, 0, 0, 0, 0}, "pKb", false}
        },
        "Chemistry - Acids & Bases",
        "pKb",
        "K_b"
    });
    
    // ========================================================================
    // pK_a + pK_b = 14 (at 25°C)
    // ========================================================================
    
    formulas.push_back({
        "pKa and pKb Relationship (solve for pK_a)",
        "\\text{pK}_a = 14 - \\text{pK}_b",
        {
            {"\\text{pK}_a", {0, 0, 0, 0, 0, 0, 0}, "pKa", false},
            {"\\text{pK}_b", {0, 0, 0, 0, 0, 0, 0}, "pKb", false}
        },
        "Chemistry - Acids & Bases",
        "pKa and pKb Relationship",
        "\\text{pK}_a"
    });
    
    formulas.push_back({
        "pKa and pKb Relationship (solve for pK_b)",
        "\\text{pK}_b = 14 - \\text{pK}_a",
        {
            {"\\text{pK}_b", {0, 0, 0, 0, 0, 0, 0}, "pKb", false},
            {"\\text{pK}_a", {0, 0, 0, 0, 0, 0, 0}, "pKa", false}
        },
        "Chemistry - Acids & Bases",
        "pKa and pKb Relationship",
        "\\text{pK}_b"
    });
    
    // ========================================================================
    // HENDERSON-HASSELBALCH EQUATION: pH = pK_a + log([A-]/[HA])
    // ========================================================================
    
    formulas.push_back({
        "Henderson-Hasselbalch (solve for pH)",
        "\\text{pH} = \\text{pK}_a + \\log\\frac{[A^-]}{[HA]}",
        {
            {"\\text{pH}", {0, 0, 0, 0, 0, 0, 0}, "pH", false},
            {"\\text{pK}_a", {0, 0, 0, 0, 0, 0, 0}, "pKa", false},
            {"[A^-]", {-3, 0, 0, 0, 0, 1, 0}, "Conjugate base concentration", false},
            {"[HA]", {-3, 0, 0, 0, 0, 1, 0}, "Weak acid concentration", false}
        },
        "Chemistry - Acids & Bases",
        "Henderson-Hasselbalch",
        "\\text{pH}"
    });
}

} // namespace Physics
