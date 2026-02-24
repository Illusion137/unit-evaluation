#pragma once

#include <array>
#include <cstdint>
#include <cstring>
#include <optional>
#include <vector>

#define DIM_METER    { 1, 0, 0, 0, 0, 0, 0 }
#define DIM_KILOGRAM { 0, 0, 1, 0, 0, 0, 0 }
#define DIM_SECOND   { 0, 1, 0, 0, 0, 0, 0 }
#define DIM_AMPERE   { 0, 0, 0, 1, 0, 0, 0 }
#define DIM_KELVIN   { 0, 0, 0, 0, 1, 0, 0 }
#define DIM_MOLE     { 0, 0, 0, 0, 0, 1, 0 }
#define DIM_CANDELA  { 0, 0, 0, 0, 0, 0, 1 }
#define DIM_NEWTON   { 1, -2, 1, 0, 0, 0, 0 }
#define DIM_JOULE    { 2, -2, 1, 0, 0, 0, 0 }
#define DIM_PASCAL   { -1, -2, 1, 0, 0, 0, 0 }
#define DIM_COULOMB  { 0, 1, 0, 1, 0, 0, 0 }
#define DIM_HERTZ    { 0, -1, 0, 0, 0, 0, 0 }

#define DIM_SIEMENS  { -2, 3, -1, 2, 0, 0, 0 }
#define DIM_OHM      { 2, -3, 1, -2, 0, 0, 0 }
#define DIM_FARAD    { -2, 4, -1, 2, 0, 0, 0 }
#define DIM_VOLT     { 2, -3, 1, -1, 0, 0, 0 }
#define DIM_WATT     { 2, -3, 1, 0, 0, 0, 0 }
#define DIM_WEBER    { 2, -2, 1, -1, 0, 0, 0 }
#define DIM_TESLA    { 0, -2, 1, -1, 0, 0, 0 }
#define DIM_HENRY    { 2, -2, 1, -2, 0, 0, 0 }

namespace dv {
    // m	meter	[ 1, 0, 0, 0, 0, 0, 0 ]
    // kg	kilogram	[ 0, 0, 1, 0, 0, 0, 0 ]
    // s	second	[ 0, 1, 0, 0, 0, 0, 0 ]
    // A	ampere	[ 0, 0, 0, 1, 0, 0, 0 ]
    // K	kelvin	[ 0, 0, 0, 0, 1, 0, 0 ]
    // mol	mole	[ 0, 0, 0, 0, 0, 1, 0 ]
    // cd	candela	[ 0, 0, 0, 0, 0, 0, 1 ]

    // N	kg·m·s⁻²	[ 1, -2, 1, 0, 0, 0, 0 ]
    // J	N·m = kg·m²·s⁻²	[ 2, -2, 1, 0, 0, 0, 0 ]
    // Pa	N/m² = kg·m⁻¹·s⁻²	[ -1, -2, 1, 0, 0, 0, 0 ]
    // C	A·s	[ 0, 1, 0, 1, 0, 0, 0 ]
    // Hz	s⁻¹	[ 0, -1, 0, 0, 0, 0, 0 ]
    using UnitVec = std::array<std::int8_t, 7>;

    static constexpr UnitVec DIMENSIONLESS_VEC = { 0, 0, 0, 0, 0, 0, 0 };
    
    struct UnitVector {
        UnitVec vec;
        bool operator==(const UnitVector &rhs) const noexcept;
        bool operator==(const UnitVec &rhs) const noexcept;
        UnitVector operator+(const UnitVector &rhs) const noexcept;
        UnitVector operator-(const UnitVector &rhs) const noexcept;
        UnitVector operator*(const UnitVector &rhs) const noexcept;
        UnitVector operator/(const UnitVector &rhs) const noexcept;
        UnitVector operator^(const UnitVector &rhs) const noexcept;
        UnitVector operator^(const double value) const noexcept;
    };
    struct EValue {
        long double value;
        long double imag = 0.0;
        UnitVector unit;
        std::vector<long double> extra_values;

        EValue() : value{0.0}, unit{DIMENSIONLESS_VEC} {}
        EValue(const long double val): value{val}, unit{DIMENSIONLESS_VEC} {}
        EValue(const long double val, const UnitVector _unit): value{val}, unit{_unit} {}

        bool is_scalar() const noexcept { return extra_values.empty(); }
        bool is_complex() const noexcept { return imag != 0.0; }
        std::size_t size() const noexcept { return extra_values.empty() ? 1 : extra_values.size(); }
        long double at(std::size_t i) const noexcept {
            if(extra_values.empty()) return value;
            return extra_values[i];
        }

        EValue operator+() const noexcept;
        EValue operator+(const EValue &rhs) const noexcept;
        EValue operator-() const noexcept;
        EValue operator-(const EValue &rhs) const noexcept;
        EValue operator*(const EValue &rhs) const noexcept;
        EValue operator/(const EValue &rhs) const noexcept;
        EValue operator^(const EValue &rhs) const noexcept;
        EValue fact() const noexcept;
        EValue abs() const noexcept;

        int sig_figs = -1;
        int decimal_places = -1;

        std::optional<std::vector<std::vector<long double>>> matrix;
    };
}
