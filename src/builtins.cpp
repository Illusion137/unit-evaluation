#include "builtins.hpp"
#include <cmath>

// ============================================================================
// Complex-aware scalar functions
// ============================================================================

dv::UnitValue dv::builtins::ln(UnitValue val) {
    if(val.is_complex()) {
        // ln(a+bi) = ln(r) + i*arg(z)
        double r = std::hypot((double)val.value, (double)val.imag);
        double theta = std::atan2((double)val.imag, (double)val.value);
        return {(long double)std::log(r), (long double)theta, dv::UnitVector{dv::DIMENSIONLESS_VEC}};
    }
    if(val.value <= 0) return {(long double)std::numeric_limits<double>::quiet_NaN()};
    return {(long double)std::log((double)val.value)};
}

dv::UnitValue dv::builtins::sin(UnitValue val) {
    if(val.is_complex()) {
        // sin(a+bi) = sin(a)*cosh(b) + i*cos(a)*sinh(b)
        double a = (double)val.value, b = (double)val.imag;
        return {(long double)(std::sin(a) * std::cosh(b)),
                (long double)(std::cos(a) * std::sinh(b)),
                dv::UnitVector{dv::DIMENSIONLESS_VEC}};
    }
    return {(long double)std::sin((double)val.value)};
}

dv::UnitValue dv::builtins::cos(UnitValue val) {
    if(val.is_complex()) {
        // cos(a+bi) = cos(a)*cosh(b) - i*sin(a)*sinh(b)
        double a = (double)val.value, b = (double)val.imag;
        return {(long double)(std::cos(a) * std::cosh(b)),
                (long double)(-std::sin(a) * std::sinh(b)),
                dv::UnitVector{dv::DIMENSIONLESS_VEC}};
    }
    return {(long double)std::cos((double)val.value)};
}

dv::UnitValue dv::builtins::tan(UnitValue val) {
    if(val.is_complex()) {
        // tan(z) = sin(z) / cos(z)
        auto s = sin(val);
        auto c = cos(val);
        return s / c;
    }
    return {(long double)std::tan((double)val.value)};
}

dv::EValue dv::builtins::sec(double value) {
    return dv::UnitValue{1.0L / (long double)std::cos(value)};
}
dv::EValue dv::builtins::csc(double value) {
    return dv::UnitValue{1.0L / (long double)std::sin(value)};
}
dv::EValue dv::builtins::cot(double value) {
    return dv::UnitValue{1.0L / (long double)std::tan(value)};
}
dv::EValue dv::builtins::log(double value, std::int32_t base) {
    if(value <= 0 || base <= 0 || base == 1)
        return dv::UnitValue{(long double)std::numeric_limits<double>::quiet_NaN()};
    if(base == 10) return dv::UnitValue{(long double)std::log10(value)};
    return dv::UnitValue{(long double)(std::log(value) / std::log((double)base))};
}
dv::EValue dv::builtins::abs(dv::EValue value) {
    return dv::evalue_abs(value);
}
dv::EValue dv::builtins::nCr(double n, double r) {
    if(r < 0 || r > n) return dv::UnitValue{0.0L};
    if(r > n - r) r = n - r;
    std::int64_t result = 1;
    for(int i = 1; i <= (int)r; ++i) {
        result = result * (long long)(n - i + 1);
        result = result / i;
    }
    return dv::UnitValue{(long double)result};
}
dv::EValue dv::builtins::nPr(double n, double r) {
    if(r < 0 || r > n) return dv::UnitValue{0.0L};
    std::int64_t result = 1;
    for(int i = 0; i < (int)r; ++i) result *= (long long)(n - i);
    return dv::UnitValue{(long double)result};
}
dv::EValue dv::builtins::nthsqrt(dv::EValue value, double n) {
    return value ^ dv::EValue{dv::UnitValue{1.0L / (long double)n}};
}
dv::EValue dv::builtins::ceil(dv::EValue value) {
    return std::visit([](const auto &v) -> dv::EValue {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, dv::UnitValue>)
            return dv::UnitValue{(long double)std::ceil((double)v.value), v.unit};
        else if constexpr (std::is_same_v<T, dv::UnitValueList>) {
            dv::UnitValueList r;
            r.elements.reserve(v.elements.size());
            for(const auto &e : v.elements)
                r.elements.push_back({(long double)std::ceil((double)e.value), e.unit});
            return r;
        }
        return dv::UnitValue{0.0L};
    }, value);
}
dv::EValue dv::builtins::factorial(dv::EValue value) {
    return dv::evalue_fact(value);
}
dv::EValue dv::builtins::floor(dv::EValue value) {
    return std::visit([](const auto &v) -> dv::EValue {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, dv::UnitValue>)
            return dv::UnitValue{(long double)std::floor((double)v.value), v.unit};
        else if constexpr (std::is_same_v<T, dv::UnitValueList>) {
            dv::UnitValueList r;
            r.elements.reserve(v.elements.size());
            for(const auto &e : v.elements)
                r.elements.push_back({(long double)std::floor((double)e.value), e.unit});
            return r;
        }
        return dv::UnitValue{0.0L};
    }, value);
}
dv::EValue dv::builtins::round(dv::EValue value, double place) {
    const double multiplier = std::pow(10.0, place);
    return std::visit([multiplier](const auto &v) -> dv::EValue {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, dv::UnitValue>)
            return dv::UnitValue{(long double)(std::round((double)v.value * multiplier) / multiplier), v.unit};
        else if constexpr (std::is_same_v<T, dv::UnitValueList>) {
            dv::UnitValueList r;
            r.elements.reserve(v.elements.size());
            for(const auto &e : v.elements)
                r.elements.push_back({(long double)(std::round((double)e.value * multiplier) / multiplier), e.unit});
            return r;
        }
        return dv::UnitValue{0.0L};
    }, value);
}
dv::EValue dv::builtins::arcsin(double value) {
    return dv::UnitValue{(long double)std::asin(value)};
}
dv::EValue dv::builtins::arccos(double value) {
    return dv::UnitValue{(long double)std::acos(value)};
}
dv::EValue dv::builtins::arctan(double value) {
    return dv::UnitValue{(long double)std::atan(value)};
}
dv::EValue dv::builtins::arcsec(double value) {
    return dv::UnitValue{1.0L / (long double)std::acos(value)};
}
dv::EValue dv::builtins::arccsc(double value) {
    return dv::UnitValue{1.0L / (long double)std::asin(value)};
}
dv::EValue dv::builtins::arccot(double value) {
    return dv::UnitValue{1.0L / (long double)std::atan(value)};
}
