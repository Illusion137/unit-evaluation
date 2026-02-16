#include "physics_formulas.hpp"

namespace Physics {

FormulaDatabase::FormulaDatabase() {
    // Initialize all formula categories
    // Each function is implemented in its own cpp file
    initialize_electrostatics();
    initialize_circuits();
    initialize_magnetism();
    initialize_induction();
    initialize_electromagnetic_waves();
    initialize_kinematics();
    initialize_dynamics();
    initialize_circular_motion();
    initialize_gravity();
    initialize_energy();
    initialize_momentum();
    initialize_rotational_mechanics();
    initialize_oscillations();
    initialize_waves();
    initialize_fluids();
    initialize_thermodynamics();
    initialize_optics();
    initialize_modern_physics();
    initialize_chemistry_basic();
    initialize_chemistry_solutions();
    initialize_chemistry_kinetics();
    initialize_chemistry_equilibrium();
    initialize_chemistry_acids_bases();
    initialize_chemistry_thermochemistry();
    initialize_chemistry_electrochemistry();
}

} // namespace Physics
