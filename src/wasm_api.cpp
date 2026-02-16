#include "evaluator.hpp"
#include <cmath>
#include <cstdint>
#include <cstring>
#include <string>

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
bool dv_set_constant(const char* name, const char* expression, const char* unit_expression) {
    if (!g_eval || !name) return false;
    g_eval->insert_constant(name, expression, unit_expression);
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
};

WASM_EXPORT
dv_result dv_eval(const char* expr) {
    dv_result result = {0.0, { 0 }, false, ""};
    
    if (!g_eval) {
        strncpy(result.error, "Evaluator not initialized", sizeof(result.error) - 1);
        return result;
    }
    
    if (!expr) {
        strncpy(result.error, "Null expression", sizeof(result.error) - 1);
        return result;
    }
    
    std::vector<std::string_view> views = {expr};
    auto results = g_eval->evaluate_expression_list(views);
    
    if (results[0]) {
        result.value = results[0].value().value;
        memcpy(result.unit, results[0].value().unit.vec.data(), 7 * sizeof(int8_t));
        result.success = true;
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
    long double* values;      // Array of results
    int8_t** units;      // Array of units
    bool* successes;     // Array of success flags
    char** errors;       // Array of error messages (NULL if success)
    int count;
};

WASM_EXPORT
dv_batch_result* dv_eval_batch(const char** exprs, int count) {
    if (!g_eval || !exprs || count <= 0) return nullptr;
    
    // Allocate result structure
    auto* batch = (dv_batch_result*)malloc(sizeof(dv_batch_result));
    batch->count = count;
    batch->values = (long double*)malloc(sizeof(long double) * count);
    batch->units = (int8_t**)malloc(sizeof(int8_t*) * count);
    for(int32_t i = 0; i < count; i++){
        batch->units[i] = (int8_t*)malloc(sizeof(int8_t) * 7);
    }
    batch->successes = (bool*)malloc(sizeof(bool) * count);
    batch->errors = (char**)malloc(sizeof(char*) * count);
    
    // Prepare expression views
    std::vector<std::string_view> views;
    views.reserve(count);
    for (int i = 0; i < count; ++i) {
        views.emplace_back(exprs[i]);
    }
    
    // Evaluate
    auto results = g_eval->evaluate_expression_list(views);
    
    // Process results
    for (int i = 0; i < count; ++i) {
        if (results[i]) {
            batch->values[i] = results[i].value().value;
            memcpy(batch->units[i], results[i].value().unit.vec.data(), 7 * sizeof(int8_t));
            batch->successes[i] = true;
            batch->errors[i] = nullptr;
        } else {
            batch->values[i] = std::nan("");
            memset(batch->units[i], 0, 7 * sizeof(int8_t));
            batch->values[i] = std::nan("");
            batch->successes[i] = false;
            
            // Allocate and copy error message
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
    for(int32_t i = 0; i < batch->count; i++){
        free(batch->units[i]);
    }
    free(batch->units);
    free(batch->successes);
    
    // Free individual error strings
    for (int i = 0; i < batch->count; ++i) {
        free(batch->errors[i]);
    }
    free(batch->errors);
    
    free(batch);
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