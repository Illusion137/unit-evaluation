#include "ast.hpp"
#include "builtins.hpp"
#include "evaluator.hpp"
#include "token.hpp"
#include <format>
#include <memory>

dv::EValue dv::AST::evaluate(dv::Evaluator &evalulator) {
    return evaluate(this, evalulator);
}
dv::EValue dv::AST::evaluate(const std::unique_ptr<AST> &ast, dv::Evaluator &evalulator) {
    return evaluate(ast.get(), evalulator);
}
dv::EValue dv::AST::evaluate(const AST *ast, dv::Evaluator &evalulator) {
    switch (ast->token.type) {
        case TokenType::EQUAL: {
            auto value = std::get<AST::ASTExpression>(ast->data).rhs->evaluate(evalulator);
            evalulator.evaluated_variables.insert_or_assign(std::string{std::get<AST::ASTExpression>(ast->data).lhs->token.text}, value);
            // TODO lhs should be a single token
            return value;
        }
        case TokenType::NUMERIC_LITERAL: return std::get<AST::ASTExpression>(ast->data).value;
        case TokenType::IDENTIFIER: {
            const auto &token_id = std::string{ast->token.text};
            if(evalulator.fixed_constants.contains(token_id)){
                return evalulator.fixed_constants.at(token_id);
            }
            else if(evalulator.evaluated_variables.contains(token_id)){
                return evalulator.evaluated_variables.at(token_id);
            }
            return 0.0; // TODO spew errors here
        }
        case TokenType::PLUS: {
            const auto &rhs = std::get<AST::ASTExpression>(ast->data).rhs;
            const dv::EValue lhs = std::get<AST::ASTExpression>(ast->data).lhs->evaluate(evalulator);
            if(rhs == nullptr) return lhs;
            return lhs + rhs->evaluate(evalulator);
        }
        case TokenType::MINUS: {
            const auto &rhs = std::get<AST::ASTExpression>(ast->data).rhs;
            const dv::EValue lhs = std::get<AST::ASTExpression>(ast->data).lhs->evaluate(evalulator);
            if(rhs == nullptr) return -lhs;
            return lhs - rhs->evaluate(evalulator);
        }
        case TokenType::TIMES: {
            const dv::EValue lhs = std::get<AST::ASTExpression>(ast->data).lhs->evaluate(evalulator);
            const dv::EValue rhs = std::get<AST::ASTExpression>(ast->data).rhs->evaluate(evalulator);
            return lhs * rhs;
        }
        case TokenType::DIVIDE:
        case TokenType::FRACTION: {
            const dv::EValue lhs = std::get<AST::ASTExpression>(ast->data).lhs->evaluate(evalulator);
            const dv::EValue rhs = std::get<AST::ASTExpression>(ast->data).rhs->evaluate(evalulator);
            return lhs / rhs;
        }
        case TokenType::EXPONENT: {
            const dv::EValue lhs = std::get<AST::ASTExpression>(ast->data).lhs->evaluate(evalulator);
            const dv::EValue rhs = std::get<AST::ASTExpression>(ast->data).rhs->evaluate(evalulator);
            return lhs ^ rhs;
        }
        case TokenType::FACTORIAL: {
            const dv::EValue lhs = std::get<AST::ASTExpression>(ast->data).lhs->evaluate(evalulator);
            return lhs.fact();
        }
        case TokenType::BUILTIN_FUNC_LN: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::ln(args[0]->evaluate(evalulator).value);
        }
        case TokenType::BUILTIN_FUNC_SIN: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::sin(args[0]->evaluate(evalulator).value);
        }
        case TokenType::BUILTIN_FUNC_COS: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::cos(args[0]->evaluate(evalulator).value);
        }
        case TokenType::BUILTIN_FUNC_TAN: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::tan(args[0]->evaluate(evalulator).value);
        }
        case TokenType::BUILTIN_FUNC_SEC: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::sec(args[0]->evaluate(evalulator).value);
        }
        case TokenType::BUILTIN_FUNC_CSC: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::csc(args[0]->evaluate(evalulator).value);
        }
        case TokenType::BUILTIN_FUNC_COT: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::cot(args[0]->evaluate(evalulator).value);
        }
        case TokenType::BUILTIN_FUNC_LOG: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            const auto &special_value = std::get<AST::ASTCall>(ast->data).special_value;
            if(special_value == nullptr) return dv::builtins::log(args[0]->evaluate(evalulator).value);
            else return dv::builtins::log(args[0]->evaluate(evalulator).value, special_value->evaluate(evalulator).value);
        }
        case TokenType::ABSOLUTE_BAR:
        case TokenType::BUILTIN_FUNC_ABS: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::abs(args[0]->evaluate(evalulator));
        }
        case TokenType::BUILTIN_FUNC_NCR: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::nCr(args[0]->evaluate(evalulator).value, args[1]->evaluate(evalulator).value);
        }
        case TokenType::BUILTIN_FUNC_NPR: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::nPr(args[0]->evaluate(evalulator).value, args[1]->evaluate(evalulator).value);
        }
        case TokenType::BUILTIN_FUNC_SQRT: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            const auto &special_value = std::get<AST::ASTCall>(ast->data).special_value;
            if(special_value == nullptr) return dv::builtins::nthsqrt(args[0]->evaluate(evalulator).value, 2.0);
            else return dv::builtins::nthsqrt(args[0]->evaluate(evalulator), special_value->evaluate(evalulator).value);
        }
        case TokenType::BUILTIN_FUNC_CEIL: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::ceil(args[0]->evaluate(evalulator));
        }
        case TokenType::BUILTIN_FUNC_FACT: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::factorial(args[0]->evaluate(evalulator));
        }
        case TokenType::BUILTIN_FUNC_FLOOR: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::floor(args[0]->evaluate(evalulator));
        }
        case TokenType::BUILTIN_FUNC_ROUND: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::round(args[0]->evaluate(evalulator), args[1]->evaluate(evalulator).value);
        }
        case TokenType::BUILTIN_FUNC_ARCSIN: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::arcsin(args[0]->evaluate(evalulator).value);
        }
        case TokenType::BUILTIN_FUNC_ARCCOS: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::arccos(args[0]->evaluate(evalulator).value);
        }
        case TokenType::BUILTIN_FUNC_ARCTAN: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::arctan(args[0]->evaluate(evalulator).value);
        }
        case TokenType::BUILTIN_FUNC_ARCSEC: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::arcsec(args[0]->evaluate(evalulator).value);
        }
        case TokenType::BUILTIN_FUNC_ARCCSC: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::arccsc(args[0]->evaluate(evalulator).value);
        }
        case TokenType::BUILTIN_FUNC_ARCCOT: {
            const auto &args = std::get<AST::ASTCall>(ast->data).args;
            return dv::builtins::arccot(args[0]->evaluate(evalulator).value);
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
        for(std::uint32_t i = 0 ; i < call.args.size(); i++){
            content += call.args[i]->to_string(depth + 1);
        }
    }
    return content;
}