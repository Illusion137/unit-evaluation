cmake_minimum_required(VERSION 3.20)
project(DimensionalEvaluation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
file(GLOB_RECURSE SRC_FILES "${SOURCE_DIR}/*.cpp")
list(REMOVE_ITEM SRC_FILES "${SOURCE_DIR}/main.cpp")

add_library(DimensionalCore STATIC ${SRC_FILES})

target_compile_options(DimensionalCore PRIVATE
    -Wall -O3 -Wno-reorder-init-list
)

add_executable(
    DimensionalEvaluation
    src/main.cpp
    ${SRC_FILES}
)
target_compile_options(DimensionalEvaluation PRIVATE -Wall -O3 -Wno-reorder-init-list)

if(EMSCRIPTEN)
    add_executable(DimensionalEvaluationWasm ${SRC_FILES})

    target_compile_options(DimensionalEvaluationWasm PRIVATE
        -O3
    )

    target_link_options(DimensionalEvaluationWasm PRIVATE
        -sMODULARIZE=1
        -sEXPORT_ES6=1
        -sENVIRONMENT=web
        -sWASM=1
    )

    set_target_properties(DimensionalEvaluationWasm PROPERTIES
        OUTPUT_NAME "dimensional"
        SUFFIX ".js"
    )
endif()