cmake_minimum_required(VERSION 3.20)
project(UnitEval LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
file(GLOB_RECURSE SRC_FILES "${SOURCE_DIR}/*.cpp")
list(REMOVE_ITEM SRC_FILES "${SOURCE_DIR}/main.cpp")

if(EMSCRIPTEN)
    add_executable(UnitEvalWasm ${SRC_FILES})

    target_compile_options(UnitEvalWasm PRIVATE
        -O3
    )

    target_link_options(UnitEvalWasm PRIVATE
        -sWASM=1
        -sMODULARIZE=1
        -sEXPORT_ES6=0
        -sENVIRONMENT=web
        -sALLOW_MEMORY_GROWTH=1
        -sFILESYSTEM=0
        # -sEXPORTED_RUNTIME_METHODS=['ccall','cwrap','HEAP8','HEAPU8','HEAPU32','HEAP32','HEAPF64','HEAPF32']
        # -sEXPORTED_FUNCTIONS=['_malloc','_free']
        -lembind
        --emit-tsd UnitEval.d.ts
    )

    set_target_properties(UnitEvalWasm PROPERTIES
        OUTPUT_NAME "UnitEval"
        SUFFIX ".js"
    )
    target_include_directories(UnitEvalWasm PRIVATE /Users/illusion/dev/emsdk/upstream/emscripten/system/include/)
else()
    # add_library(UnitEvalCore STATIC ${SRC_FILES})

    # target_compile_options(UnitEvalCore PRIVATE
    #     -Wall -O3 -Wno-reorder-init-list
    # )

    # list(REMOVE_ITEM SRC_FILES "${SOURCE_DIR}/wasm_api.cpp")
    add_executable(
        UnitEval
        src/main.cpp
        ${SRC_FILES}
    )
    target_compile_options(UnitEval PRIVATE -Wall -O3 -Wno-reorder-init-list)
    target_include_directories(UnitEval PRIVATE /Users/illusion/dev/emsdk/upstream/emscripten/system/include/)
endif()