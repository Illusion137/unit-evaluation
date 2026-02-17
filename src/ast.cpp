#include "ast.hpp"
#include "builtins.hpp"
#include "evaluator.hpp"
#include "token.hpp"
#include <format>
#include <memory>

dv::MaybeEValue dv::AST::evaluate(dv::Evaluator &evalulator) {
    return evaluate(this, evalulator);
}
dv::MaybeEValue dv::AST::evaluate(const std::unique_ptr<AST> &ast, dv::Evaluator &evalulator) {
    return evaluate(ast.get(), evalulator);
}
dv::MaybeEValue dv::AST::evaluate(const AST *ast, dv::Evaluator &evalulator) {
    switch (ast->token.type) {
        case TokenType::EQUAL: {
            const auto &expr = std::get<ASTExpression>(ast->data);
            if(expr.lhs->token.type == TokenType::FORMULA_QUERY) {
                auto rhs = expr.rhs->evaluate(evalulator);
                if(!rhs) return rhs;
                evalulator.last_formula_results = evalulator.get_available_formulas(rhs->unit);
                return *rhs;
            }
            auto value = expr.rhs->evaluate(evalulator);
            if(!value) return value;
            evalulator.evaluated_variables.insert_or_assign(
                std::string{expr.lhs->token.text}, *value);
            return value;
        }
        case TokenType::NUMERIC_LITERAL:
            return std::get<ASTExpression>(ast->data).value;
        case TokenType::IDENTIFIER: {
            const auto &token_id = std::string{ast->token.text};
            if(evalulator.fixed_constants.contains(token_id))
                return evalulator.fixed_constants.at(token_id);
            if(evalulator.evaluated_variables.contains(token_id))
                return evalulator.evaluated_variables.at(token_id);
            return std::unexpected{std::format("Undefined variable '{}'", token_id)};
        }
        case TokenType::PLUS: {
            const auto &expr = std::get<ASTExpression>(ast->data);
            auto lhs = expr.lhs->evaluate(evalulator);
            if(!lhs) return lhs;
            if(!expr.rhs) return *lhs;
            auto rhs = expr.rhs->evaluate(evalulator);
            if(!rhs) return rhs;
            return *lhs + *rhs;
        }
        case TokenType::MINUS: {
            const auto &expr = std::get<ASTExpression>(ast->data);
            auto lhs = expr.lhs->evaluate(evalulator);
            if(!lhs) return lhs;
            if(!expr.rhs) return -*lhs;
            auto rhs = expr.rhs->evaluate(evalulator);
            if(!rhs) return rhs;
            return *lhs - *rhs;
        }
        case TokenType::TIMES: {
            const auto &expr = std::get<ASTExpression>(ast->data);
            auto lhs = expr.lhs->evaluate(evalulator);
            if(!lhs) return lhs;
            auto rhs = expr.rhs->evaluate(evalulator);
            if(!rhs) return rhs;
            return *lhs * *rhs;
        }
        case TokenType::DIVIDE:
        case TokenType::FRACTION: {
            const auto &expr = std::get<ASTExpression>(ast->data);
            auto lhs = expr.lhs->evaluate(evalulator);
            if(!lhs) return lhs;
            auto rhs = expr.rhs->evaluate(evalulator);
            if(!rhs) return rhs;
            return *lhs / *rhs;
        }
        case TokenType::EXPONENT: {
            const auto &expr = std::get<ASTExpression>(ast->data);
            auto lhs = expr.lhs->evaluate(evalulator);
            if(!lhs) return lhs;
            auto rhs = expr.rhs->evaluate(evalulator);
            if(!rhs) return rhs;
            return *lhs ^ *rhs;
        }
        case TokenType::FACTORIAL: {
            auto lhs = std::get<ASTExpression>(ast->data).lhs->evaluate(evalulator);
            if(!lhs) return lhs;
            return lhs->fact();
        }
        case TokenType::BUILTIN_FUNC_LN: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return dv::builtins::ln(arg->value);
        }
        case TokenType::BUILTIN_FUNC_SIN: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return dv::builtins::sin(arg->value);
        }
        case TokenType::BUILTIN_FUNC_COS: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return dv::builtins::cos(arg->value);
        }
        case TokenType::BUILTIN_FUNC_TAN: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return dv::builtins::tan(arg->value);
        }
        case TokenType::BUILTIN_FUNC_SEC: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return dv::builtins::sec(arg->value);
        }
        case TokenType::BUILTIN_FUNC_CSC: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return dv::builtins::csc(arg->value);
        }
        case TokenType::BUILTIN_FUNC_COT: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return dv::builtins::cot(arg->value);
        }
        case TokenType::BUILTIN_FUNC_LOG: {
            const auto &call = std::get<ASTCall>(ast->data);
            auto arg = call.args[0]->evaluate(evalulator);
            if(!arg) return arg;
            if(!call.special_value) return dv::builtins::log(arg->value);
            auto base = call.special_value->evaluate(evalulator);
            if(!base) return base;
            return dv::builtins::log(arg->value, base->value);
        }
        case TokenType::ABSOLUTE_BAR:
        case TokenType::BUILTIN_FUNC_ABS: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return dv::builtins::abs(*arg);
        }
        case TokenType::BUILTIN_FUNC_NCR: {
            const auto &args = std::get<ASTCall>(ast->data).args;
            auto a = args[0]->evaluate(evalulator);
            if(!a) return a;
            auto b = args[1]->evaluate(evalulator);
            if(!b) return b;
            return dv::builtins::nCr(a->value, b->value);
        }
        case TokenType::BUILTIN_FUNC_NPR: {
            const auto &args = std::get<ASTCall>(ast->data).args;
            auto a = args[0]->evaluate(evalulator);
            if(!a) return a;
            auto b = args[1]->evaluate(evalulator);
            if(!b) return b;
            return dv::builtins::nPr(a->value, b->value);
        }
        case TokenType::BUILTIN_FUNC_SQRT: {
            const auto &call = std::get<ASTCall>(ast->data);
            auto arg = call.args[0]->evaluate(evalulator);
            if(!arg) return arg;
            if(!call.special_value) return dv::builtins::nthsqrt(*arg, 2.0);
            auto n = call.special_value->evaluate(evalulator);
            if(!n) return n;
            return dv::builtins::nthsqrt(*arg, n->value);
        }
        case TokenType::BUILTIN_FUNC_CEIL: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return dv::builtins::ceil(*arg);
        }
        case TokenType::BUILTIN_FUNC_FACT: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return dv::builtins::factorial(*arg);
        }
        case TokenType::BUILTIN_FUNC_FLOOR: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return dv::builtins::floor(*arg);
        }
        case TokenType::BUILTIN_FUNC_ROUND: {
            const auto &args = std::get<ASTCall>(ast->data).args;
            auto a = args[0]->evaluate(evalulator);
            if(!a) return a;
            auto b = args[1]->evaluate(evalulator);
            if(!b) return b;
            return dv::builtins::round(*a, b->value);
        }
        case TokenType::BUILTIN_FUNC_ARCSIN: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return dv::builtins::arcsin(arg->value);
        }
        case TokenType::BUILTIN_FUNC_ARCCOS: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return dv::builtins::arccos(arg->value);
        }
        case TokenType::BUILTIN_FUNC_ARCTAN: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return dv::builtins::arctan(arg->value);
        }
        case TokenType::BUILTIN_FUNC_ARCSEC: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return dv::builtins::arcsec(arg->value);
        }
        case TokenType::BUILTIN_FUNC_ARCCSC: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return dv::builtins::arccsc(arg->value);
        }
        case TokenType::BUILTIN_FUNC_ARCCOT: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return dv::builtins::arccot(arg->value);
        }
        case TokenType::BUILTIN_FUNC_VALUE: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return EValue{arg->value};
        }
        case TokenType::BUILTIN_FUNC_UNIT: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return EValue{1.0, arg->unit};
        }
        case TokenType::FORMULA_QUERY:
            return std::unexpected<std::string>{"'?' can only be used as '? = (unit)' to search for formulas"};
        default: break;
    }
    return std::unexpected{std::format("Unsupported expression (token: '{}')", ast->token.text)};
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
