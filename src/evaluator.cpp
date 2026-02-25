#include "evaluator.hpp"
#include "dimeval.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "ast.hpp"
#include <expected>
#include <format>
#include <initializer_list>
#include <numeric>
#include <vector>
#ifdef EVAL_PRINT_AST
#include <print>
#endif

std::string dv::Expression::get_single_expression() const {
    const std::string& unit = unit_expr.empty() ? std::string("1") : unit_expr;
    auto pos = value_expr.find('=');
    if (pos != std::string::npos && pos != 0 && pos != value_expr.size() - 1 && !this->unit_expr.empty()) {
        std::string lhs = value_expr.substr(0, pos);
        std::string rhs = value_expr.substr(pos + 1);
        return std::format("{} = \\left({}\\right)\\cdot{}", lhs, rhs, unit);
    }
    if(this->unit_expr.empty()) return value_expr;
    return std::format("\\left({}\\right)\\cdot{}", value_expr, unit);
}

dv::Evaluator::~Evaluator() = default;

dv::Evaluator::Evaluator(){
    std::vector<dv::AssignExpression> const_expressions = {
        {"e_c", "1.602*10^{-19}", "\\C"},
        {"e_0", "8.854187817*10^{-12}", "\\frac{\\F}{\\m}"},
        {"k_e", "8.99*10^9", "\\frac{\\N\\m^2}{\\C^2}"},
        
        {"c", "2.99792458*10^8", "\\frac{\\m}{\\s}"},
        {"m_e", "9.1938*10^{-31}", "\\kg"},
        {"m_p", "1.67262*10^{-27}", "\\kg"},
        {"m_n", "1.674927*10^{-27}", "\\kg"},
        
        // TODO 
        // {"R", "8.31446", "\\J\\K^{-1}\\mol^{-1}"},
        {"C_K", "273.15", "\\K"},
        {"h", "6.620607015*10^{-34}", "\\J\\s"},
        {"a_0", "5.291772*10^{-11}", "\\m"},
        {"N_A", "6.022*10^{23}", "\\mol^{-1}"},
    };
    for(const auto &expression : const_expressions){
        insert_constant(expression.identifier, expression);
    }
}

// dv::Evaluator::Evaluator(const std::span<const dv::AssignExpression> const_expressions){
//     for(const auto &expression : const_expressions){
//         insert_constant(expression.identifier, expression);
//     }
// }

dv::Evaluator::MaybeEvaluated dv::Evaluator::evaluate_expression(const Expression &expression){
    auto parsed = parse_expression(expression);
    if(!parsed) return std::unexpected{parsed.error()};
    return parsed.value().ast->evaluate(*this);
}


