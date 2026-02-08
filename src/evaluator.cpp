#include "evaluator.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include <expected>
#include <numeric>
#include <vector>

std::vector<dv::Evaluator::MaybeEvaluated> dv::Evaluator::evaluate_expression_list(const std::span<const std::string_view> expression_list){
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
        evaluated[evaluation_index] = parsed_expressions[evaluation_index].value()->evaluate(*this);
    }
    
    return evaluated;
}

dv::Parser::MaybeAST dv::Evaluator::parse_expression(const std::string_view expression){
    Lexer lexer{expression};
    const auto &tokens = lexer.extract_all_tokens();
    if(!tokens) {
        return std::unexpected{tokens.error()}; 
    }
    Parser parser{tokens.value()};
    return parser.parse();
}