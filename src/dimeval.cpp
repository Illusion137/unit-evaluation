#include "dimeval.hpp"
#include <cmath>

bool dv::UnitVector::operator==(const UnitVector &rhs) const noexcept {
    return std::memcmp(this->vec.data(), rhs.vec.data(), sizeof(std::int8_t)) == 0;
}
bool dv::UnitVector::operator==(const UnitVec &rhs) const noexcept {
    return std::memcmp(this->vec.data(), rhs.data(), sizeof(std::int8_t)) == 0;
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

dv::EValue dv::EValue::operator+() const noexcept {
    return { this->value, this->unit };
}
dv::EValue dv::EValue::operator+(const EValue &rhs) const noexcept {
    return { this->value + rhs.value, this->unit + rhs.unit };
}
dv::EValue dv::EValue::operator-() const noexcept {
    return { -this->value, this->unit };
}
dv::EValue dv::EValue::operator-(const EValue &rhs) const noexcept {
    return { this->value - rhs.value, this->unit - rhs.unit };
}
dv::EValue dv::EValue::operator*(const EValue &rhs) const noexcept {
    return { this->value * rhs.value, this->unit * rhs.unit };
}
dv::EValue dv::EValue::operator/(const EValue &rhs) const noexcept {
    return { this->value / rhs.value, this->unit / rhs.unit };
}
dv::EValue dv::EValue::operator^(const EValue &rhs) const noexcept {
    if(rhs.unit == DIMENSIONLESS_VEC)  return { std::pow(this->value, rhs.value), this->unit ^ rhs.value };
    return { std::pow(this->value, rhs.value), this->unit ^ rhs.unit };
}
dv::EValue dv::EValue::fact() const noexcept {
    long double fact = 1;
    for(uint32_t i = 2; i <= (uint64_t)this->value; i++) fact *= i;
    return { fact, { 0 } };
}
dv::EValue dv::EValue::abs() const noexcept {
    return { std::fabs(this->value), this->unit };
}