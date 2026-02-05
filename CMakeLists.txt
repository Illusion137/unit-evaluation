cmake_minimum_required(VERSION 3.20)
project(DimensionalEvaluation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
file(GLOB_RECURSE SRC_FILES "${SOURCE_DIR}/*.cpp")

add_executable(
    DimensionalEvaluation
    src/main.cpp
    ${SRC_FILES}
)
target_compile_options(DimensionalEvaluation PRIVATE -Wall -O3 -Wno-reorder-init-list)