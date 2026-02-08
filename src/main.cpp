#include "evaluator.hpp"
#include <cstdlib>
#include <print>
#include <span>
#include <string_view>

int main(){
    // const std::string_view test_input = "\\frac{\\log_{2}9^{2}+90!-2467\\cdot\\frac{7890}{712}+\\sqrt{673933-83445}+5^{2^{3!}}}{4783-45611\\cdot6548\\cdot\\frac{3459}{450}\\cdot\\left(732037\\right)345\\sqrt{3489201}}";
    // const std::string_view test_input = "";

    std::array<std::string_view, 5> expressions = {
        "k = 8.99\\cdot10^{9}",
        "e_c = 1.602",
        "k\\frac{e_ce_c}{1.0}",
        "x = 5!",
        "2^2",
    };

    dv::Evaluator evaluator{};
    const auto evaled = evaluator.evaluate_expression_list(expressions);
    for(const auto &eval : evaled){
        if(!eval) std::println("[ERROR]: {}", eval.error());
        else std::println("[VALUE]: {}", eval.value().value);
    }
    // const auto result = root.value()->evaluate();
    // std::println("{} = {} {}", test_input, result.value, result.unit.vec);

    return EXIT_SUCCESS;
}