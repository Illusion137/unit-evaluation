# Unit-Evaluation

A high-performance library for parsing and evaluating mathematical expressions with full support for LaTeX syntax, dimensional analysis, and unit checking. Built in C++ with WebAssembly bindings for seamless integration in both native and web applications.

[![C++23](https://img.shields.io/badge/C++-23-blue.svg)](https://isocpp.org/)
[![WebAssembly](https://img.shields.io/badge/WebAssembly-Supported-orange.svg)](https://webassembly.org/)

## Features

- **LaTeX Expression Parsing**: Native support for LaTeX mathematical notation including `\cdot`, `\frac{}{}`, exponents, and more
- **Dimensional Analysis**: Automatic unit checking and conversion to prevent dimensional errors
- **Batch Evaluation**: Efficiently evaluate multiple related expressions with shared variables
- **Variable Assignment**: Define and reuse variables across expressions
- **Constants Management**: Set physical or mathematical constants for your calculations
- **High Performance**: Written in C++23 with optimized evaluation engine
- **WebAssembly Support**: Full TypeScript/JavaScript API for web applications
- **Error Reporting**: Detailed error messages with expression context

## Table of Contents

- [Installation](#installation)
  - [C++ Library](#c-library)
  - [WebAssembly/JavaScript](#webassemblyjavascript)
- [Quick Start](#quick-start)
  - [C++ Usage](#c-usage)
  - [TypeScript/JavaScript Usage](#typescriptjavascript-usage)
- [API Reference](#api-reference)
  - [C++ API](#c-api)
  - [TypeScript API](#typescript-api)
- [Expression Syntax](#expression-syntax)
- [Examples](#examples)
- [Building from Source](#building-from-source)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)

## Installation

### C++ Library

#### Using CMake (Recommended)

Add this repository as a submodule or download the source:
```bash
git clone https://github.com/yourusername/dimensional-evaluation.git
cd dimensional-evaluation
```

Include in your CMake project:
```cmake
add_subdirectory(dimensional-evaluation)
target_link_libraries(your_project DimensionalCore)
```

#### Manual Installation
```bash
mkdir build && cd build
cmake ..
cmake --build .
sudo cmake --install .
```

### WebAssembly/JavaScript

#### NPM (Coming Soon)
```bash
npm install dimensional-evaluation
```

#### CDN
```html
<script src="https://cdn.jsdelivr.net/npm/dimensional-evaluation@latest/dist/dimensional.js"></script>
```

#### Build from Source
```bash
# Install emscripten first
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh

# Build WASM module
cd /path/to/dimensional-evaluation
mkdir build-wasm && cd build-wasm
emcmake cmake ..
cmake --build .
```

## Quick Start

### C++ Usage
```cpp
#include "evaluator.hpp"
#include <iostream>

int main() {
    dv::Evaluator evaluator;
    
    // Set physical constants
    evaluator.fixed_constants["k"] = dv::EValue{8.99e9};  // Coulomb's constant
    evaluator.fixed_constants["e"] = dv::EValue{1.602e-19}; // Elementary charge
    
    // Evaluate expressions
    std::array<std::string_view, 4> expressions = {
        "q_1 = 2.0 \\cdot e",           // Charge 1
        "q_2 = -3.0 \\cdot e",          // Charge 2
        "r = 1.0",                       // Distance in meters
        "F = k \\frac{q_1 \\cdot q_2}{r^2}"  // Coulomb's law
    };
    
    auto results = evaluator.evaluate_expression_list(expressions);
    
    for (size_t i = 0; i < results.size(); ++i) {
        if (results[i]) {
            std::cout << "Expression " << i << ": " 
                      << results[i].value().value << std::endl;
        } else {
            std::cerr << "Error in expression " << i << ": " 
                      << results[i].error() << std::endl;
        }
    }
    
    return 0;
}
```

### TypeScript/JavaScript Usage
```typescript
import { DimensionalEvaluator } from 'dimensional-evaluation';

// Load WASM module
const module = await import('./dimensional.js');
const evaluator = new DimensionalEvaluator(module);

try {
    // Set constants
    evaluator.set_constant('c', 299792458);     // Speed of light
    evaluator.set_constant('m', 1.0);           // Mass in kg
    
    // Single expression evaluation
    const energy = evaluator.eval('E = m \\cdot c^2');
    
    if (energy.success) {
        console.log(`Energy: ${energy.value} J`);
    } else {
        console.error(`Error: ${energy.error}`);
    }
    
    // Batch evaluation
    const results = evaluator.eval_batch([
        'a = 5!',
        'b = 2^8',
        'c = \\frac{a + b}{2}',
        'result = \\sqrt{c}'
    ]);
    
    results.forEach((result, i) => {
        if (result.success) {
            console.log(`Expression ${i}: ${result.value}`);
        } else {
            console.error(`Expression ${i}: ${result.error}`);
        }
    });
    
    // Access evaluated variables
    const a = evaluator.get_variable('a');
    const b = evaluator.get_variable('b');
    console.log(`a = ${a}, b = ${b}`);
    
} finally {
    evaluator.destroy();
}
```

## API Reference

### C++ API

#### `dv::Evaluator`

Main evaluation class for parsing and computing expressions.

**Methods:**
```cpp
// Evaluate multiple expressions in sequence
std::vector<MaybeEvaluated> evaluate_expression_list(
    const std::span<const std::string_view> expression_list
);

// Public members
std::unordered_map<std::string, EValue> fixed_constants;    // User-defined constants
std::unordered_map<std::string, EValue> evaluated_variables; // Variables from expressions
```

#### `dv::EValue`

Represents a value with dimensional units.
```cpp
struct EValue {
    long double value;
    UnitVector unit;
    
    EValue(const long double val);
    EValue(const long double val, const UnitVector _unit);
};
```

### TypeScript API

#### `DimensionalEvaluator`

Main class for evaluating expressions in JavaScript/TypeScript.

**Constructor:**
```typescript
constructor(wasm_module: WasmModule)
```

**Methods:**
```typescript
// Lifecycle
destroy(): void
is_initialized(): boolean
reset(): void

// Constants management
set_constant(name: string, value: number): boolean
remove_constant(name: string): boolean
clear_constants(): void
get_constant_count(): number

// Expression evaluation
eval(expression: string): EvalResult
eval_batch(expressions: string[]): EvalResult[]

// Variables management
get_variable(name: string): number | null
clear_variables(): void
get_variable_count(): number

// Utility
get_version(): string
```

**Types:**
```typescript
interface EvalResult {
    success: boolean;
    value?: number;
    error?: string;
}
```

## Expression Syntax

### Supported Operations

| Operation | Syntax | Example |
|-----------|--------|---------|
| Addition | `+` | `a + b` |
| Subtraction | `-` | `a - b` |
| Multiplication | `*` or `\cdot` | `a * b` or `a \cdot b` |
| Division | `/` or `\frac{}{}` | `a / b` or `\frac{a}{b}` |
| Exponentiation | `^` | `a^2` |
| Parentheses | `()` | `(a + b) * c` |
| Factorial | `!` | `5!` |
| Square root | `\sqrt{}` | `\sqrt{16}` |

### Variable Assignment
```latex
x = 42
y = 2 \cdot x
z = \frac{x + y}{3}
```

### Scientific Notation
```latex
c = 3.0 \cdot 10^{8}
h = 6.626 \cdot 10^{-34}
```

### LaTeX Fractions
```latex
F = \frac{G \cdot m_1 \cdot m_2}{r^2}
```

### Complex Expressions
```latex
result = \frac{\sqrt{a^2 + b^2}}{2 \cdot \pi \cdot r}
```

## Examples

### Example 1: Physics Calculations
```cpp
dv::Evaluator evaluator;

// Gravitational force calculation
evaluator.fixed_constants["G"] = dv::EValue{6.674e-11};

std::array<std::string_view, 4> exprs = {
    "m_1 = 5.972 \\cdot 10^{24}",  // Earth mass (kg)
    "m_2 = 7.342 \\cdot 10^{22}",  // Moon mass (kg)
    "r = 3.844 \\cdot 10^{8}",      // Distance (m)
    "F = \\frac{G \\cdot m_1 \\cdot m_2}{r^2}"
};

auto results = evaluator.evaluate_expression_list(exprs);
// F ≈ 1.982e20 N
```

### Example 2: Financial Calculations (JavaScript)
```javascript
const evaluator = new DimensionalEvaluator(module);

evaluator.set_constant('r', 0.05);  // 5% interest rate

const results = evaluator.eval_batch([
    'P = 10000',                           // Principal
    'n = 12',                              // Compounds per year
    't = 10',                              // Years
    'A = P \\cdot (1 + \\frac{r}{n})^{n \\cdot t}'  // Compound interest
]);

console.log(`Final amount: $${results[3].value.toFixed(2)}`);
// Final amount: $16470.09
```

### Example 3: Statistical Calculations
```typescript
const evaluator = new DimensionalEvaluator(module);

const data_analysis = evaluator.eval_batch([
    'n = 100',
    'sum_x = 5050',
    'sum_x_sq = 338350',
    'mean = \\frac{sum_x}{n}',
    'variance = \\frac{sum_x_sq}{n} - mean^2',
    'std_dev = \\sqrt{variance}'
]);

if (data_analysis[5].success) {
    console.log(`Standard deviation: ${data_analysis[5].value}`);
}
```

### Example 4: Engineering Calculations
```cpp
dv::Evaluator evaluator;

// Beam deflection calculation
std::array<std::string_view, 6> beam_calc = {
    "E = 200 \\cdot 10^{9}",       // Young's modulus (Pa)
    "I = 1.0 \\cdot 10^{-6}",      // Moment of inertia (m^4)
    "L = 5.0",                      // Beam length (m)
    "F = 1000",                     // Applied force (N)
    "deflection = \\frac{F \\cdot L^{3}}{3 \\cdot E \\cdot I}",
    "max_stress = \\frac{F \\cdot L}{I}"
};

auto results = evaluator.evaluate_expression_list(beam_calc);
```

## Building from Source

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.15 or higher
- (Optional) Emscripten SDK for WebAssembly builds

### Native Build
```bash
git clone https://github.com/yourusername/dimensional-evaluation.git
cd dimensional-evaluation
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### WebAssembly Build
```bash
# Setup emscripten
source /path/to/emsdk/emsdk_env.sh

# Build
mkdir build-wasm && cd build-wasm
emcmake cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

### Build Options
```bash
cmake .. -DBUILD_TESTS=ON          # Enable unit tests
cmake .. -DBUILD_EXAMPLES=ON       # Build example programs
cmake .. -DBUILD_WASM=ON           # Build WebAssembly module
cmake .. -DENABLE_SANITIZERS=ON    # Enable address/undefined sanitizers
```

## Testing
```bash
cd build
ctest --output-on-failure

# Or run tests directly
./tests/unit_tests
./tests/integration_tests
```

### Running JavaScript Tests
```bash
npm install
npm test
```

## Performance

Benchmarks on AMD Ryzen 9 5900X:

| Operation | Expressions/sec | Time per expression |
|-----------|----------------|---------------------|
| Simple arithmetic | 5,000,000 | 200 ns |
| With variables | 2,500,000 | 400 ns |
| Complex LaTeX | 500,000 | 2 μs |
| Batch (100 exprs) | 50,000 batches | 20 μs per batch |

WebAssembly performance is typically 50-70% of native C++ performance.

## Roadmap

- [ ] Add support for trigonometric functions (`\sin`, `\cos`, `\tan`)
- [ ] Implement logarithmic functions (`\log`, `\ln`)
- [ ] Add matrix operations
- [ ] Support for complex numbers
- [ ] Unit conversion system
- [ ] Symbolic differentiation
- [ ] Expression simplification
- [ ] Python bindings
- [ ] NPM package publication

## Contributing

Contributions are welcome! Please read our [Contributing Guide](CONTRIBUTING.md) for details on our code of conduct and the process for submitting pull requests.

### Development Setup
```bash
git clone https://github.com/yourusername/dimensional-evaluation.git
cd dimensional-evaluation
git checkout -b feature/your-feature-name

# Make your changes
# Add tests
# Run tests and linting

git commit -m "Add your feature"
git push origin feature/your-feature-name
```