#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_optics() {
    
    // ========================================================================
    // SNELL'S LAW: n_1 * sin(theta_1) = n_2 * sin(theta_2)
    // ========================================================================
    
    formulas.push_back({
        "Snell's Law (relationship)",
        "n_1 \\sin\\theta_1 = n_2 \\sin\\theta_2",
        {
            {"n_1", {0, 0, 0, 0, 0, 0, 0}, "Index of refraction 1", false},
            {"\\theta_1", {0, 0, 0, 0, 0, 0, 0}, "Angle 1", false},
            {"n_2", {0, 0, 0, 0, 0, 0, 0}, "Index of refraction 2", false},
            {"\\theta_2", {0, 0, 0, 0, 0, 0, 0}, "Angle 2", false}
        },
        "Optics",
        "Snell's Law",
        "relationship"
    });
    
    // ========================================================================
    // THIN LENS EQUATION: 1/f = 1/d_o + 1/d_i
    // ========================================================================
    
    formulas.push_back({
        "Thin Lens Equation (relationship)",
        "\\frac{1}{f} = \\frac{1}{d_o} + \\frac{1}{d_i}",
        {
            {"f", {1, 0, 0, 0, 0, 0, 0}, "Focal length", false},
            {"d_o", {1, 0, 0, 0, 0, 0, 0}, "Object distance", false},
            {"d_i", {1, 0, 0, 0, 0, 0, 0}, "Image distance", false}
        },
        "Optics",
        "Thin Lens Equation",
        "relationship"
    });
    
    // ========================================================================
    // MAGNIFICATION: m = -d_i / d_o
    // ========================================================================
    
    formulas.push_back({
        "Magnification (solve for m)",
        "m = -\\frac{d_i}{d_o}",
        {
            {"m", {0, 0, 0, 0, 0, 0, 0}, "Magnification", false},
            {"d_i", {1, 0, 0, 0, 0, 0, 0}, "Image distance", false},
            {"d_o", {1, 0, 0, 0, 0, 0, 0}, "Object distance", false}
        },
        "Optics",
        "Magnification",
        "m"
    });
    
    formulas.push_back({
        "Magnification (solve for d_i)",
        "d_i = -m d_o",
        {
            {"d_i", {1, 0, 0, 0, 0, 0, 0}, "Image distance", false},
            {"m", {0, 0, 0, 0, 0, 0, 0}, "Magnification", false},
            {"d_o", {1, 0, 0, 0, 0, 0, 0}, "Object distance", false}
        },
        "Optics",
        "Magnification",
        "d_i"
    });
    
    formulas.push_back({
        "Magnification (solve for d_o)",
        "d_o = -\\frac{d_i}{m}",
        {
            {"d_o", {1, 0, 0, 0, 0, 0, 0}, "Object distance", false},
            {"d_i", {1, 0, 0, 0, 0, 0, 0}, "Image distance", false},
            {"m", {0, 0, 0, 0, 0, 0, 0}, "Magnification", false}
        },
        "Optics",
        "Magnification",
        "d_o"
    });
    
    // ========================================================================
    // MAGNIFICATION HEIGHT: m = h_i / h_o
    // ========================================================================
    
    formulas.push_back({
        "Magnification from Height (solve for m)",
        "m = \\frac{h_i}{h_o}",
        {
            {"m", {0, 0, 0, 0, 0, 0, 0}, "Magnification", false},
            {"h_i", {1, 0, 0, 0, 0, 0, 0}, "Image height", false},
            {"h_o", {1, 0, 0, 0, 0, 0, 0}, "Object height", false}
        },
        "Optics",
        "Magnification from Height",
        "m"
    });
    
    formulas.push_back({
        "Magnification from Height (solve for h_i)",
        "h_i = m h_o",
        {
            {"h_i", {1, 0, 0, 0, 0, 0, 0}, "Image height", false},
            {"m", {0, 0, 0, 0, 0, 0, 0}, "Magnification", false},
            {"h_o", {1, 0, 0, 0, 0, 0, 0}, "Object height", false}
        },
        "Optics",
        "Magnification from Height",
        "h_i"
    });
    
    formulas.push_back({
        "Magnification from Height (solve for h_o)",
        "h_o = \\frac{h_i}{m}",
        {
            {"h_o", {1, 0, 0, 0, 0, 0, 0}, "Object height", false},
            {"h_i", {1, 0, 0, 0, 0, 0, 0}, "Image height", false},
            {"m", {0, 0, 0, 0, 0, 0, 0}, "Magnification", false}
        },
        "Optics",
        "Magnification from Height",
        "h_o"
    });
    
    // ========================================================================
    // INDEX OF REFRACTION: n = c / v
    // ========================================================================
    
    formulas.push_back({
        "Index of Refraction (solve for n)",
        "n = \\frac{c}{v}",
        {
            {"n", {0, 0, 0, 0, 0, 0, 0}, "Index of refraction", false},
            {"c", {1, -1, 0, 0, 0, 0, 0}, "Speed of light in vacuum", true},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Speed of light in medium", false}
        },
        "Optics",
        "Index of Refraction",
        "n"
    });
    
    formulas.push_back({
        "Index of Refraction (solve for v)",
        "v = \\frac{c}{n}",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Speed of light in medium", false},
            {"c", {1, -1, 0, 0, 0, 0, 0}, "Speed of light in vacuum", true},
            {"n", {0, 0, 0, 0, 0, 0, 0}, "Index of refraction", false}
        },
        "Optics",
        "Index of Refraction",
        "v"
    });
}

} // namespace Physics
