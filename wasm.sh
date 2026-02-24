export CMAKE_BUILD_PARALLEL_LEVEL=8
emcc eval.cpp \
    -O3 \
    -s WASM=1 \
    -s MODULARIZE=1 \
    -s EXPORT_NAME="MathCore" \
    -s EXPORTED_FUNCTIONS='["_eval","_setVar"]' \
    -s EXPORTED_RUNTIME_METHODS='["ccall"]'
