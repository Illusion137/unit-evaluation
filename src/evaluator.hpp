#pragma once

#include "dimeval.hpp"
#include <expected>
#include <span>
#include <unordered_map>
#include <vector>

namespace dv {
    struct AST;
    class Evaluator {
        public:
        using MaybeAST = std::expected<std::unique_ptr<AST>, std::string>;
        using MaybeEvaluated = std::expected<EValue, std::string>;
        std::vector<MaybeEvaluated> evaluate_expression_list(const std::span<const std::string_view> expression_list); 
        std::unordered_map<std::string, EValue> fixed_constants;
        std::unordered_map<std::string, EValue> evaluated_variables;
    private:
        MaybeAST parse_expression(const std::string_view expression);
    };
}