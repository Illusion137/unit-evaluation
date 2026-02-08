# emcmake cmake -B build-wasm -S .
emcmake cmake -S . -B build-wasm
cmake --build build-wasm
# cd build
# cmake --build .
# ./DimensionalEvaluation