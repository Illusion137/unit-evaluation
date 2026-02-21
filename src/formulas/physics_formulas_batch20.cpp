#include "physics_formulas.hpp"

namespace Physics {
    void FormulaDatabase::batch_20() {
		this->formulas.emplace_back("Doppler Effect Moving Source", "f_s = \\frac{f_obs}{\\frac{v}{v \\pm v_s}}", std::vector<Variable>{{"f_{obs}", {0, -1, 0, 0, 0, 0, 0}, "Observed frequency", false},{"f_s", {0, -1, 0, 0, 0, 0, 0}, "Source frequency", false},{"v", {1, -1, 0, 0, 0, 0, 0}, "Wave velocity", false},{"v_s", {1, -1, 0, 0, 0, 0, 0}, "Source velocity", false}}, "f_s");
    }
} // namespace Physics
