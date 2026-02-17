#include "dimeval.hpp"
#include <string>

namespace dv {
    std::string unit_to_latex(const UnitVector &unit);
    std::string value_to_scientific(const long double &value);
}