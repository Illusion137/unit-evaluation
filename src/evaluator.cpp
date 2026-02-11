#include "evaluator.hpp"
#include "dimeval.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include <expected>
#include <numeric>
#include <vector>
#ifdef EVAL_PRINT_AST
#include <print>
#endif

std::vector<dv::Evaluator::MaybeEvaluated> dv::Evaluator::evaluate_expression_list(const std::span<const std::string_view> expression_list){
    evaluated_variables.clear();
    std::vector<dv::Parser::MaybeAST> parsed_expressions;
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
        try {
            evaluated[evaluation_index] = parsed_expressions[evaluation_index].value()->evaluate(*this);
        } catch (const std::runtime_error& e) {
            evaluated[evaluation_index] = std::unexpected{e.what()};
        }
    }
    
    return evaluated;
}

void dv::Evaluator::insert_constant(const std::string_view name, const std::string_view expression, const std::string_view unit_expression){
    auto parsed_expression = parse_expression(expression);
    auto parsed_unit_expression = parse_expression(unit_expression);
    if(!parsed_expression || !parsed_unit_expression) return;
    EValue value = {parsed_expression.value()->evaluate(*this).value, parsed_unit_expression.value()->evaluate(*this).unit};
    fixed_constants.insert_or_assign(std::string{name}, std::move(value));
}

dv::Parser::MaybeAST dv::Evaluator::parse_expression(const std::string_view expression){
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