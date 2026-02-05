#include "ast.hpp"
#include "builtins.hpp"
#include "token.hpp"

dv::EValue dv::eval(const std::unique_ptr<AST> &ast) {
    switch (ast->token.type) {
        case TokenType::NUMERIC_LITERAL: return ast->value;
        // case TokenType::IDENTIFIER: return vars[node.symbol];
        case TokenType::PLUS: {
            const dv::EValue lhs = eval(ast->lhs);
            const dv::EValue rhs = eval(ast->rhs);
            return lhs + rhs;
        }
        case TokenType::MINUS: {
            const dv::EValue lhs = eval(ast->lhs);
            const dv::EValue rhs = eval(ast->rhs);
            return lhs - rhs;
        }
        // case TokenType::UNARY_MINUS: {
        //     const dv::EValue lhs = eval(ast->lhs);
        //     return -lhs;
        // }
        case TokenType::TIMES: {
            const dv::EValue lhs = eval(ast->lhs);
            const dv::EValue rhs = eval(ast->rhs);
            return lhs * rhs;
        }
        case TokenType::FRACTION: {
            const dv::EValue lhs = eval(ast->lhs);
            const dv::EValue rhs = eval(ast->rhs);
            return lhs / rhs;
        }
        case TokenType::EXPONENT: {
            const dv::EValue lhs = eval(ast->lhs);
            const dv::EValue rhs = eval(ast->rhs);
            return lhs ^ rhs;
        }
        case TokenType::DIVIDE:
        case TokenType::FACTORIAL: {
            const dv::EValue lhs = eval(ast->lhs);
            return lhs.fact();
        }
        case TokenType::BUILTIN_FUNC_LN: {
            const dv::EValue lhs = eval(ast->lhs);
            return dv::builtins::ln(lhs.value);
        }
        case TokenType::BUILTIN_FUNC_SIN: {
            const dv::EValue lhs = eval(ast->lhs);
            return dv::builtins::sin(lhs.value);
        }
        case TokenType::BUILTIN_FUNC_COS: {
            const dv::EValue lhs = eval(ast->lhs);
            return dv::builtins::cos(lhs.value);
        }
        case TokenType::BUILTIN_FUNC_TAN: {
            const dv::EValue lhs = eval(ast->lhs);
            return dv::builtins::tan(lhs.value);
        }
        case TokenType::BUILTIN_FUNC_SEC: {
            const dv::EValue lhs = eval(ast->lhs);
            return dv::builtins::sec(lhs.value);
        }
        case TokenType::BUILTIN_FUNC_CSC: {
            const dv::EValue lhs = eval(ast->lhs);
            return dv::builtins::csc(lhs.value);
        }
        case TokenType::BUILTIN_FUNC_COT: {
            const dv::EValue lhs = eval(ast->lhs);
            return dv::builtins::cot(lhs.value);
        }
        case TokenType::BUILTIN_FUNC_LOG: {
            const dv::EValue lhs = eval(ast->lhs);
            const dv::EValue rhs = eval(ast->rhs);
            return dv::builtins::log(lhs.value, rhs.value);
        }
        case TokenType::BUILTIN_FUNC_ABS: {
            const dv::EValue lhs = eval(ast->lhs);
            return dv::builtins::abs(lhs);
        }
        case TokenType::BUILTIN_FUNC_NCR: {
            const dv::EValue lhs = eval(ast->lhs);
            const dv::EValue rhs = eval(ast->rhs);
            return dv::builtins::nCr(lhs.value, rhs.value);
        }
        case TokenType::BUILTIN_FUNC_NPR: {
            const dv::EValue lhs = eval(ast->lhs);
            const dv::EValue rhs = eval(ast->rhs);
            return dv::builtins::nPr(lhs.value, rhs.value);
        }
        case TokenType::BUILTIN_FUNC_SQRT: {
            const dv::EValue lhs = eval(ast->lhs);
            const dv::EValue rhs = eval(ast->rhs);
            return dv::builtins::nthsqrt(lhs, rhs.value);
        }
        case TokenType::BUILTIN_FUNC_CEIL: {
            const dv::EValue lhs = eval(ast->lhs);
            return dv::builtins::ceil(lhs);
        }
        case TokenType::BUILTIN_FUNC_FACT: {
            const dv::EValue lhs = eval(ast->lhs);
            return dv::builtins::factorial(lhs.value);
        }
        case TokenType::BUILTIN_FUNC_FLOOR: {
            const dv::EValue lhs = eval(ast->lhs);
            return dv::builtins::floor(lhs);
        }
        case TokenType::BUILTIN_FUNC_ROUND: {
            const dv::EValue lhs = eval(ast->lhs);
            const dv::EValue rhs = eval(ast->rhs);
            return dv::builtins::round(lhs, rhs.value);
        }
        case TokenType::BUILTIN_FUNC_ARCSIN: {
            const dv::EValue lhs = eval(ast->lhs);
            return dv::builtins::arcsin(lhs.value);
        }
        case TokenType::BUILTIN_FUNC_ARCCOS: {
            const dv::EValue lhs = eval(ast->lhs);
            return dv::builtins::arccos(lhs.value);
        }
        case TokenType::BUILTIN_FUNC_ARCTAN: {
            const dv::EValue lhs = eval(ast->lhs);
            return dv::builtins::arctan(lhs.value);
        }
        case TokenType::BUILTIN_FUNC_ARCSEC: {
            const dv::EValue lhs = eval(ast->lhs);
            return dv::builtins::arcsec(lhs.value);
        }
        case TokenType::BUILTIN_FUNC_ARCCSC: {
            const dv::EValue lhs = eval(ast->lhs);
            return dv::builtins::arccsc(lhs.value);
        }
        case TokenType::BUILTIN_FUNC_ARCCOT: {
            const dv::EValue lhs = eval(ast->lhs);
            return dv::builtins::arccot(lhs.value);
        }
        default: break;
    }
    return 0.0;
}