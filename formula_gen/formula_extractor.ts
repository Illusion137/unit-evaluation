import fs from "fs";
import { rearrangeLatex } from "./rearrange";
import formulas_dynamics from "./formulas_dynamics.json"
import formulas_gravity from "./formulas_gravity.json"
import formulas_modern_physics from "./formulas_modern_physics.json"
import formulas_electrostatics from "./formulas_electrostatics.json"
import formulas_inductance from "./formulas_inductance.json"
import formulas_optics from "./formulas_optics.json"
import formulas_capacitance from "./formulas_capacitance.json"
import formulas_energy_momentum from "./formulas_energy_momentum.json"
import formulas_induction from "./formulas_induction.json"
import formulas_oscillations_waves from "./formulas_oscillations_waves.json"
import formulas_chemistry from "./formulas_chemistry.json"
import formulas_engineering from "./formulas_engineering.json"
import formulas_kinematics from "./formulas_kinematics.json"
import formulas_rotational from "./formulas_rotational.json"
import formulas_current_resistance from "./formulas_current_resistance.json"
import formulas_fluids from "./formulas_fluids.json"
import formulas_magnetic_sources from "./formulas_magnetic_sources.json"
import formulas_thermodynamics from "./formulas_thermodynamics.json"
import formulas_dc_circuits from "./formulas_dc_circuits.json"
import formulas_geometry from "./formulas_geometry.json"
import formulas_magnetism from "./formulas_magnetism.json"

function parse_pushbacks_to_json(input: string): (typeof formulas_dynamics[0])[] {
    const results: (typeof formulas_dynamics[0])[] = [];

    // Find each push_back block using brace depth tracking instead of regex
    let i = 0;
    while (i < input.length) {
        const pushBackIdx = input.indexOf('formulas.push_back({', i);
        if (pushBackIdx === -1) break;

        // Find the matching closing }); by tracking brace depth
        const bodyStart = pushBackIdx + 'formulas.push_back('.length;
        let depth = 0;
        let bodyEnd = -1;

        for (let j = bodyStart; j < input.length; j++) {
            if (input[j] === '{') depth++;
            else if (input[j] === '}') {
                depth--;
                if (depth === 0) {
                    bodyEnd = j;
                    break;
                }
            }
        }

        if (bodyEnd === -1) break;

        const body = input.slice(bodyStart + 1, bodyEnd); // contents inside outermost { }
        i = bodyEnd + 1;

        // ---- Extract top-level quoted strings (name, latex, category, group, solveFor) ----
        // We need to find quoted strings at the TOP level (not inside the variables block)
        // Strategy: find the variables block first, then extract strings before/after it

        // Find the variables block: it starts after the second top-level comma
        // Walk through body tracking depth to find top-level commas
        const topLevelCommaPositions: number[] = [];
        let d = 0;
        for (let j = 0; j < body.length; j++) {
            if (body[j] === '{') d++;
            else if (body[j] === '}') d--;
            else if (body[j] === ',' && d === 0) {
                topLevelCommaPositions.push(j);
            }
        }

        if (topLevelCommaPositions.length < 2) continue;

        // Segment 0: name  (before first top-level comma)
        // Segment 1: latex (between 1st and 2nd top-level comma)
        // Segment 2: variables block (between 2nd and 3rd top-level comma)
        // Segment 3: category
        // Segment 4: group
        // Segment 5: solveFor

        const segments = [
            body.slice(0, topLevelCommaPositions[0]),
            body.slice(topLevelCommaPositions[0] + 1, topLevelCommaPositions[1]),
            body.slice(topLevelCommaPositions[1] + 1, topLevelCommaPositions[2]),
            body.slice(topLevelCommaPositions[2] + 1, topLevelCommaPositions[3]),
            body.slice(topLevelCommaPositions[3] + 1, topLevelCommaPositions[4]),
            body.slice(topLevelCommaPositions[4] + 1),
        ];

        const extractString = (s: string): string | null => {
            const m = s.match(/^\s*"((?:[^"\\]|\\.)*)"\s*$/);
            return m ? m[1] : null;
        };

        const name = extractString(segments[0])?.replace(/ \(.+?\)/, '');
        const latex = extractString(segments[1])?.replaceAll("\\\\", '\\');

        if (!name || !latex) continue;

        // ---- Parse variables block ----
        const varsOuter = segments[2].trim();
        // Should start and end with { }
        if (!varsOuter.startsWith('{') || !varsOuter.endsWith('}')) continue;
        const varsBlock = varsOuter.slice(1, -1); // strip outer braces

        const variables: (typeof formulas_dynamics[0])['variables'] = [];

        // Walk through varsBlock finding each top-level { } entry
        let vi = 0;
        while (vi < varsBlock.length) {
            const start = varsBlock.indexOf('{', vi);
            if (start === -1) break;

            let vDepth = 0;
            let end = -1;
            for (let j = start; j < varsBlock.length; j++) {
                if (varsBlock[j] === '{') vDepth++;
                else if (varsBlock[j] === '}') {
                    vDepth--;
                    if (vDepth === 0) {
                        end = j;
                        break;
                    }
                }
            }

            if (end === -1) break;

            const entry = varsBlock.slice(start + 1, end);
            vi = end + 1;

            // Find top-level commas within this entry to split into 4 parts
            const entryCommas: number[] = [];
            let ed = 0;
            for (let j = 0; j < entry.length; j++) {
                if (entry[j] === '{') ed++;
                else if (entry[j] === '}') ed--;
                else if (entry[j] === ',' && ed === 0) entryCommas.push(j);
            }

            if (entryCommas.length < 3) continue;

            const entrySegments = [
                entry.slice(0, entryCommas[0]),
                entry.slice(entryCommas[0] + 1, entryCommas[1]),
                // dims array spans from entryCommas[1] to the last comma before bool
                entry.slice(entryCommas[1] + 1, entryCommas[entryCommas.length - 1]),
                entry.slice(entryCommas[entryCommas.length - 1] + 1),
            ];

            const varName = extractString(entrySegments[0]);
            const description = extractString(entrySegments[2].replace(/^\s*\{[^}]*\}\s*,\s*/, ''));
            const constant = entrySegments[3].trim() === 'true';

            // Extract the {dims} block
            const dimsMatch = entrySegments[1].match(/\{([^}]*)\}/);
            if (!varName || !dimsMatch || !description) continue;

            const unit = dimsMatch[1].split(',').map((n) => parseInt(n.trim(), 10));
            variables.push({ name: varName, unit, description, constant });
        }

        results.push({ name, latex, variables });
    }

    return results;
}