std::vector<dv::Evaluator::MaybeEvaluated> dv::Evaluator::evaluate_expression_list(const std::span<const dv::Expression> expression_list){
    evaluated_variables.clear();
    last_formula_results.clear();
    custom_functions.clear();
    variable_source_expressions.clear();
    std::vector<dv::MaybeASTDependencies> parsed_expressions;
    parsed_expressions.reserve(expression_list.size());
    for(const auto &expression : expression_list){
        parsed_expressions.emplace_back(parse_expression(expression));
    }

    // === Leaf detection for sig_figs display formatting ===
    // An expression is a "display leaf" if:
    //   1. It references at least one user-defined variable (excluding its own output)
    //   2. Its assigned output (if any) is not referenced by any other expression
    // Only display leaves apply sig-fig-aware scientific notation.

    // Step A: extract assigned variable/function name for each expression
    std::vector<std::string> assigned_vars(parsed_expressions.size());
    for (size_t i = 0; i < parsed_expressions.size(); i++) {
        if (!parsed_expressions[i]) continue;
        const auto* root = parsed_expressions[i].value().ast.get();
        if (root->token.type == TokenType::EQUAL) {
            const auto* expr_data = std::get_if<dv::AST::ASTExpression>(&root->data);
            if (expr_data && expr_data->lhs) {
                auto t = expr_data->lhs->token.type;
                if (t == TokenType::IDENTIFIER || t == TokenType::FUNC_CALL)
                    assigned_vars[i] = std::string(expr_data->lhs->token.text);
            }
        }
    }

    // Step B: set of all user-defined names in this batch
    std::unordered_set<std::string> user_defined_vars;
    for (const auto& v : assigned_vars)
        if (!v.empty()) user_defined_vars.insert(v);

    // Step C: for each expression, is its output referenced by any OTHER expression?
    auto is_depended_upon = [&](size_t i) -> bool {
        if (assigned_vars[i].empty()) return false;
        for (size_t j = 0; j < parsed_expressions.size(); j++) {
            if (i == j || !parsed_expressions[j]) continue;
            if (parsed_expressions[j].value().identifier_dependencies.count(assigned_vars[i]))
                return true;
        }
        return false;
    };

    // Step D: is_display_leaf — has user deps (excl. self-assignment ref) and is not depended upon
    auto is_display_leaf = [&](size_t i) -> bool {
        if (!parsed_expressions[i]) return false;
        const auto& deps = parsed_expressions[i].value().identifier_dependencies;
        const auto& self_var = assigned_vars[i];
        bool has_user_dep = false;
        for (const auto& dep : deps) {
            if (dep == self_var) continue;  // skip self (LHS parsed as IDENTIFIER)
            if (user_defined_vars.count(dep)) { has_user_dep = true; break; }
        }
        if (!has_user_dep) return false;
        return !is_depended_upon(i);
    };

    std::vector<MaybeEvaluated> evaluated(parsed_expressions.size(), EValue{UnitValue{0.0L}});
    std::vector<std::uint32_t> evaluation_indices(parsed_expressions.size());
    std::iota(evaluation_indices.begin(), evaluation_indices.end(), 0);
    // TODO sort this by dependencies

    for(const auto evaluation_index: evaluation_indices){
        if(!parsed_expressions[evaluation_index]) {
            evaluated[evaluation_index] = std::unexpected{parsed_expressions[evaluation_index].error()};
            continue;
        }
        evaluated[evaluation_index] = parsed_expressions[evaluation_index].value().ast->evaluate(*this);
        // Store last successful result as 'ans'
        if(evaluated[evaluation_index]) {
            evaluated_variables.insert_or_assign("ans", evaluated[evaluation_index].value());
        }
    }

    // Apply conversion units: divide result value by conversion factor when units match
    for (size_t i = 0; i < expression_list.size(); i++) {
        if (expression_list[i].conversion_unit_expr.empty()) continue;
        if (!evaluated[i]) continue;
        auto conv = evaluate_expression(Expression{"1", expression_list[i].conversion_unit_expr});
        if (!conv) continue;
        const auto* conv_uv = std::get_if<UnitValue>(&*conv);
        if (!conv_uv || conv_uv->value == 0.0L) continue;
        auto* result_uv = std::get_if<UnitValue>(&*evaluated[i]);
        if (!result_uv) continue;
        if (result_uv->unit != conv_uv->unit) continue;
        UnitValue converted{result_uv->value / conv_uv->value,
                            result_uv->imag  / conv_uv->value,
                            result_uv->unit};
        converted.sig_figs = result_uv->sig_figs;
        evaluated[i] = EValue{converted};
    }

    // Zero sig_figs for non-display-leaf expressions (suppress sig-fig formatting)
    for (size_t i = 0; i < evaluated.size(); i++) {
        if (!evaluated[i] || is_display_leaf(i)) continue;
        if (auto* uv = std::get_if<UnitValue>(&evaluated[i].value()))
            uv->sig_figs = 0;
        else if (auto* uvl = std::get_if<UnitValueList>(&evaluated[i].value()))
            for (auto& e : uvl->elements) e.sig_figs = 0;
    }

    return evaluated;
}

void dv::Evaluator::insert_constant(const std::string name, const Expression &expression){
    auto parsed_expression = parse_expression(expression.value_expr);
    auto parsed_unit_expression = parse_expression(expression.unit_expr);
    if(!parsed_expression || !parsed_unit_expression) return;
    auto value_result = parsed_expression.value().ast->evaluate(*this);
    auto unit_result = parsed_unit_expression.value().ast->evaluate(*this);
    if(!value_result || !unit_result) return;
    const UnitValue* vr = std::get_if<UnitValue>(&*value_result);
    const UnitValue* ur = std::get_if<UnitValue>(&*unit_result);
    if(!vr || !ur) return;
    EValue value = UnitValue{vr->value, ur->unit};
    fixed_constants.insert_or_assign(name, std::move(value));
}

std::vector<Physics::Formula> dv::Evaluator::get_available_formulas(const dv::UnitVector &target) const noexcept {
    std::vector<dv::UnitVector> available_units;
    for(const auto &[key, value]: this->evaluated_variables) {
        if(const auto* uv = std::get_if<UnitValue>(&value))
            available_units.push_back(uv->unit);
    }
    return searcher.find_by_units(available_units, target);
}

dv::MaybeASTDependencies dv::Evaluator::parse_expression(const Expression expression){
    auto single_expr = expression.get_single_expression();
    Lexer lexer{single_expr};
    const auto &tokens = lexer.extract_all_tokens();
    if(!tokens) {
        return std::unexpected{tokens.error()}; 
    }
    Parser parser{tokens.value()};
#ifdef EVAL_PRINT_AST
    auto p = parser.parse();
    std::println("{}", *p.value());
    return p;
#else
    return parser.parse();
#endif
}

dv::MaybeASTDependencies dv::Evaluator::parse_expression(const std::string expression){
    Lexer lexer{expression};
    const auto &tokens = lexer.extract_all_tokens();
    if(!tokens) {
        return std::unexpected{tokens.error()}; 
    }
    Parser parser{tokens.value()};
#ifdef EVAL_PRINT_AST
    auto p = parser.parse();
    std::println("{}", *p.value());
    return p;
#else
    return parser.parse();
#endif
}