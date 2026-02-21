#include "dimeval.hpp"
#include <cmath>

bool dv::UnitVector::operator==(const UnitVector &rhs) const noexcept {
    return this->vec == rhs;
}
bool dv::UnitVector::operator==(const UnitVec &rhs) const noexcept {
    return this->vec == rhs;
}
dv::UnitVector dv::UnitVector::operator+(const UnitVector &rhs) const noexcept {
    UnitVector temp_vec = *this;
    if(temp_vec != rhs) temp_vec.vec.fill(0);
    return temp_vec;
}
dv::UnitVector dv::UnitVector::operator-(const UnitVector &rhs) const noexcept {
    UnitVector temp_vec = *this;
    if(temp_vec != rhs) temp_vec.vec.fill(0);
    return temp_vec;
}
dv::UnitVector dv::UnitVector::operator*(const UnitVector &rhs) const noexcept {
    UnitVector temp_vec;
    for (uint32_t i = 0; i < vec.size(); i++) temp_vec.vec[i] = this->vec[i] + rhs.vec[i];
    return temp_vec;
}
dv::UnitVector dv::UnitVector::operator/(const UnitVector &rhs) const noexcept {
    UnitVector temp_vec;
    for (uint32_t i = 0; i < vec.size(); i++) temp_vec.vec[i] = this->vec[i] - rhs.vec[i];
    return temp_vec;
}
dv::UnitVector dv::UnitVector::operator^(const UnitVector &rhs) const noexcept {
    UnitVector temp_vec;
    if(rhs == DIMENSIONLESS_VEC) {
        temp_vec.vec.fill(0);
        return temp_vec;
    }
    for (uint32_t i = 0; i < vec.size(); i++) temp_vec.vec[i] = this->vec[i] * rhs.vec[i];
    return temp_vec;
}
dv::UnitVector dv::UnitVector::operator^(const double value) const noexcept {
    UnitVector temp_vec;
    temp_vec.vec.fill(0);
    for (uint32_t i = 0; i < vec.size(); i++) temp_vec.vec[i] = this->vec[i] * value;
    return temp_vec;
}

// Helper: apply a scalar binary op element-wise across two EValues
static dv::EValue apply_elementwise(const dv::EValue &lhs, const dv::EValue &rhs,
    long double (*op)(long double, long double), dv::UnitVector result_unit) {
    dv::EValue result;
    result.unit = result_unit;
    if(lhs.is_scalar() && rhs.is_scalar()) {
        result.value = op(lhs.value, rhs.value);
        return result;
    }
    std::size_t sz = lhs.is_scalar() ? rhs.size() : (rhs.is_scalar() ? lhs.size() : std::min(lhs.size(), rhs.size()));
    result.extra_values.resize(sz);
    for(std::size_t i = 0; i < sz; i++) {
        result.extra_values[i] = op(lhs.at(i), rhs.at(i));
    }
    result.value = result.extra_values[0];
    return result;
}

dv::EValue dv::EValue::operator+() const noexcept {
    return *this;
}
dv::EValue dv::EValue::operator+(const EValue &rhs) const noexcept {
    auto unit_result = this->unit + rhs.unit;
    return apply_elementwise(*this, rhs, [](long double a, long double b){ return a + b; }, unit_result);
}
dv::EValue dv::EValue::operator-() const noexcept {
    EValue result = *this;
    result.value = -result.value;
    for(auto &v : result.extra_values) v = -v;
    return result;
}
dv::EValue dv::EValue::operator-(const EValue &rhs) const noexcept {
    auto unit_result = this->unit - rhs.unit;
    return apply_elementwise(*this, rhs, [](long double a, long double b){ return a - b; }, unit_result);
}
dv::EValue dv::EValue::operator*(const EValue &rhs) const noexcept {
    auto unit_result = this->unit * rhs.unit;
    if(this->is_scalar() && rhs.is_scalar()) {
        // Complex multiplication
        if(this->is_complex() || rhs.is_complex()) {
            EValue r;
            r.value = this->value * rhs.value - this->imag * rhs.imag;
            r.imag = this->value * rhs.imag + this->imag * rhs.value;
            r.unit = unit_result;
            return r;
        }
    }
    return apply_elementwise(*this, rhs, [](long double a, long double b){ return a * b; }, unit_result);
}
dv::EValue dv::EValue::operator/(const EValue &rhs) const noexcept {
    auto unit_result = this->unit / rhs.unit;
    if(this->is_scalar() && rhs.is_scalar()) {
        // Complex division
        if(this->is_complex() || rhs.is_complex()) {
            long double denom = rhs.value * rhs.value + rhs.imag * rhs.imag;
            EValue r;
            r.value = (this->value * rhs.value + this->imag * rhs.imag) / denom;
            r.imag = (this->imag * rhs.value - this->value * rhs.imag) / denom;
            r.unit = unit_result;
            return r;
        }
    }
    return apply_elementwise(*this, rhs, [](long double a, long double b){ return a / b; }, unit_result);
}
dv::EValue dv::EValue::operator^(const EValue &rhs) const noexcept {
    auto compute_unit = [&]() -> UnitVector {
        if(rhs.unit == DIMENSIONLESS_VEC) return this->unit ^ rhs.value;
        return this->unit ^ rhs.unit;
    };
    auto unit_result = compute_unit();
    return apply_elementwise(*this, rhs, [](long double a, long double b){ return std::pow(a, b); }, unit_result);
}
dv::EValue dv::EValue::fact() const noexcept {
    if(is_scalar()) {
        long double f = 1;
        for(uint32_t i = 2; i <= (uint64_t)this->value; i++) f *= i;
        return { f, { 0 } };
    }
    EValue result;
    result.unit = UnitVector{DIMENSIONLESS_VEC};
    result.extra_values.resize(size());
    for(std::size_t j = 0; j < size(); j++) {
        long double f = 1;
        for(uint32_t i = 2; i <= (uint64_t)at(j); i++) f *= i;
        result.extra_values[j] = f;
    }
    result.value = result.extra_values[0];
    return result;
}
dv::EValue dv::EValue::abs() const noexcept {
    if(is_complex()) {
        return { std::sqrt(value * value + imag * imag), this->unit };
    }
    if(is_scalar()) return { std::fabs(this->value), this->unit };
    EValue result;
    result.unit = this->unit;
    result.extra_values.resize(size());
    for(std::size_t i = 0; i < size(); i++) result.extra_values[i] = std::fabs(at(i));
    result.value = result.extra_values[0];
    return result;
}
