#include "testing.hpp"
#include <cstdlib>
#include <span>

int main(){
    static const std::vector<LatexTest> ALL_TESTS = {
        // basic
        {"1+2",3},{"5-7",-2},{"3\\cdot4",12},{"8/2",4},{"2^3",8},
        {"2^{3^2}",512},{"(2^3)^2",64},{"7+3\\cdot2",13},{"(7+3)\\cdot2",20},{"-5+2",-3},

        // fractions & roots
        {"\\frac{1}{2}",0.5},{"\\frac{3}{4}",0.75},{"\\frac{2+2}{4}",1.0},
        {"\\frac{10}{2+3}",2.0},{"\\sqrt{4}",2.0},{"\\sqrt{9+7}",4.0},
        {"\\sqrt{16}+2",6.0},{"\\sqrt{2^2+2^2}",std::sqrt(8.0)},

        // abs & factorial
        {"|-5|",5},{"|3-7|",4},{"5!",120},{"3!+4!",30},{"4!/(2!)",12},{"|-3!|",6},

        // trig (radians)
        {"\\sin(0)",0},{"\\cos(0)",1},{"\\tan(0)",0},
        {"\\sin(\\pi/2)",1},{"\\cos(\\pi)",-1},
        {"\\sin(\\pi/6)",0.5},{"\\cos(\\pi/3)",0.5},{"\\tan(\\pi/4)",1},

        // mixed
        {"2^{1+2}",8},{"\\sqrt{2^4}",4},{"\\sin(2^2)",std::sin(4)},
        {"3^\\sin(\\pi/2)",3},{"|\\cos(\\pi)|",1},
        {"\\frac{\\sin(\\pi/2)}{\\cos(0)}",1},

        // stress
        {"((2+3)\\cdot(4-1))^2",225},
        {"\\frac{2}{\\sqrt{4}}",1},
        {"2^{-3}",0.125},
        {"-(2+3)^2",-25},
        {"\\sqrt{(2+3)^2}",5},
    };
    run_non_related_tests(ALL_TESTS);

    // std::array<std::string_view, 5> expressions = {
    //     "a = 10",
    //     "2^2a",
    //     "k\\frac{e_ce_c}{1.0}",
    //     "5!",
    //     "2^2",
    // };

    // dv::Evaluator evaluator{};
    // const auto evaled = evaluator.evaluate_expression_list(expressions);
    // for(const auto &eval : evaled){
    //     if(!eval) std::println("[ERROR]: {}", eval.error());
    //     else std::println("[VALUE]: {}", eval.value().value);
    // }

    // auto end = std::chrono::steady_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    // auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    // std::println("Time taken: {}ms OR {}μs", duration.count(), microseconds);

    // const auto result = root.value()->evaluate();
    // std::println("{} = {} {}", test_input, result.value, result.unit.vec);

    return EXIT_SUCCESS;
}