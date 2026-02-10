# emcmake cmake -B build-wasm -S .
emcmake cmake -S . -B build-wasm
cmake --build build-wasm
rm /Users/illusion/dev/diptych/public/wasm/UnitEval.js
rm /Users/illusion/dev/diptych/public/wasm/UnitEval.wasm
mv build-wasm/UnitEval.js /Users/illusion/dev/diptych/public/wasm/UnitEval.js
mv build-wasm/UnitEval.wasm /Users/illusion/dev/diptych/public/wasm/UnitEval.wasm