#include "lexer.hpp"
#include "parser.hpp"
#include <cstdlib>
#include <print>
#include <string_view>

int main(){
    const std::string_view test_input = "2^{3^{\\cos\\left(1\\right)}}+6";
    // const std::string_view test_input = "x = 5\\cos(2\\pi) + \\nCr(5, 2)";
    // const std::string_view test_input = "(5 + 2 * 10 * (5 - 4)) / 2";
    // const std::string_view test_input = "5\\left(\\arcsin\\cos^{-1}\\left(x\\right)\\right)+\\frac{2^2}{3^2}-3\\cdot3+e_c+m_{electron}+\\frac{1}{2}mv^2-1!-3\\pi\\lambda+\\sqrt[3]{2^{\\pi}}";
    // const std::string_view test_input = "5\\sqrt[3]{4}+\\log_2\\left(\\ln\\left(x\\right)\\right)\\alpha_{27}";
    
    dv::Lexer lexer{test_input};
    const auto tokens = lexer.extract_all_tokens();
    if(!tokens){
        std::println("{}", tokens.error());
        return 1;
    }
    std::println("{}", tokens.value());
    dv::Parser parser{tokens.value()};
    const auto root = parser.parse();
    if(!root){
        std::println("{}", root.error());
        return 1;
    }
    std::println("{}", *root.value());
    const auto result = root.value()->evaluate();
    std::println("{} = {} {}", test_input, result.value, result.unit.vec);

    return EXIT_SUCCESS;
}