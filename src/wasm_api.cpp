#include "evaluator.hpp"
#include "value_utils.hpp"
#include <cmath>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#define WASM_EXPORT EMSCRIPTEN_KEEPALIVE
#else
#define WASM_EXPORT
#endif

using namespace dv;

static Evaluator* g_eval = nullptr;

extern "C" {

// ============================================================================
// Lifecycle Management
// ============================================================================

WASM_EXPORT
bool dv_init() {
    if (g_eval) return false; // Already initialized
    g_eval = new Evaluator();
    return true;
}

WASM_EXPORT
void dv_destroy() {
    delete g_eval;
    g_eval = nullptr;
}

WASM_EXPORT
bool dv_is_initialized() {
    return g_eval != nullptr;
}

// ============================================================================
// Constants Management
// ============================================================================

WASM_EXPORT
bool dv_set_constant(const char* name, const char* value_expr, const char* unit_expr) {
    if (!g_eval || !name || !value_expr) return false;
    Expression expr{value_expr, unit_expr ? unit_expr : ""};
    g_eval->insert_constant(name, expr);
    return true;
}

WASM_EXPORT
bool dv_remove_constant(const char* name) {
    if (!g_eval || !name) return false;
    return g_eval->fixed_constants.erase(name) > 0;
}

WASM_EXPORT
void dv_clear_constants() {
    if (g_eval) g_eval->fixed_constants.clear();
}

WASM_EXPORT
int dv_get_constant_count() {
    return g_eval ? static_cast<int>(g_eval->fixed_constants.size()) : 0;
}

// ============================================================================
// Single Expression Evaluation
// ============================================================================

struct dv_result {
    long double value;
    int8_t unit[7];
    bool success;
    char error[256];
    char unit_latex[256];
    char value_scientific[256];
};

WASM_EXPORT
dv_result dv_eval(const char* value_expr, const char* unit_expr) {
    dv_result result = {};

    if (!g_eval) {
        strncpy(result.error, "Evaluator not initialized", sizeof(result.error) - 1);
        return result;
    }

    if (!value_expr) {
        strncpy(result.error, "Null expression", sizeof(result.error) - 1);
        return result;
    }

    Expression expr{value_expr, unit_expr ? unit_expr : ""};
    std::vector<Expression> exprs = {expr};
    auto results = g_eval->evaluate_expression_list(exprs);

    if (results[0]) {
        const auto& ev = results[0].value();
        result.value = ev.value;
        memcpy(result.unit, ev.unit.vec.data(), 7 * sizeof(int8_t));
        result.success = true;

        auto latex = unit_to_latex(ev.unit);
        strncpy(result.unit_latex, latex.c_str(), sizeof(result.unit_latex) - 1);
        result.unit_latex[sizeof(result.unit_latex) - 1] = '\0';

        auto sci = value_to_scientific(ev.value);
        strncpy(result.value_scientific, sci.c_str(), sizeof(result.value_scientific) - 1);
        result.value_scientific[sizeof(result.value_scientific) - 1] = '\0';
    } else {
        strncpy(result.error, results[0].error().c_str(), sizeof(result.error) - 1);
        result.error[sizeof(result.error) - 1] = '\0';
    }

    return result;
}

// ============================================================================
// Batch Evaluation (Multiple Expressions)
// ============================================================================

struct dv_batch_result {
    long double* values;
    int8_t** units;
    bool* successes;
    char** errors;
    char** unit_latexes;
    char** value_scientifics;
    int count;
};

WASM_EXPORT
dv_batch_result* dv_eval_batch(const char** value_exprs, const char** unit_exprs, int count) {
    if (!g_eval || !value_exprs || count <= 0) return nullptr;

    auto* batch = (dv_batch_result*)malloc(sizeof(dv_batch_result));
    batch->count = count;
    batch->values = (long double*)malloc(sizeof(long double) * count);
    batch->units = (int8_t**)malloc(sizeof(int8_t*) * count);
    for (int i = 0; i < count; i++) {
        batch->units[i] = (int8_t*)malloc(sizeof(int8_t) * 7);
    }
    batch->successes = (bool*)malloc(sizeof(bool) * count);
    batch->errors = (char**)malloc(sizeof(char*) * count);
    batch->unit_latexes = (char**)malloc(sizeof(char*) * count);
    batch->value_scientifics = (char**)malloc(sizeof(char*) * count);

    std::vector<Expression> exprs;
    exprs.reserve(count);
    for (int i = 0; i < count; i++) {
        std::string unit = (unit_exprs && unit_exprs[i]) ? unit_exprs[i] : "";
        exprs.push_back(Expression{value_exprs[i], std::move(unit)});
    }

    auto results = g_eval->evaluate_expression_list(exprs);

    for (int i = 0; i < count; i++) {
        if (results[i]) {
            const auto& ev = results[i].value();
            batch->values[i] = ev.value;
            memcpy(batch->units[i], ev.unit.vec.data(), 7 * sizeof(int8_t));
            batch->successes[i] = true;
            batch->errors[i] = nullptr;

            auto latex = unit_to_latex(ev.unit);
            batch->unit_latexes[i] = (char*)malloc(latex.length() + 1);
            strcpy(batch->unit_latexes[i], latex.c_str());

            auto sci = value_to_scientific(ev.value);
            batch->value_scientifics[i] = (char*)malloc(sci.length() + 1);
            strcpy(batch->value_scientifics[i], sci.c_str());
        } else {
            batch->values[i] = std::nan("");
            memset(batch->units[i], 0, 7 * sizeof(int8_t));
            batch->successes[i] = false;
            batch->unit_latexes[i] = nullptr;
            batch->value_scientifics[i] = nullptr;

            const auto& err = results[i].error();
            batch->errors[i] = (char*)malloc(err.length() + 1);
            strcpy(batch->errors[i], err.c_str());
        }
    }

    return batch;
}

WASM_EXPORT
void dv_free_batch_result(dv_batch_result* batch) {
    if (!batch) return;

    free(batch->values);
    for (int i = 0; i < batch->count; i++) {
        free(batch->units[i]);
        free(batch->errors[i]);
        free(batch->unit_latexes[i]);
        free(batch->value_scientifics[i]);
    }
    free(batch->units);
    free(batch->successes);
    free(batch->errors);
    free(batch->unit_latexes);
    free(batch->value_scientifics);

    free(batch);
}

// ============================================================================
// Formula Search
// ============================================================================

struct dv_formula_list {
    char** names;
    char** latexes;
    char** categories;
    int count;
};

WASM_EXPORT
dv_formula_list* dv_get_available_formulas(const int8_t* target_unit) {
    if (!g_eval || !target_unit) return nullptr;

    UnitVector target;
    memcpy(target.vec.data(), target_unit, 7);

    auto formulas = g_eval->get_available_formulas(target);

    auto* list = (dv_formula_list*)malloc(sizeof(dv_formula_list));
    list->count = static_cast<int>(formulas.size());
    list->names = (char**)malloc(sizeof(char*) * list->count);
    list->latexes = (char**)malloc(sizeof(char*) * list->count);
    list->categories = (char**)malloc(sizeof(char*) * list->count);

    for (int i = 0; i < list->count; i++) {
        list->names[i] = (char*)malloc(formulas[i].name.length() + 1);
        strcpy(list->names[i], formulas[i].name.c_str());

        list->latexes[i] = (char*)malloc(formulas[i].latex.length() + 1);
        strcpy(list->latexes[i], formulas[i].latex.c_str());

        list->categories[i] = (char*)malloc(formulas[i].category.length() + 1);
        strcpy(list->categories[i], formulas[i].category.c_str());
    }

    return list;
}

WASM_EXPORT
void dv_free_formula_list(dv_formula_list* list) {
    if (!list) return;

    for (int i = 0; i < list->count; i++) {
        free(list->names[i]);
        free(list->latexes[i]);
        free(list->categories[i]);
    }
    free(list->names);
    free(list->latexes);
    free(list->categories);

    free(list);
}

// ============================================================================
// Variables Management
// ============================================================================

WASM_EXPORT
bool dv_get_variable(const char* name, long double* out_value) {
    if (!g_eval || !name || !out_value) return false;

    auto it = g_eval->evaluated_variables.find(name);
    if (it == g_eval->evaluated_variables.end()) return false;

    *out_value = it->second.value;
    return true;
}

WASM_EXPORT
void dv_clear_variables() {
    if (g_eval) g_eval->evaluated_variables.clear();
}

WASM_EXPORT
int dv_get_variable_count() {
    return g_eval ? static_cast<int>(g_eval->evaluated_variables.size()) : 0;
}

// ============================================================================
// Memory Management Helpers
// ============================================================================

WASM_EXPORT
void dv_free(void* ptr) {
    free(ptr);
}

// ============================================================================
// Version Info
// ============================================================================

WASM_EXPORT
const char* dv_version() {
    return "1.0.0";
}

} // extern "C"
