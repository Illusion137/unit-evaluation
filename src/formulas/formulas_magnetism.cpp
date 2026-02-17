#include "physics_formulas.hpp"

namespace Physics {

void FormulaDatabase::initialize_magnetism() {
    
    // ========================================================================
    // MAGNETIC FORCE ON MOVING CHARGE: F = q * v * B (perpendicular)
    // ========================================================================
    
    formulas.push_back({
        "Magnetic Force on Charge (solve for F)",
        "F = qvB",
        {
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false}
        },
        "Magnetism",
        "Magnetic Force on Charge",
        "F"
    });
    
    formulas.push_back({
        "Magnetic Force on Charge (solve for q)",
        "q = \\frac{F}{vB}",
        {
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false}
        },
        "Magnetism",
        "Magnetic Force on Charge",
        "q"
    });
    
    formulas.push_back({
        "Magnetic Force on Charge (solve for v)",
        "v = \\frac{F}{qB}",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false}
        },
        "Magnetism",
        "Magnetic Force on Charge",
        "v"
    });
    
    formulas.push_back({
        "Magnetic Force on Charge (solve for B)",
        "B = \\frac{F}{qv}",
        {
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false}
        },
        "Magnetism",
        "Magnetic Force on Charge",
        "B"
    });
    
    // ========================================================================
    // MAGNETIC FORCE ON CURRENT: F = B * I * L
    // ========================================================================
    
    formulas.push_back({
        "Magnetic Force on Current (solve for F)",
        "F = BIL",
        {
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"L", {1, 0, 0, 0, 0, 0, 0}, "Length", false}
        },
        "Magnetism",
        "Magnetic Force on Current",
        "F"
    });
    
    formulas.push_back({
        "Magnetic Force on Current (solve for B)",
        "B = \\frac{F}{IL}",
        {
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"L", {1, 0, 0, 0, 0, 0, 0}, "Length", false}
        },
        "Magnetism",
        "Magnetic Force on Current",
        "B"
    });
    
    formulas.push_back({
        "Magnetic Force on Current (solve for I)",
        "I = \\frac{F}{BL}",
        {
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"L", {1, 0, 0, 0, 0, 0, 0}, "Length", false}
        },
        "Magnetism",
        "Magnetic Force on Current",
        "I"
    });
    
    formulas.push_back({
        "Magnetic Force on Current (solve for L)",
        "L = \\frac{F}{BI}",
        {
            {"L", {1, 0, 0, 0, 0, 0, 0}, "Length", false},
            {"F", {1, -2, 1, 0, 0, 0, 0}, "Force", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false}
        },
        "Magnetism",
        "Magnetic Force on Current",
        "L"
    });
    
    // ========================================================================
    // MAGNETIC FIELD OF STRAIGHT WIRE: B = (mu_0 * I) / (2 * pi * r)
    // ========================================================================
    
    formulas.push_back({
        "Magnetic Field of Wire (solve for B)",
        "B = \\frac{\\mu_0 I}{2\\pi r}",
        {
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false}
        },
        "Magnetism",
        "Magnetic Field of Wire",
        "B"
    });
    
    formulas.push_back({
        "Magnetic Field of Wire (solve for I)",
        "I = \\frac{2\\pi r B}{\\mu_0}",
        {
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true}
        },
        "Magnetism",
        "Magnetic Field of Wire",
        "I"
    });
    
    formulas.push_back({
        "Magnetic Field of Wire (solve for r)",
        "r = \\frac{\\mu_0 I}{2\\pi B}",
        {
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false}
        },
        "Magnetism",
        "Magnetic Field of Wire",
        "r"
    });
    
    // ========================================================================
    // MAGNETIC FIELD OF SOLENOID: B = mu_0 * n * I
    // ========================================================================
    
    formulas.push_back({
        "Magnetic Field of Solenoid (solve for B)",
        "B = \\mu_0 n I",
        {
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true},
            {"n", {-1, 0, 0, 0, 0, 0, 0}, "Turns per unit length", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false}
        },
        "Magnetism",
        "Magnetic Field of Solenoid",
        "B"
    });
    
    formulas.push_back({
        "Magnetic Field of Solenoid (solve for n)",
        "n = \\frac{B}{\\mu_0 I}",
        {
            {"n", {-1, 0, 0, 0, 0, 0, 0}, "Turns per unit length", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false}
        },
        "Magnetism",
        "Magnetic Field of Solenoid",
        "n"
    });
    
    formulas.push_back({
        "Magnetic Field of Solenoid (solve for I)",
        "I = \\frac{B}{\\mu_0 n}",
        {
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true},
            {"n", {-1, 0, 0, 0, 0, 0, 0}, "Turns per unit length", false}
        },
        "Magnetism",
        "Magnetic Field of Solenoid",
        "I"
    });
    
    // ========================================================================
    // CYCLOTRON RADIUS: r = (m * v) / (q * B)
    // ========================================================================
    
    formulas.push_back({
        "Cyclotron Radius (solve for r)",
        "r = \\frac{mv}{qB}",
        {
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false}
        },
        "Magnetism",
        "Cyclotron Radius",
        "r"
    });
    
    formulas.push_back({
        "Cyclotron Radius (solve for m)",
        "m = \\frac{rqB}{v}",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false}
        },
        "Magnetism",
        "Cyclotron Radius",
        "m"
    });
    
    formulas.push_back({
        "Cyclotron Radius (solve for v)",
        "v = \\frac{rqB}{m}",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false}
        },
        "Magnetism",
        "Cyclotron Radius",
        "v"
    });
    
    formulas.push_back({
        "Cyclotron Radius (solve for q)",
        "q = \\frac{mv}{rB}",
        {
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false}
        },
        "Magnetism",
        "Cyclotron Radius",
        "q"
    });
    
    formulas.push_back({
        "Cyclotron Radius (solve for B)",
        "B = \\frac{mv}{qr}",
        {
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius", false}
        },
        "Magnetism",
        "Cyclotron Radius",
        "B"
    });
    
    // ========================================================================
    // MAGNETIC FLUX: Phi = B * A * cos(theta)
    // For perpendicular: Phi = B * A
    // ========================================================================
    
    formulas.push_back({
        "Magnetic Flux (solve for Phi)",
        "\\Phi = BA",
        {
            {"\\Phi", {2, -2, 1, -1, 0, 0, 0}, "Magnetic flux", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area", false}
        },
        "Magnetism",
        "Magnetic Flux",
        "\\Phi"
    });
    
    formulas.push_back({
        "Magnetic Flux (solve for B)",
        "B = \\frac{\\Phi}{A}",
        {
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"\\Phi", {2, -2, 1, -1, 0, 0, 0}, "Magnetic flux", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area", false}
        },
        "Magnetism",
        "Magnetic Flux",
        "B"
    });
    
    formulas.push_back({
        "Magnetic Flux (solve for A)",
        "A = \\frac{\\Phi}{B}",
        {
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area", false},
            {"\\Phi", {2, -2, 1, -1, 0, 0, 0}, "Magnetic flux", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false}
        },
        "Magnetism",
        "Magnetic Flux",
        "A"
    });
    
    // ========================================================================
    // CYCLOTRON FREQUENCY: f = (q * B) / (2 * pi * m)
    // ========================================================================
    
    formulas.push_back({
        "Cyclotron Frequency (solve for f)",
        "f = \\frac{qB}{2\\pi m}",
        {
            {"f", {0, -1, 0, 0, 0, 0, 0}, "Frequency", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false}
        },
        "Magnetism",
        "Cyclotron Frequency",
        "f"
    });
    
    formulas.push_back({
        "Cyclotron Frequency (solve for q)",
        "q = \\frac{2\\pi m f}{B}",
        {
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"f", {0, -1, 0, 0, 0, 0, 0}, "Frequency", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false}
        },
        "Magnetism",
        "Cyclotron Frequency",
        "q"
    });
    
    formulas.push_back({
        "Cyclotron Frequency (solve for B)",
        "B = \\frac{2\\pi m f}{q}",
        {
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"f", {0, -1, 0, 0, 0, 0, 0}, "Frequency", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false}
        },
        "Magnetism",
        "Cyclotron Frequency",
        "B"
    });
    
    formulas.push_back({
        "Cyclotron Frequency (solve for m)",
        "m = \\frac{qB}{2\\pi f}",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"f", {0, -1, 0, 0, 0, 0, 0}, "Frequency", false}
        },
        "Magnetism",
        "Cyclotron Frequency",
        "m"
    });
    // ========================================================================
    // MAGNETIC ENERGY DENSITY: u = B^2 / (2 * mu_0)
    // ========================================================================
    
    formulas.push_back({
        "Magnetic Energy Density (solve for u)",
        "u = \\frac{B^2}{2\\mu_0}",
        {
            {"u", {-1, -2, 1, 0, 0, 0, 0}, "Energy density", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true}
        },
        "Magnetism",
        "Magnetic Energy Density",
        "u"
    });
    
    formulas.push_back({
        "Magnetic Energy Density (solve for B)",
        "B = \\sqrt{2\\mu_0 u}",
        {
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true},
            {"u", {-1, -2, 1, 0, 0, 0, 0}, "Energy density", false}
        },
        "Magnetism",
        "Magnetic Energy Density",
        "B"
    });
    
    // ========================================================================
    // HALL EFFECT: V_H = (I * B) / (n * q * t)
    // ========================================================================
    
    formulas.push_back({
        "Hall Voltage (solve for V_H)",
        "V_H = \\frac{IB}{nqt}",
        {
            {"V_H", {2, -3, 1, -1, 0, 0, 0}, "Hall voltage", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"n", {-3, 0, 0, 0, 0, 0, 0}, "Charge carrier density", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge per carrier", false},
            {"t", {1, 0, 0, 0, 0, 0, 0}, "Thickness", false}
        },
        "Magnetism",
        "Hall Voltage",
        "V_H"
    });
    
    formulas.push_back({
        "Hall Voltage (solve for n)",
        "n = \\frac{IB}{qV_H t}",
        {
            {"n", {-3, 0, 0, 0, 0, 0, 0}, "Charge carrier density", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge per carrier", false},
            {"V_H", {2, -3, 1, -1, 0, 0, 0}, "Hall voltage", false},
            {"t", {1, 0, 0, 0, 0, 0, 0}, "Thickness", false}
        },
        "Magnetism",
        "Hall Voltage",
        "n"
    });
    
    formulas.push_back({
        "Hall Voltage (solve for B)",
        "B = \\frac{nqV_H t}{I}",
        {
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"n", {-3, 0, 0, 0, 0, 0, 0}, "Charge carrier density", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge per carrier", false},
            {"V_H", {2, -3, 1, -1, 0, 0, 0}, "Hall voltage", false},
            {"t", {1, 0, 0, 0, 0, 0, 0}, "Thickness", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false}
        },
        "Magnetism",
        "Hall Voltage",
        "B"
    });
    
    // ========================================================================
    // AMPERE'S LAW (FOR STRAIGHT WIRE): B * 2*pi*r = mu_0 * I
    // Already covered in "Magnetic Field of Wire", but adding enclosed current form
    // ========================================================================
    
    formulas.push_back({
        "Ampere's Law for Circular Path (solve for B)",
        "B = \\frac{\\mu_0 I_{enc}}{2\\pi r}",
        {
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true},
            {"I_{enc}", {0, 0, 0, 1, 0, 0, 0}, "Enclosed current", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance from wire", false}
        },
        "Magnetism",
        "Ampere's Law for Circular Path",
        "B"
    });
    
    formulas.push_back({
        "Ampere's Law for Circular Path (solve for I_enc)",
        "I_{enc} = \\frac{2\\pi r B}{\\mu_0}",
        {
            {"I_{enc}", {0, 0, 0, 1, 0, 0, 0}, "Enclosed current", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance from wire", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true}
        },
        "Magnetism",
        "Ampere's Law for Circular Path",
        "I_{enc}"
    });
    
    // ========================================================================
    // MAGNETIC DIPOLE MOMENT: mu = I * A
    // ========================================================================
    
    formulas.push_back({
        "Magnetic Dipole Moment (solve for mu)",
        "\\mu = IA",
        {
            {"\\mu", {2, 0, 0, 1, 0, 0, 0}, "Magnetic dipole moment", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area of loop", false}
        },
        "Magnetism",
        "Magnetic Dipole Moment",
        "\\mu"
    });
    
    formulas.push_back({
        "Magnetic Dipole Moment (solve for I)",
        "I = \\frac{\\mu}{A}",
        {
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"\\mu", {2, 0, 0, 1, 0, 0, 0}, "Magnetic dipole moment", false},
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area of loop", false}
        },
        "Magnetism",
        "Magnetic Dipole Moment",
        "I"
    });
    
    formulas.push_back({
        "Magnetic Dipole Moment (solve for A)",
        "A = \\frac{\\mu}{I}",
        {
            {"A", {2, 0, 0, 0, 0, 0, 0}, "Area of loop", false},
            {"\\mu", {2, 0, 0, 1, 0, 0, 0}, "Magnetic dipole moment", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false}
        },
        "Magnetism",
        "Magnetic Dipole Moment",
        "A"
    });
    
    // ========================================================================
    // TORQUE ON MAGNETIC DIPOLE: tau = mu * B * sin(theta)
    // For perpendicular: tau = mu * B
    // ========================================================================
    
    formulas.push_back({
        "Torque on Magnetic Dipole (solve for tau)",
        "\\tau = \\mu B",
        {
            {"\\tau", {2, -2, 1, 0, 0, 0, 0}, "Torque", false},
            {"\\mu", {2, 0, 0, 1, 0, 0, 0}, "Magnetic dipole moment", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false}
        },
        "Magnetism",
        "Torque on Magnetic Dipole",
        "\\tau"
    });
    
    formulas.push_back({
        "Torque on Magnetic Dipole (solve for mu)",
        "\\mu = \\frac{\\tau}{B}",
        {
            {"\\mu", {2, 0, 0, 1, 0, 0, 0}, "Magnetic dipole moment", false},
            {"\\tau", {2, -2, 1, 0, 0, 0, 0}, "Torque", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false}
        },
        "Magnetism",
        "Torque on Magnetic Dipole",
        "\\mu"
    });
    
    formulas.push_back({
        "Torque on Magnetic Dipole (solve for B)",
        "B = \\frac{\\tau}{\\mu}",
        {
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"\\tau", {2, -2, 1, 0, 0, 0, 0}, "Torque", false},
            {"\\mu", {2, 0, 0, 1, 0, 0, 0}, "Magnetic dipole moment", false}
        },
        "Magnetism",
        "Torque on Magnetic Dipole",
        "B"
    });
    
    // ========================================================================
    // POTENTIAL ENERGY OF MAGNETIC DIPOLE: U = -mu * B * cos(theta)
    // For perpendicular: U = -mu * B
    // ========================================================================
    
    formulas.push_back({
        "Magnetic Dipole Potential Energy (solve for U)",
        "U = -\\mu B",
        {
            {"U", {2, -2, 1, 0, 0, 0, 0}, "Potential energy", false},
            {"\\mu", {2, 0, 0, 1, 0, 0, 0}, "Magnetic dipole moment", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false}
        },
        "Magnetism",
        "Magnetic Dipole Potential Energy",
        "U"
    });
    
    // ========================================================================
    // FORCE BETWEEN PARALLEL CURRENTS: F/L = (mu_0 * I_1 * I_2) / (2 * pi * d)
    // ========================================================================
    
    formulas.push_back({
        "Force Between Parallel Currents (solve for F/L)",
        "\\frac{F}{L} = \\frac{\\mu_0 I_1 I_2}{2\\pi d}",
        {
            {"F/L", {0, -2, 1, 0, 0, 0, 0}, "Force per unit length", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true},
            {"I_1", {0, 0, 0, 1, 0, 0, 0}, "Current 1", false},
            {"I_2", {0, 0, 0, 1, 0, 0, 0}, "Current 2", false},
            {"d", {1, 0, 0, 0, 0, 0, 0}, "Separation distance", false}
        },
        "Magnetism",
        "Force Between Parallel Currents",
        "F/L"
    });
    
    formulas.push_back({
        "Force Between Parallel Currents (solve for d)",
        "d = \\frac{\\mu_0 I_1 I_2}{2\\pi F/L}",
        {
            {"d", {1, 0, 0, 0, 0, 0, 0}, "Separation distance", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true},
            {"I_1", {0, 0, 0, 1, 0, 0, 0}, "Current 1", false},
            {"I_2", {0, 0, 0, 1, 0, 0, 0}, "Current 2", false},
            {"F/L", {0, -2, 1, 0, 0, 0, 0}, "Force per unit length", false}
        },
        "Magnetism",
        "Force Between Parallel Currents",
        "d"
    });
    
    // ========================================================================
    // MAGNETIC FIELD AT CENTER OF CIRCULAR LOOP: B = (mu_0 * I) / (2 * r)
    // ========================================================================
    
    formulas.push_back({
        "Magnetic Field at Center of Loop (solve for B)",
        "B = \\frac{\\mu_0 I}{2r}",
        {
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius of loop", false}
        },
        "Magnetism",
        "Magnetic Field at Center of Loop",
        "B"
    });
    
    formulas.push_back({
        "Magnetic Field at Center of Loop (solve for I)",
        "I = \\frac{2rB}{\\mu_0}",
        {
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius of loop", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true}
        },
        "Magnetism",
        "Magnetic Field at Center of Loop",
        "I"
    });
    
    formulas.push_back({
        "Magnetic Field at Center of Loop (solve for r)",
        "r = \\frac{\\mu_0 I}{2B}",
        {
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius of loop", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false}
        },
        "Magnetism",
        "Magnetic Field at Center of Loop",
        "r"
    });
    
    // ========================================================================
    // BIOT-SAVART LAW (for small current element): dB = (mu_0 * I * dl * sin(theta)) / (4 * pi * r^2)
    // Conceptual formula
    // ========================================================================
    
    formulas.push_back({
        "Biot-Savart Law (conceptual)",
        "dB = \\frac{\\mu_0 I dl \\sin\\theta}{4\\pi r^2}",
        {
            {"dB", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field element", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"dl", {1, 0, 0, 0, 0, 0, 0}, "Current element length", false},
            {"\\theta", {0, 0, 0, 0, 0, 0, 0}, "Angle", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Distance", false}
        },
        "Magnetism",
        "Biot-Savart Law",
        "dB"
    });
    
    // ========================================================================
    // CYCLOTRON PERIOD: T = (2 * pi * m) / (q * B)
    // ========================================================================
    
    formulas.push_back({
        "Cyclotron Period (solve for T)",
        "T = \\frac{2\\pi m}{qB}",
        {
            {"T", {0, 1, 0, 0, 0, 0, 0}, "Period", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false}
        },
        "Magnetism",
        "Cyclotron Period",
        "T"
    });
    
    formulas.push_back({
        "Cyclotron Period (solve for m)",
        "m = \\frac{TqB}{2\\pi}",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"T", {0, 1, 0, 0, 0, 0, 0}, "Period", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false}
        },
        "Magnetism",
        "Cyclotron Period",
        "m"
    });
    
    formulas.push_back({
        "Cyclotron Period (solve for B)",
        "B = \\frac{2\\pi m}{qT}",
        {
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"T", {0, 1, 0, 0, 0, 0, 0}, "Period", false}
        },
        "Magnetism",
        "Cyclotron Period",
        "B"
    });
    
    // ========================================================================
    // MAGNETIC FIELD INSIDE TOROID: B = (mu_0 * N * I) / (2 * pi * r)
    // ========================================================================
    
    formulas.push_back({
        "Magnetic Field in Toroid (solve for B)",
        "B = \\frac{\\mu_0 N I}{2\\pi r}",
        {
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true},
            {"N", {0, 0, 0, 0, 0, 0, 0}, "Total number of turns", false},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius to point", false}
        },
        "Magnetism",
        "Magnetic Field in Toroid",
        "B"
    });
    
    formulas.push_back({
        "Magnetic Field in Toroid (solve for N)",
        "N = \\frac{2\\pi r B}{\\mu_0 I}",
        {
            {"N", {0, 0, 0, 0, 0, 0, 0}, "Total number of turns", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius to point", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true},
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false}
        },
        "Magnetism",
        "Magnetic Field in Toroid",
        "N"
    });
    
    formulas.push_back({
        "Magnetic Field in Toroid (solve for I)",
        "I = \\frac{2\\pi r B}{\\mu_0 N}",
        {
            {"I", {0, 0, 0, 1, 0, 0, 0}, "Current", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius to point", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"\\mu_0", {1, -2, 1, -2, 0, 0, 0}, "Permeability of free space", true},
            {"N", {0, 0, 0, 0, 0, 0, 0}, "Total number of turns", false}
        },
        "Magnetism",
        "Magnetic Field in Toroid",
        "I"
    });
    
    // ========================================================================
    // VELOCITY SELECTOR: E = v * B (for particles passing through undeflected)
    // ========================================================================
    
    formulas.push_back({
        "Velocity Selector (solve for v)",
        "v = \\frac{E}{B}",
        {
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false}
        },
        "Magnetism",
        "Velocity Selector",
        "v"
    });
    
    formulas.push_back({
        "Velocity Selector (solve for E)",
        "E = vB",
        {
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false}
        },
        "Magnetism",
        "Velocity Selector",
        "E"
    });
    
    formulas.push_back({
        "Velocity Selector (solve for B)",
        "B = \\frac{E}{v}",
        {
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"E", {1, -3, 1, -1, 0, 0, 0}, "Electric field", false},
            {"v", {1, -1, 0, 0, 0, 0, 0}, "Velocity", false}
        },
        "Magnetism",
        "Velocity Selector",
        "B"
    });
    
    // ========================================================================
    // MASS SPECTROMETER: m = (q * B^2 * r^2) / (2 * V)
    // ========================================================================
    
    formulas.push_back({
        "Mass Spectrometer (solve for m)",
        "m = \\frac{qB^2 r^2}{2V}",
        {
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius of path", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Accelerating voltage", false}
        },
        "Magnetism",
        "Mass Spectrometer",
        "m"
    });
    
    formulas.push_back({
        "Mass Spectrometer (solve for r)",
        "r = \\sqrt{\\frac{2mV}{qB^2}}",
        {
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius of path", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Accelerating voltage", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false}
        },
        "Magnetism",
        "Mass Spectrometer",
        "r"
    });
    
    formulas.push_back({
        "Mass Spectrometer (solve for B)",
        "B = \\sqrt{\\frac{2mV}{qr^2}}",
        {
            {"B", {0, -2, 1, -1, 0, 0, 0}, "Magnetic field", false},
            {"m", {0, 0, 1, 0, 0, 0, 0}, "Mass", false},
            {"V", {2, -3, 1, -1, 0, 0, 0}, "Accelerating voltage", false},
            {"q", {0, 1, 0, 1, 0, 0, 0}, "Charge", false},
            {"r", {1, 0, 0, 0, 0, 0, 0}, "Radius of path", false}
        },
        "Magnetism",
        "Mass Spectrometer",
        "B"
    });
}

} // namespace Physics
    
