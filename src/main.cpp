#include "lexer.hpp"
#include "parser.hpp"
#include <cstdlib>
#include <print>
#include <string_view>

int main(){
    const std::string_view test_input = "\\cos^{-1}(\\frac{1.41421356237}{2})";
    // const std::string_view test_input = "(5 + 2 * 10 * (5 - 4)) / 2";
    // const std::string_view test_input = "5\\left(\\arcsin\\cos^{-1}\\left(x\\right)\\right)+\\frac{2^2}{3^2}-3\\cdot3+e_c+m_{electron}+\\frac{1}{2}mv^2-1!-3\\pi\\lambda+\\sqrt[3]{2^{\\pi}}";
    // const std::string_view test_input = "5\\sqrt[3]{4}+\\log_2\\left(\\ln\\left(x\\right)\\right)\\alpha_{27}";
    
    dv::Lexer lexer{test_input};
    const auto tokens = lexer.extract_all_tokens();
    std::println("{}", tokens);
    dv::Parser parser{tokens};
    const auto root = parser.parse();
    std::println("{}", *root);
    const auto result = root->evaluate();
    std::println("{} = {}", test_input, result.value);

    return EXIT_SUCCESS;
}