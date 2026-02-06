#include "builtins.hpp"
#include <cmath>

dv::EValue dv::builtins::ln(double value){
    if (value <= 0) return std::nan("");
    return std::log(value);
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
    if (value <= 0 || base <= 0 || base == 1) {
        return std::nan("");
    }
    if(base == 10) return std::log10(value);
    return std::log(value) / std::log(base);
}
dv::EValue dv::builtins::abs(dv::EValue value){
    return value.abs();
}
dv::EValue dv::builtins::nCr(double n, double r){
    if (r < 0 || r > n) return 0;
    if (r > n - r) r = n - r;

    std::int64_t result = 1;
    for (int i = 1; i <= r; ++i) {
        result = result * (n - i + 1);
        result = result / i;
    }
    return result;
}
dv::EValue dv::builtins::nPr(double n, double r){
    if (r < 0 || r > n) return 0;
    std::int64_t result = 1;
    for (int i = 0; i < r; ++i) {
        result *= (n - i);
    }
    return result;
}
dv::EValue dv::builtins::nthsqrt(dv::EValue value, double n){
    return value ^ (1.0 / n);
}
dv::EValue dv::builtins::ceil(dv::EValue value){
    return {std::ceil(value.value), value.unit};
}
dv::EValue dv::builtins::factorial(dv::EValue value){
    return value.fact();
}
dv::EValue dv::builtins::floor(dv::EValue value){
    return {std::floor(value.value), value.unit};
}
dv::EValue dv::builtins::round(dv::EValue value, double place){
    const double multiplier = std::pow(10.0, place);
    return {std::round(value.value * multiplier) / multiplier, value.unit};
}
dv::EValue dv::builtins::arcsin(double value){
    return std::asin(value);
}
dv::EValue dv::builtins::arccos(double value){
    return std::acos(value);
}
dv::EValue dv::builtins::arctan(double value){
    return std::atan(value);
}
dv::EValue dv::builtins::arcsec(double value){
    return 1.0 / std::acos(value);
}
dv::EValue dv::builtins::arccsc(double value){
    return 1.0 / std::asin(value);
}
dv::EValue dv::builtins::arccot(double value){
    return 1.0 / std::atan(value);
}