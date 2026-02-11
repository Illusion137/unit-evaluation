#pragma once

#include <array>
#include <cstdint>
#include <cstring>

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
    struct UnitDef {
        const char* name;
        UnitVec dim;
        double scale;
    };

    static const UnitDef UNIT_TABLE[] = {
        { "m",  {1,0,0,0,0,0,0}, 1 },
        { "s",  {0,1,0,0,0,0,0}, 1 },
        { "kg", {0,0,1,0,0,0,0}, 1 },
        { "N",  {1,-2,1,0,0,0,0}, 1 },
        { "J",  {2,-2,1,0,0,0,0}, 1 },
        { "W",  {2,-3,1,0,0,0,0}, 1 },
        { "C",  {0,1,0,1,0,0,0}, 1 },
        { "V",  {2,-3,1,-1,0,0,0}, 1 },
        { "Ω",  {2,-3,1,-2,0,0,0}, 1 },
        { "T",  {0,-2,1,-1,0,0,0}, 1 },
        { "Wb", {2,-2,1,-1,0,0,0}, 1 },
    };

    struct Prefix { const char* p; double scale; };

    static const Prefix PREFIXES[] = {
        {"Y",1e24},
        {"Z",1e21},
        {"E",1e18},
        {"P",1e15},
        {"T",1e12},
        {"G",1e9},
        {"M",1e6},
        {"k",1e3},
        {"h",1e2},
        {"da",1e1},
        {"d",1e-1},
        {"c",1e-2},
        {"m",1e-3},
        {"u",1e-6},
        {"n",1e-9},
        {"p",1e-12},
        {"f",1e-15},
        {"a",1e-18}
    };

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
        UnitVector unit;
        EValue() : value{0.0}, unit{DIMENSIONLESS_VEC} {}
        EValue(const long double val): value{val}, unit{DIMENSIONLESS_VEC} {}
        EValue(const long double val, const UnitVector _unit): value{val}, unit{_unit} {}
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
