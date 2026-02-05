#pragma once

#include "dimeval.hpp"
#include <unordered_map>

namespace builtins {
    EValue abs(double value);
    EValue sqrt(EValue value);
    EValue nthroot(EValue value);
    EValue sindeg();
    EValue sin();
    EValue asindeg();
    EValue asin();
    EValue cosdeg();
    EValue cos();
    EValue acosdeg();
    EValue acos();
    EValue tandeg();
    EValue tan();
    EValue atandeg();
    EValue atan();
    EValue ln();
    EValue log();
    EValue logb();
    EValue round();
    EValue floor();
    EValue ceil();
    EValue factorial();
    EValue nCr();
    EValue nPr();
    static const std::unordered_map<std::string, std::uint8_t> BUILTIN_MAP = {
        
    };
}