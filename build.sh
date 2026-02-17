# emcmake cmake -B build-wasm -S .
emcmake cmake -S . -B build-wasm
cmake --build build-wasm
rm /Users/illusion/dev/Everett/public/wasm/UnitEval.js
rm /Users/illusion/dev/Everett/public/wasm/UnitEval.wasm
rm /Users/illusion/dev/Everett/src/dimension_wasm_interface.ts
cp build-wasm/UnitEval.js /Users/illusion/dev/Everett/public/wasm/UnitEval.js
cp build-wasm/UnitEval.wasm /Users/illusion/dev/Everett/public/wasm/UnitEval.wasm
cp dimension_wasm_interface.ts /Users/illusion/dev/Everett/src/dimension_wasm_interface.ts