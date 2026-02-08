#include "ast.hpp"
#include "builtins.hpp"
#include "token.hpp"
#include <format>
#include <memory>

dv::EValue dv::AST::evaluate() {
    return evaluate(this);
}
dv::EValue dv::AST::evaluate(const std::unique_ptr<AST> &ast) {
    return evaluate(ast.get());
}
dv::EValue dv::AST::evaluate(const AST *ast) {
    switch (ast->token.type) {
        case TokenType::EQUAL: {
            // TODO add into sym table
            // TODO lhs should be a single token
            return evaluate(std::get<AST::ASTExpression>(ast->data).rhs);
        }
        case TokenType::NUMERIC_LITERAL: return std::get<AST::ASTExpression>(ast->data).value;
        // case TokenType::IDENTIFIER: return vars[node.symbol];
        case TokenType::PLUS: {
            const dv::EValue lhs = evaluate(std::get<AST::ASTExpression>(ast->data).lhs);
            const dv::EValue rhs = evaluate(std::get<AST::ASTExpression>(ast->data).rhs);
            return lhs + rhs;
        }
        case TokenType::MINUS: {
            const dv::EValue lhs = evaluate(std::get<AST::ASTExpression>(ast->data).lhs);
            const dv::EValue rhs = evaluate(std::get<AST::ASTExpression>(ast->data).rhs);
            return lhs - rhs;
        }
        // case TokenType::UNARY_MINUS: {
        //     const dv::EValue lhs = evaluate(std::get<AST::ASTExpression>(ast->data).lhs);
        //     return -lhs;
        // }
        case TokenType::TIMES: {
            const dv::EValue lhs = evaluate(std::get<AST::ASTExpression>(ast->data).lhs);
            const dv::EValue rhs = evaluate(std::get<AST::ASTExpression>(ast->data).rhs);
            return lhs * rhs;
        }
        case TokenType::FRACTION: {
            const dv::EValue lhs = evaluate(std::get<AST::ASTExpression>(ast->data).lhs);
            const dv::EValue rhs = evaluate(std::get<AST::ASTExpression>(ast->data).rhs);
            return lhs / rhs;
        }
        case TokenType::EXPONENT: {
            const dv::EValue lhs = evaluate(std::get<AST::ASTExpression>(ast->data).lhs);
            const dv::EValue rhs = evaluate(std::get<AST::ASTExpression>(ast->data).rhs);
            return lhs ^ rhs;
        }
        case TokenType::DIVIDE:
        case TokenType::FACTORIAL: {
            const dv::EValue lhs = evaluate(std::get<AST::ASTExpression>(ast->data).lhs);
            return lhs.fact();
        }
        case TokenType::BUILTIN_FUNC_LN: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::ln(evaluate(args[0]).value);
        }
        case TokenType::BUILTIN_FUNC_SIN: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::sin(evaluate(args[0]).value);
        }
        case TokenType::BUILTIN_FUNC_COS: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::cos(evaluate(args[0]).value);
        }
        case TokenType::BUILTIN_FUNC_TAN: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::tan(evaluate(args[0]).value);
        }
        case TokenType::BUILTIN_FUNC_SEC: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::sec(evaluate(args[0]).value);
        }
        case TokenType::BUILTIN_FUNC_CSC: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::csc(evaluate(args[0]).value);
        }
        case TokenType::BUILTIN_FUNC_COT: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::cot(evaluate(args[0]).value);
        }
        case TokenType::BUILTIN_FUNC_LOG: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            const auto special_value = std::get<AST::ASTCall>(ast->data).special_value;
            if(special_value == 0) return dv::builtins::log(evaluate(args[0]).value);
            else return dv::builtins::log(evaluate(args[0]).value, special_value);
        }
        case TokenType::BUILTIN_FUNC_ABS: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::abs(evaluate(args[0]));
        }
        case TokenType::BUILTIN_FUNC_NCR: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::nCr(evaluate(args[0]).value, evaluate(args[1]).value);
        }
        case TokenType::BUILTIN_FUNC_NPR: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::nPr(evaluate(args[0]).value, evaluate(args[1]).value);
        }
        case TokenType::BUILTIN_FUNC_SQRT: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            const auto special_value = std::get<AST::ASTCall>(ast->data).special_value;
            if(special_value == 0) return dv::builtins::nthsqrt(evaluate(args[0]).value, 2.0);
            else return dv::builtins::nthsqrt(evaluate(args[0]), special_value);
        }
        case TokenType::BUILTIN_FUNC_CEIL: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::ceil(evaluate(args[0]));
        }
        case TokenType::BUILTIN_FUNC_FACT: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::factorial(evaluate(args[0]));
        }
        case TokenType::BUILTIN_FUNC_FLOOR: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::floor(evaluate(args[0]));
        }
        case TokenType::BUILTIN_FUNC_ROUND: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::round(evaluate(args[0]), evaluate(args[1]).value);
        }
        case TokenType::BUILTIN_FUNC_ARCSIN: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::arcsin(evaluate(args[0]).value);
        }
        case TokenType::BUILTIN_FUNC_ARCCOS: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::arccos(evaluate(args[0]).value);
        }
        case TokenType::BUILTIN_FUNC_ARCTAN: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::arctan(evaluate(args[0]).value);
        }
        case TokenType::BUILTIN_FUNC_ARCSEC: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::arcsec(evaluate(args[0]).value);
        }
        case TokenType::BUILTIN_FUNC_ARCCSC: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::arccsc(evaluate(args[0]).value);
        }
        case TokenType::BUILTIN_FUNC_ARCCOT: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::arccot(evaluate(args[0]).value);
        }
        default: break;
    }
    return 0.0;
}

std::string dv::AST::to_string(const std::uint16_t depth) const noexcept{
    constexpr std::uint32_t tab_size = 4;
    std::string tabs = std::format("{:>{}}", "", depth * tab_size);
    std::string content = std::format("{}{}\n", tabs, token);
    if(this->data.index() == 0){
        const auto &expr = std::get<AST::ASTExpression>(this->data);
        if(expr.lhs) content += expr.lhs->to_string(depth + 1);
        if(expr.rhs) content += expr.rhs->to_string(depth + 1);
    }
    else {
        const auto &call = std::get<AST::ASTCall>(this->data);
        content += std::format("{} [SP]: {}\n", tabs, call.special_value);
        for(std::uint32_t i = 0 ; i < call.args.size(); i++){
            content += call.args[i]->to_string(depth + 1);
        }
    }
    return content;
}