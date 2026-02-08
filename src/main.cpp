#include "lexer.hpp"
#include "parser.hpp"
#include <cstdlib>
#include <print>
#include <string_view>

int main(){
    const std::string_view test_input = "\\frac{\\log_{2}9^{2}+90!-2467\\cdot\\frac{7890}{712}+\\sqrt{673933-83445}+5^{2^{3!}}}{4783-45611\\cdot6548\\cdot\\frac{3459}{450}\\cdot\\left(732037\\right)345\\sqrt{3489201}}";
    
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