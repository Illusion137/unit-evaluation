#include "builtins.hpp"
#include <cmath>

dv::EValue dv::builtins::ln(double value){
    // return std::log(value);
    return 0.0;
}
dv::EValue dv::builtins::sin(double value){
    return std::sin(value);
}
dv::EValue dv::builtins::cos(double value){
    return std::cos(value);
}
dv::EValue dv::builtins::tan(double value){
    return std::tan(value);
}
dv::EValue dv::builtins::sec(double value){
    return 1.0 / std::cos(value);
}
dv::EValue dv::builtins::csc(double value){
    return 1.0 / std::sin(value);
}
dv::EValue dv::builtins::cot(double value){
    return 1.0 / std::tan(value);
}
dv::EValue dv::builtins::log(double value, std::int32_t base){
    // return std::log10(value);
    return 0.0;
}
dv::EValue dv::builtins::abs(dv::EValue value){
    return {std::fabs(value.value), value.unit};
}
dv::EValue dv::builtins::nCr(double n, double r){
    return 0.0;
}
dv::EValue dv::builtins::nPr(double n, double r){
    return 0.0;
}
dv::EValue dv::builtins::nthsqrt(dv::EValue value, double n){
    return 0.0;
}
dv::EValue dv::builtins::ceil(dv::EValue value){
    return 0.0;
}
dv::EValue dv::builtins::factorial(double value){
    return 0.0;
}
dv::EValue dv::builtins::floor(dv::EValue value){
    return 0.0;
}
dv::EValue dv::builtins::round(dv::EValue value, double place){
    return 0.0;
}
dv::EValue dv::builtins::arcsin(double value){
    return 0.0;
}
dv::EValue dv::builtins::arccos(double value){
    return 0.0;
}
dv::EValue dv::builtins::arctan(double value){
    return 0.0;
}
dv::EValue dv::builtins::arcsec(double value){
    return 0.0;
}
dv::EValue dv::builtins::arccsc(double value){
    return 0.0;
}
dv::EValue dv::builtins::arccot(double value){
    return 0.0;
}