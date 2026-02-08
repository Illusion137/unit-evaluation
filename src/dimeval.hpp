#pragma once

#include <array>
#include <cstdint>
#include <cstring>

namespace dv {
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
        { "Ω",{2,-3,1,-2,0,0,0}, 1 },
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