const formlua_list = [
    ...formulas_dynamics,
    ...formulas_gravity,
    ...formulas_modern_physics,
    ...formulas_electrostatics,
    ...formulas_inductance,
    ...formulas_optics,
    ...formulas_capacitance,
    ...formulas_energy_momentum,
    ...formulas_induction,
    ...formulas_oscillations_waves,
    ...formulas_chemistry,
    ...formulas_engineering,
    ...formulas_kinematics,
    ...formulas_rotational,
    ...formulas_current_resistance,
    ...formulas_fluids,
    ...formulas_magnetic_sources,
    ...formulas_thermodynamics,
    ...formulas_dc_circuits,
    ...formulas_geometry,
    ...formulas_magnetism,
    ...parse_pushbacks_to_json(fs.readFileSync("./formula_gen/ALL.txt").toString("utf-8"))
];

const output_formulas: (typeof formlua_list[0] & { solve_for: string })[] = [];
const seen_latex = new Set<string>([]);

for (const formula of formlua_list) {
    const formula_arangements = rearrangeLatex(formula.latex);
    for (const arangement of formula_arangements) {
        if (arangement.solved === false) continue;
        if (seen_latex.has(arangement.latex)) continue;
        output_formulas.push(
            {
                ...formula,
                latex: arangement.latex,
                solve_for: arangement.variable
            }
        );
        seen_latex.add(arangement.latex);
    }
}

fs.writeFileSync("formula_gen/all_formulas.json", JSON.stringify(output_formulas));
// console.log(JSON.stringify(output_formulas.length));