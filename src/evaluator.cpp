#include "evaluator.hpp"
#include "dimeval.hpp"
#include "lexer.hpp"
#include "parser.hpp"
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

dv::Evaluator::Evaluator(){
    std::vector<dv::AssignExpression> const_expressions = {
        {"e_c", "1.602*10^{-19}", "\\C"},
        {"e_0", "8.854187817*10^{-12}", "\\frac{\\F}{\\m}"},
        {"k_e", "8.99*10^9", "\\frac{\\N\\m^2}{\\C^2}"},
        
        {"c", "2.99792458*10^8", "\\frac{\\m}{\\s}"},
        {"m_e", "9.1938*10^{-31}", "\\kg"},
        {"m_p", "1.67262*10^{-27}", "\\kg"},
        {"m_n", "1.674927*10^{-27}", "\\kg"},
        
        {"R", "8.31446", "\\J\\K^{-1}\\mol^{-1}"},
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
    std::vector<dv::MaybeASTDependencies> parsed_expressions;
    parsed_expressions.reserve(expression_list.size());
    for(const auto &expression : expression_list){
        parsed_expressions.emplace_back(parse_expression(expression));
    }
    std::vector<MaybeEvaluated> evaluated(parsed_expressions.size(), 0.0);
    std::vector<std::uint32_t> evaluation_indices(parsed_expressions.size());
    std::iota(evaluation_indices.begin(), evaluation_indices.end(), 0);
    // TODO sort this by dependencies

    for(const auto evaluation_index: evaluation_indices){
        if(!parsed_expressions[evaluation_index]) {
            evaluated[evaluation_index] = std::unexpected{parsed_expressions[evaluation_index].error()};
            continue;
        }
        evaluated[evaluation_index] = parsed_expressions[evaluation_index].value().ast->evaluate(*this);
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
    EValue value = {value_result->value, unit_result->unit};
    fixed_constants.insert_or_assign(name, std::move(value));
}

std::vector<Physics::Formula> dv::Evaluator::get_available_formulas(const dv::UnitVector &target) const noexcept {
    std::vector<dv::UnitVector> available_units;
    for(const auto &[key, value]: this->evaluated_variables) {
        available_units.push_back(value.unit);
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