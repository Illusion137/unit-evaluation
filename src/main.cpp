#include "lexer.hpp"
#include <cstdlib>
#include <string_view>

int main(){
    const std::string_view test_input = "5\\left(\\arcsin\\cos^{-1}\\left(x\\right)\\right)+\\frac{2^2}{3^2}-3\\cdot3+e_c+m_{electron}+\\frac{1}{2}mv^2-1!-3\\pi\\lambda+\\sqrt[3]{2^{\\pi}}";
    // const std::string_view test_input = "5\\sqrt[3]{4}+\\log_2\\left(\\ln\\left(x\\right)\\right)\\alpha_{27}";
    
    dv::Lexer lexer = {test_input};
    lexer.extract_all_tokens();

    return EXIT_SUCCESS;
}