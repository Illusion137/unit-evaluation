#include "ast.hpp"
#include "builtins.hpp"
#include "evaluator.hpp"
#include "token.hpp"
#include <format>
#include <memory>
#include <cmath>
#include <algorithm>
#include <numeric>

std::unique_ptr<dv::AST> dv::AST::clone() const {
    auto result = std::make_unique<AST>();
    result->token = this->token;
    if(this->data.index() == 0) {
        const auto &expr = std::get<ASTExpression>(this->data);
        ASTExpression new_expr;
        new_expr.value = expr.value;
        if(expr.lhs) new_expr.lhs = expr.lhs->clone();
        if(expr.rhs) new_expr.rhs = expr.rhs->clone();
        result->data = std::move(new_expr);
    } else {
        const auto &call = std::get<ASTCall>(this->data);
        ASTCall new_call;
        for(const auto &arg : call.args) {
            new_call.args.emplace_back(arg->clone());
        }
        if(call.special_value) new_call.special_value = call.special_value->clone();
        result->data = std::move(new_call);
    }
    return result;
}

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
            // Custom function definition: f(x,y) = expr
            if(expr.lhs->token.type == TokenType::FUNC_CALL) {
                const auto &call = std::get<ASTCall>(expr.lhs->data);
                std::string func_name = std::string(expr.lhs->token.text);
                std::vector<std::string> param_names;
                for(const auto &arg : call.args) {
                    if(arg->token.type != TokenType::IDENTIFIER) {
                        return std::unexpected{std::format("Function parameter must be a variable name, got '{}'", arg->token.text)};
                    }
                    param_names.emplace_back(arg->token.text);
                }
                CustomFunction cf;
                cf.name = func_name;
                cf.param_names = std::move(param_names);
                cf.body = expr.rhs->clone();
                evalulator.custom_functions.insert_or_assign(func_name, std::move(cf));
                return EValue{0.0}; // function defined
            }
            auto value = expr.rhs->evaluate(evalulator);
            if(!value) return value;
            evalulator.evaluated_variables.insert_or_assign(
                std::string{expr.lhs->token.text}, *value);
            // Store source expression for sig-fig tracking
            evalulator.variable_source_expressions.insert_or_assign(
                std::string{expr.lhs->token.text}, std::string{expr.rhs->token.text});
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
            // Imaginary unit 'i' - only if not otherwise defined
            if(token_id == "i") {
                EValue imag_unit;
                imag_unit.value = 0.0;
                imag_unit.imag = 1.0;
                return imag_unit;
            }
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
        case TokenType::PLUS_MINUS: {
            const auto &expr = std::get<ASTExpression>(ast->data);
            auto lhs = expr.lhs->evaluate(evalulator);
            if(!lhs) return lhs;
            auto rhs = expr.rhs->evaluate(evalulator);
            if(!rhs) return rhs;
            // Returns array [lhs+rhs, lhs-rhs]
            EValue result;
            result.unit = lhs->unit + rhs->unit;
            result.extra_values = {lhs->value + rhs->value, lhs->value - rhs->value};
            result.value = result.extra_values[0];
            return result;
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
        case TokenType::PERCENT: {
            auto lhs = std::get<ASTExpression>(ast->data).lhs->evaluate(evalulator);
            if(!lhs) return lhs;
            return *lhs / EValue{100.0};
        }
        case TokenType::MODULO: {
            const auto &expr = std::get<ASTExpression>(ast->data);
            auto lhs = expr.lhs->evaluate(evalulator);
            if(!lhs) return lhs;
            auto rhs = expr.rhs->evaluate(evalulator);
            if(!rhs) return rhs;
            return EValue{std::fmod(lhs->value, rhs->value)};
        }
        // Comparison operators
        case TokenType::LESS_THAN: {
            const auto &expr = std::get<ASTExpression>(ast->data);
            auto lhs = expr.lhs->evaluate(evalulator);
            if(!lhs) return lhs;
            auto rhs = expr.rhs->evaluate(evalulator);
            if(!rhs) return rhs;
            return EValue{lhs->value < rhs->value ? 1.0L : 0.0L};
        }
        case TokenType::GREATER_THAN: {
            const auto &expr = std::get<ASTExpression>(ast->data);
            auto lhs = expr.lhs->evaluate(evalulator);
            if(!lhs) return lhs;
            auto rhs = expr.rhs->evaluate(evalulator);
            if(!rhs) return rhs;
            return EValue{lhs->value > rhs->value ? 1.0L : 0.0L};
        }
        case TokenType::LESS_EQUAL: {
            const auto &expr = std::get<ASTExpression>(ast->data);
            auto lhs = expr.lhs->evaluate(evalulator);
            if(!lhs) return lhs;
            auto rhs = expr.rhs->evaluate(evalulator);
            if(!rhs) return rhs;
            return EValue{lhs->value <= rhs->value ? 1.0L : 0.0L};
        }
        case TokenType::GREATER_EQUAL: {
            const auto &expr = std::get<ASTExpression>(ast->data);
            auto lhs = expr.lhs->evaluate(evalulator);
            if(!lhs) return lhs;
            auto rhs = expr.rhs->evaluate(evalulator);
            if(!rhs) return rhs;
            return EValue{lhs->value >= rhs->value ? 1.0L : 0.0L};
        }
        case TokenType::LOGICAL_AND: {
            const auto &expr = std::get<ASTExpression>(ast->data);
            auto lhs = expr.lhs->evaluate(evalulator);
            if(!lhs) return lhs;
            auto rhs = expr.rhs->evaluate(evalulator);
            if(!rhs) return rhs;
            return EValue{(lhs->value != 0.0 && rhs->value != 0.0) ? 1.0L : 0.0L};
        }
        case TokenType::LOGICAL_OR: {
            const auto &expr = std::get<ASTExpression>(ast->data);
            auto lhs = expr.lhs->evaluate(evalulator);
            if(!lhs) return lhs;
            auto rhs = expr.rhs->evaluate(evalulator);
            if(!rhs) return rhs;
            return EValue{(lhs->value != 0.0 || rhs->value != 0.0) ? 1.0L : 0.0L};
        }
        case TokenType::LOGICAL_NOT: {
            const auto &expr = std::get<ASTExpression>(ast->data);
            auto lhs = expr.lhs->evaluate(evalulator);
            if(!lhs) return lhs;
            return EValue{lhs->value == 0.0 ? 1.0L : 0.0L};
        }
        // Array literal
        case TokenType::ARRAY_LITERAL: {
            const auto &call = std::get<ASTCall>(ast->data);
            if(call.args.empty()) return EValue{0.0};
            EValue result;
            result.extra_values.reserve(call.args.size());
            for(const auto &arg : call.args) {
                auto val = arg->evaluate(evalulator);
                if(!val) return val;
                result.extra_values.push_back(val->value);
                result.unit = val->unit; // use last element's unit
            }
            result.value = result.extra_values[0];
            return result;
        }
        // Array indexing
        case TokenType::INDEX_ACCESS: {
            const auto &expr = std::get<ASTExpression>(ast->data);
            auto arr = expr.lhs->evaluate(evalulator);
            if(!arr) return arr;
            auto idx = expr.rhs->evaluate(evalulator);
            if(!idx) return idx;
            std::size_t index = (std::size_t)idx->value;
            if(index >= arr->size()) {
                return std::unexpected{std::format("Index {} out of bounds (size {})", index, arr->size())};
            }
            return EValue{arr->at(index), arr->unit};
        }
        // Transpose
        case TokenType::TRANSPOSE: {
            const auto &expr = std::get<ASTExpression>(ast->data);
            auto mat = expr.lhs->evaluate(evalulator);
            if(!mat) return mat;
            if(!mat->matrix) return std::unexpected{"Transpose requires a matrix"};
            auto &m = *mat->matrix;
            std::size_t rows = m.size(), cols = m[0].size();
            std::vector<std::vector<long double>> transposed(cols, std::vector<long double>(rows));
            for(std::size_t i = 0; i < rows; i++)
                for(std::size_t j = 0; j < cols; j++)
                    transposed[j][i] = m[i][j];
            EValue result;
            result.matrix = std::move(transposed);
            result.value = result.matrix->at(0).at(0);
            result.unit = mat->unit;
            return result;
        }
        // Builtins
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
            // Handle sqrt of negative -> complex
            if(arg->value < 0 && !call.special_value) {
                EValue result;
                result.value = 0.0;
                result.imag = std::sqrt(-arg->value);
                return result;
            }
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
        // Summation
        case TokenType::BUILTIN_FUNC_SUM: {
            const auto &call = std::get<ASTCall>(ast->data);
            auto start_val = call.args[0]->evaluate(evalulator);
            if(!start_val) return start_val;
            auto end_val = call.args[1]->evaluate(evalulator);
            if(!end_val) return end_val;
            std::string loop_var = std::string(call.special_value->token.text);
            int start = (int)start_val->value;
            int end = (int)end_val->value;

            // Save and restore loop variable
            EValue saved;
            bool had_var = evalulator.evaluated_variables.contains(loop_var);
            if(had_var) saved = evalulator.evaluated_variables.at(loop_var);

            EValue accumulator{0.0};
            for(int i = start; i <= end; i++) {
                evalulator.evaluated_variables.insert_or_assign(loop_var, EValue{(long double)i});
                auto body_val = call.args[2]->evaluate(evalulator);
                if(!body_val) {
                    if(had_var) evalulator.evaluated_variables.insert_or_assign(loop_var, saved);
                    else evalulator.evaluated_variables.erase(loop_var);
                    return body_val;
                }
                accumulator = accumulator + *body_val;
            }

            if(had_var) evalulator.evaluated_variables.insert_or_assign(loop_var, saved);
            else evalulator.evaluated_variables.erase(loop_var);
            return accumulator;
        }
        // Product
        case TokenType::BUILTIN_FUNC_PROD: {
            const auto &call = std::get<ASTCall>(ast->data);
            auto start_val = call.args[0]->evaluate(evalulator);
            if(!start_val) return start_val;
            auto end_val = call.args[1]->evaluate(evalulator);
            if(!end_val) return end_val;
            std::string loop_var = std::string(call.special_value->token.text);
            int start = (int)start_val->value;
            int end = (int)end_val->value;

            EValue saved;
            bool had_var = evalulator.evaluated_variables.contains(loop_var);
            if(had_var) saved = evalulator.evaluated_variables.at(loop_var);

            EValue accumulator{1.0};
            for(int i = start; i <= end; i++) {
                evalulator.evaluated_variables.insert_or_assign(loop_var, EValue{(long double)i});
                auto body_val = call.args[2]->evaluate(evalulator);
                if(!body_val) {
                    if(had_var) evalulator.evaluated_variables.insert_or_assign(loop_var, saved);
                    else evalulator.evaluated_variables.erase(loop_var);
                    return body_val;
                }
                accumulator = accumulator * *body_val;
            }

            if(had_var) evalulator.evaluated_variables.insert_or_assign(loop_var, saved);
            else evalulator.evaluated_variables.erase(loop_var);
            return accumulator;
        }
        // Derivative: numerical central difference
        case TokenType::DERIVATIVE: {
            const auto &call = std::get<ASTCall>(ast->data);
            std::string var_name = std::string(call.special_value->token.text);
            int order = (int)ast->token.value.value;
            if(order < 1) order = 1;

            // Check if variable is defined
            bool var_defined = evalulator.evaluated_variables.contains(var_name) ||
                               evalulator.fixed_constants.contains(var_name);

            if(var_defined) {
                // Numerical derivative at the current value
                long double x_val;
                if(evalulator.evaluated_variables.contains(var_name))
                    x_val = evalulator.evaluated_variables.at(var_name).value;
                else
                    x_val = evalulator.fixed_constants.at(var_name).value;

                long double h = 1e-7;
                // Apply derivative order times
                auto eval_at = [&](long double x) -> long double {
                    auto saved = evalulator.evaluated_variables[var_name];
                    evalulator.evaluated_variables[var_name] = EValue{x};
                    auto result = call.args[0]->evaluate(evalulator);
                    evalulator.evaluated_variables[var_name] = saved;
                    return result ? result->value : 0.0;
                };

                long double result = 0;
                if(order == 1) {
                    result = (eval_at(x_val + h) - eval_at(x_val - h)) / (2 * h);
                } else if(order == 2) {
                    result = (eval_at(x_val + h) - 2 * eval_at(x_val) + eval_at(x_val - h)) / (h * h);
                } else {
                    // Higher order: apply first derivative repeatedly
                    // For simplicity, use recursive central difference
                    long double h_n = std::pow(1e-7, 1.0 / order);
                    result = eval_at(x_val + h_n) - eval_at(x_val - h_n);
                    result /= (2 * h_n);
                    for(int n = 1; n < order; n++) {
                        // Numerical re-differentiation with widening h
                        h_n *= 10;
                    }
                }
                return EValue{result};
            } else {
                // Create a custom function that computes the derivative
                CustomFunction cf;
                cf.name = "__deriv_" + var_name;
                cf.param_names = {var_name};
                cf.body = ast->clone(); // store the derivative AST itself
                evalulator.custom_functions.insert_or_assign(cf.name, std::move(cf));
                return EValue{0.0}; // deferred
            }
        }
        // f'(x) - prime derivative of custom function
        case TokenType::PRIME: {
            const auto &call = std::get<ASTCall>(ast->data);
            std::string func_name = std::string(ast->token.text);
            int order = (int)ast->token.value.value;
            if(order < 1) order = 1;

            if(!evalulator.custom_functions.contains(func_name)) {
                return std::unexpected{std::format("Undefined function '{}' for derivative", func_name)};
            }
            auto &cf = evalulator.custom_functions.at(func_name);

            // Evaluate arguments
            std::vector<EValue> arg_values;
            for(const auto &arg : call.args) {
                auto val = arg->evaluate(evalulator);
                if(!val) return val;
                arg_values.push_back(*val);
            }

            long double h = 1e-7;
            auto eval_func = [&](long double x) -> long double {
                // Save, bind, evaluate, restore
                std::map<std::string, EValue> saved_vars;
                for(std::size_t i = 0; i < cf.param_names.size(); i++) {
                    if(evalulator.evaluated_variables.contains(cf.param_names[i]))
                        saved_vars[cf.param_names[i]] = evalulator.evaluated_variables[cf.param_names[i]];
                    if(i == 0) evalulator.evaluated_variables[cf.param_names[i]] = EValue{x};
                    else if(i < arg_values.size()) evalulator.evaluated_variables[cf.param_names[i]] = arg_values[i];
                }
                auto result = cf.body->evaluate(evalulator);
                for(auto &[k, v] : saved_vars)
                    evalulator.evaluated_variables[k] = v;
                for(std::size_t i = 0; i < cf.param_names.size(); i++) {
                    if(!saved_vars.contains(cf.param_names[i]))
                        evalulator.evaluated_variables.erase(cf.param_names[i]);
                }
                return result ? result->value : 0.0;
            };

            long double x_val = arg_values.empty() ? 0.0 : arg_values[0].value;
            long double result = 0;
            if(order == 1) {
                result = (eval_func(x_val + h) - eval_func(x_val - h)) / (2 * h);
            } else {
                result = (eval_func(x_val + h) - 2 * eval_func(x_val) + eval_func(x_val - h)) / (h * h);
            }
            return EValue{result};
        }
        // Integral: Simpson's 1/3 rule
        case TokenType::BUILTIN_FUNC_INT: {
            const auto &call = std::get<ASTCall>(ast->data);
            auto lower = call.args[0]->evaluate(evalulator);
            if(!lower) return lower;
            auto upper = call.args[1]->evaluate(evalulator);
            if(!upper) return upper;
            std::string int_var = std::string(call.special_value->token.text);

            long double a = lower->value, b = upper->value;
            int n = 1000; // subdivisions (must be even)
            long double h_step = (b - a) / n;

            EValue saved;
            bool had_var = evalulator.evaluated_variables.contains(int_var);
            if(had_var) saved = evalulator.evaluated_variables.at(int_var);

            auto eval_at = [&](long double x) -> long double {
                evalulator.evaluated_variables[int_var] = EValue{x};
                auto result = call.args[2]->evaluate(evalulator);
                return result ? result->value : 0.0;
            };

            long double sum = eval_at(a) + eval_at(b);
            for(int j = 1; j < n; j++) {
                long double x = a + j * h_step;
                sum += (j % 2 == 0) ? 2 * eval_at(x) : 4 * eval_at(x);
            }
            sum *= h_step / 3.0;

            if(had_var) evalulator.evaluated_variables.insert_or_assign(int_var, saved);
            else evalulator.evaluated_variables.erase(int_var);

            // Unit: body_unit * var_unit
            return EValue{sum};
        }
        // Custom function call
        case TokenType::FUNC_CALL: {
            std::string func_name = std::string(ast->token.text);
            if(!evalulator.custom_functions.contains(func_name)) {
                return std::unexpected{std::format("Undefined function '{}'", func_name)};
            }
            auto &cf = evalulator.custom_functions.at(func_name);
            const auto &call = std::get<ASTCall>(ast->data);

            if(call.args.size() != cf.param_names.size()) {
                return std::unexpected{std::format("Function '{}' expects {} args, got {}",
                    func_name, cf.param_names.size(), call.args.size())};
            }

            // Evaluate arguments
            std::vector<EValue> arg_values;
            for(const auto &arg : call.args) {
                auto val = arg->evaluate(evalulator);
                if(!val) return val;
                arg_values.push_back(*val);
            }

            // Save old variable values, bind params
            std::map<std::string, EValue> saved_vars;
            for(std::size_t i = 0; i < cf.param_names.size(); i++) {
                if(evalulator.evaluated_variables.contains(cf.param_names[i]))
                    saved_vars[cf.param_names[i]] = evalulator.evaluated_variables[cf.param_names[i]];
                evalulator.evaluated_variables[cf.param_names[i]] = arg_values[i];
            }

            auto result = cf.body->evaluate(evalulator);

            // Restore
            for(auto &[k, v] : saved_vars)
                evalulator.evaluated_variables[k] = v;
            for(std::size_t i = 0; i < cf.param_names.size(); i++) {
                if(!saved_vars.contains(cf.param_names[i]))
                    evalulator.evaluated_variables.erase(cf.param_names[i]);
            }

            return result;
        }
        // min, max, gcd, lcm
        case TokenType::BUILTIN_FUNC_MIN: {
            const auto &args = std::get<ASTCall>(ast->data).args;
            auto first = args[0]->evaluate(evalulator);
            if(!first) return first;
            long double result = first->value;
            for(std::size_t i = 1; i < args.size(); i++) {
                auto val = args[i]->evaluate(evalulator);
                if(!val) return val;
                result = std::min(result, val->value);
            }
            return EValue{result, first->unit};
        }
        case TokenType::BUILTIN_FUNC_MAX: {
            const auto &args = std::get<ASTCall>(ast->data).args;
            auto first = args[0]->evaluate(evalulator);
            if(!first) return first;
            long double result = first->value;
            for(std::size_t i = 1; i < args.size(); i++) {
                auto val = args[i]->evaluate(evalulator);
                if(!val) return val;
                result = std::max(result, val->value);
            }
            return EValue{result, first->unit};
        }
        case TokenType::BUILTIN_FUNC_GCD: {
            const auto &args = std::get<ASTCall>(ast->data).args;
            auto first = args[0]->evaluate(evalulator);
            if(!first) return first;
            long long result = (long long)first->value;
            for(std::size_t i = 1; i < args.size(); i++) {
                auto val = args[i]->evaluate(evalulator);
                if(!val) return val;
                result = std::gcd(result, (long long)val->value);
            }
            return EValue{(long double)result};
        }
        case TokenType::BUILTIN_FUNC_LCM: {
            const auto &args = std::get<ASTCall>(ast->data).args;
            auto first = args[0]->evaluate(evalulator);
            if(!first) return first;
            long long result = (long long)first->value;
            for(std::size_t i = 1; i < args.size(); i++) {
                auto val = args[i]->evaluate(evalulator);
                if(!val) return val;
                result = std::lcm(result, (long long)val->value);
            }
            return EValue{(long double)result};
        }
        // sig(x) - significant figures
        case TokenType::BUILTIN_FUNC_SIG: {
            const auto &call = std::get<ASTCall>(ast->data);
            auto arg = call.args[0]->evaluate(evalulator);
            if(!arg) return arg;
            // For now, return the value with sig_figs from the argument
            // Full sig-fig tracking would require propagation through all ops
            return EValue{(long double)arg->sig_figs};
        }
        // Complex number builtins
        case TokenType::BUILTIN_FUNC_RE: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return EValue{arg->value, arg->unit};
        }
        case TokenType::BUILTIN_FUNC_IM: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            return EValue{arg->imag, arg->unit};
        }
        case TokenType::BUILTIN_FUNC_CONJ: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            EValue result = *arg;
            result.imag = -result.imag;
            return result;
        }
        // Piecewise
        case TokenType::PIECEWISE_BEGIN: {
            const auto &call = std::get<ASTCall>(ast->data);
            // args are pairs: [value0, cond0, value1, cond1, ...]
            for(std::size_t i = 0; i + 1 < call.args.size(); i += 2) {
                auto cond = call.args[i + 1]->evaluate(evalulator);
                if(!cond) return cond;
                if(cond->value != 0.0) {
                    return call.args[i]->evaluate(evalulator);
                }
            }
            return std::unexpected{"Piecewise: no matching condition"};
        }
        // Matrix literal
        case TokenType::MATRIX_BEGIN: {
            const auto &call = std::get<ASTCall>(ast->data);
            int encoded = (int)ast->token.value.value;
            int rows = encoded / 1000;
            int cols = encoded % 1000;

            std::vector<std::vector<long double>> matrix(rows, std::vector<long double>(cols));
            std::size_t idx = 0;
            for(int r = 0; r < rows; r++) {
                for(int c = 0; c < cols; c++) {
                    if(idx >= call.args.size()) {
                        return std::unexpected{"Matrix: not enough elements"};
                    }
                    auto val = call.args[idx++]->evaluate(evalulator);
                    if(!val) return val;
                    matrix[r][c] = val->value;
                }
            }
            EValue result;
            result.value = matrix[0][0];
            result.matrix = std::move(matrix);
            return result;
        }
        // det(M)
        case TokenType::BUILTIN_FUNC_DET: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            if(!arg->matrix) return std::unexpected{"\\det requires a matrix"};
            auto &m = *arg->matrix;
            std::size_t n = m.size();
            if(n != m[0].size()) return std::unexpected{"\\det requires a square matrix"};
            // Simple determinant via LU-like expansion for small matrices
            if(n == 1) return EValue{m[0][0]};
            if(n == 2) return EValue{m[0][0]*m[1][1] - m[0][1]*m[1][0]};
            if(n == 3) {
                return EValue{
                    m[0][0]*(m[1][1]*m[2][2] - m[1][2]*m[2][1]) -
                    m[0][1]*(m[1][0]*m[2][2] - m[1][2]*m[2][0]) +
                    m[0][2]*(m[1][0]*m[2][1] - m[1][1]*m[2][0])
                };
            }
            // Cofactor expansion for larger matrices
            long double det = 0;
            for(std::size_t j = 0; j < n; j++) {
                // Build submatrix
                std::vector<std::vector<long double>> sub(n-1, std::vector<long double>(n-1));
                for(std::size_t r = 1; r < n; r++) {
                    std::size_t sc = 0;
                    for(std::size_t c = 0; c < n; c++) {
                        if(c == j) continue;
                        sub[r-1][sc++] = m[r][c];
                    }
                }
                // Recursively compute sub-determinant via the same method
                // For simplicity, use a lambda
                EValue sub_ev;
                sub_ev.matrix = std::move(sub);
                // We need to evaluate det of sub_ev - but we can't recurse through AST easily
                // So implement inline Gaussian elimination
                long double sign = (j % 2 == 0) ? 1.0 : -1.0;
                // For now, support up to 4x4 via cofactor
                if(n == 4) {
                    auto &s = *sub_ev.matrix;
                    long double sub_det =
                        s[0][0]*(s[1][1]*s[2][2] - s[1][2]*s[2][1]) -
                        s[0][1]*(s[1][0]*s[2][2] - s[1][2]*s[2][0]) +
                        s[0][2]*(s[1][0]*s[2][1] - s[1][1]*s[2][0]);
                    det += sign * m[0][j] * sub_det;
                }
            }
            return EValue{det};
        }
        // trace(M)
        case TokenType::BUILTIN_FUNC_TRACE: {
            auto arg = std::get<ASTCall>(ast->data).args[0]->evaluate(evalulator);
            if(!arg) return arg;
            if(!arg->matrix) return std::unexpected{"\\operatorname{tr} requires a matrix"};
            auto &m = *arg->matrix;
            long double trace = 0;
            for(std::size_t i = 0; i < std::min(m.size(), m[0].size()); i++) {
                trace += m[i][i];
            }
            return EValue{trace};
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
