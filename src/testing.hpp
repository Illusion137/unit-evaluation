#include "evaluator.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include <array>
#include <print>
#include <span>
#include <string_view>
struct LatexTest {
    const std::string_view expression;
    const double expected_result;
};

static inline void print_ast_red(const std::string_view view){
    dv::Lexer lexer{view};
    const auto &tokens = lexer.extract_all_tokens();
    if(!tokens) return;
    dv::Parser parser{tokens.value()};
    const auto &ast = parser.parse();
    if(!ast) return;
    std::print("\033[31m");
    std::println("{}", *ast.value());
    std::print("\033[0m\n");
}

static inline bool run_non_related_tests(const std::span<const LatexTest> tests){
    constexpr double epsilon = 0.001;
    std::int32_t passed = 0;
    bool success = true;
    for(const auto &test: tests){
        std::array<std::string_view, 1> single_expression_list = {test.expression};
        dv::Evaluator evaluator{};
        const auto &eval = evaluator.evaluate_expression_list(single_expression_list);
        const auto &value = eval[0];
        if(!value){
            success = false;
            std::println("\033[31m[FAIL] {} = ERROR({}) ✗\033[0m", test.expression, value.error());
            continue;
        }
        if(std::fabs(value.value().value - test.expected_result) > epsilon){
            success = false;
            std::println("\033[31m[FAIL] {} = {} : Expected → {} ✗\033[0m", test.expression, value.value().value, test.expected_result);
            print_ast_red(test.expression);
            continue;
        }
        else {
            passed++;
            std::println("\033[0;32m[PASS] {} = {} ✓\033[0m", test.expression, test.expected_result);
        }
    }
    std::println("\033[31m[FAILED] {} \033[0m: \033[0;32m[PASSED] {}\033[0m", tests.size() - passed, passed);
    return success;
}