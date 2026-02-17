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
    const std::span<const dv::AssignExpression> const_expressions = {
        std::initializer_list<const dv::AssignExpression>{
            {.identifier = "e_c", .value_expr = "1.602*10^{-19}", .unit_expr = "\\C"},
            {.identifier = "e_0", .value_expr = "8.854187817*10^{-12}", .unit_expr = "\\frac{\\F}{\\m}"},
            {.identifier = "k_e", .value_expr = "8.99*10^9", .unit_expr = "\\frac{\\N\\m^2}{\\C^2}"},
            
            {.identifier = "c", .value_expr = "2.99792458*10^8", .unit_expr = "\\frac{\\m}{\\s}"},
            {.identifier = "m_e", .value_expr = "9.1938*10^{-31}", .unit_expr = "\\kg"},
            {.identifier = "m_p", .value_expr = "1.67262*10^{-27}", .unit_expr = "\\kg"},
            {.identifier = "m_n", .value_expr = "1.674927*10^{-27}", .unit_expr = "\\kg"},
            
            {.identifier = "h", .value_expr = "6.620607015*10^{-34}", .unit_expr = "\\J\\s"},
            {.identifier = "a_0", .value_expr = "5.291772*10^{-11}", .unit_expr = "\\m"},
            {.identifier = "N_A", .value_expr = "6.022*10^{23}", .unit_expr = "\\mol^{-1}"},
        }
    };
    for(const auto &expression : const_expressions){
        insert_constant(expression.identifier, expression);
    }
}

dv::Evaluator::Evaluator(const std::span<const dv::AssignExpression> const_expressions){
    for(const auto &expression : const_expressions){
        insert_constant(expression.identifier, expression);
    }
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
    for(auto it = this->evaluated_variables.begin(); it != this->evaluated_variables.end(); it++) {
        available_units.emplace_back(std::move(it->second.unit));
    }
    return searcher.find_by_units(available_units, target);
}

dv::MaybeASTDependencies dv::Evaluator::parse_expression(const Expression &expression){
    auto single_expr = expression.get_single_expression();
    Lexer lexer{expression.get_single_expression()};
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

dv::MaybeASTDependencies dv::Evaluator::parse_expression(const std::string &expression){
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