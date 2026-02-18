import all_formulas from "./all_formulas.json"
import fs from 'fs';

function to_formula_list(formulas: (typeof all_formulas[0])[]): string {
    return formulas.map((f) => {
        const vars = f.variables.map((v: any) => {
            const unit = `{${v.unit.join(', ')}}`;
            return `{"${v.name}", ${unit}, "${v.description}", ${v.constant}}`;
        }).join(',');

        return `\t\tthis->formulas.emplace_back("${f.name}", "${f.latex}", std::vector<Variable>{${vars}}, "${f.solve_for}");`;
    }).join('\n');
}
const str = `#include "physics_formulas.hpp"

namespace Physics {
    FormulaDatabase::FormulaDatabase() {
        this->formulas.reserve(2000);
${to_formula_list(all_formulas).replaceAll('\\', '\\\\')}
    }
} // namespace Physics
`

fs.writeFileSync("src/formulas/physics_formulas_main.cpp", str);