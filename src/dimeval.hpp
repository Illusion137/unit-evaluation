#pragma once

#include <array>
#include <cstdint>
#include <cstring>

namespace dv {
    using UnitVec = std::array<std::int8_t, 7>;
    static constexpr UnitVec DIMENSIONLESS_VEC = { 0 };
    
    struct UnitVector {
        UnitVec vec;
        bool operator==(const UnitVector &rhs) const noexcept;
        bool operator==(const UnitVec &rhs) const noexcept;
        UnitVector operator+(const UnitVector &rhs) const noexcept;
        UnitVector operator-(const UnitVector &rhs) const noexcept;
        UnitVector operator*(const UnitVector &rhs) const noexcept;
        UnitVector operator/(const UnitVector &rhs) const noexcept;
        UnitVector operator^(const UnitVector &rhs) const noexcept;
    };
    struct EValue {
        double value;
        UnitVector unit;
        EValue(const double val): value{val}, unit{DIMENSIONLESS_VEC} {}
        EValue(const double val, const UnitVector _unit): value{val}, unit{_unit} {}
        EValue operator+() const noexcept;
        EValue operator+(const EValue &rhs) const noexcept;
        EValue operator-() const noexcept;
        EValue operator-(const EValue &rhs) const noexcept;
        EValue operator*(const EValue &rhs) const noexcept;
        EValue operator/(const EValue &rhs) const noexcept;
        EValue operator^(const EValue &rhs) const noexcept;
        EValue fact() const noexcept;
        EValue abs() const noexcept;
    };
}
