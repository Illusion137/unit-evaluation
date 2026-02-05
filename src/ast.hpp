#pragma once

#include "dimeval.hpp"

enum NodeType {
    NUMBER,
    VARIABLE,
    ADDITION,
    UNARY_PLUS,
    SUBTRACTION,
    UNARY_MINUS,
    MULTIPLICATION,
    DIVISION,
    EXPONENT,
    FACTORIAL,
    ABSOLUTE_VALUE,
    FUNCTION,
};

struct AST {
    NodeType type;
    int lhs = -1;
    int rhs = -1;
    int symbol = -1;
    EValue value;
};

static EValue eval(const AST *ast, int idx) {
    const AST& node = ast[idx];

    switch (node.type) {
        case NUMBER: return node.value;
        case VARIABLE: return vars[node.symbol];
        case UNARY_PLUS: {
            const EValue lhs = eval(ast, node.lhs);
            return +lhs;
        }
        case ADDITION: {
            const EValue lhs = eval(ast, node.lhs);
            const EValue rhs = eval(ast, node.rhs);
            return lhs + rhs;
        }
        case SUBTRACTION: {
            const EValue lhs = eval(ast, node.lhs);
            const EValue rhs = eval(ast, node.rhs);
            return lhs - rhs;
        }
        case UNARY_MINUS: {
            const EValue lhs = eval(ast, node.lhs);
            return -lhs;
        }
        case MULTIPLICATION: {
            const EValue lhs = eval(ast, node.lhs);
            const EValue rhs = eval(ast, node.rhs);
            return lhs * rhs;
        }
        case DIVISION: {
            const EValue lhs = eval(ast, node.lhs);
            const EValue rhs = eval(ast, node.rhs);
            return lhs / rhs;
        }
        case EXPONENT: {
            const EValue lhs = eval(ast, node.lhs);
            const EValue rhs = eval(ast, node.rhs);
            return lhs ^ rhs;
        }
        case FACTORIAL: {
            const EValue lhs = eval(ast, node.lhs);
            return lhs.fact();
        }
        case ABSOLUTE_VALUE: {
            const EValue lhs = eval(ast, node.lhs);
            return lhs.abs();
        }
        case FUNCTION: break;
        default: break;
    }
    return {};
}