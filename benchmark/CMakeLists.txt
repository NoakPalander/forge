cmake_minimum_required(VERSION 3.26)
project(forge-benchmark)

include(${CMAKE_SOURCE_DIR}/deps/CMakeLists.txt)

add_executable(forge-benchmark
    ${FORGE_SOURCES}
    benchmark.cpp)

target_include_directories(forge-benchmark PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(forge-benchmark PRIVATE cxx_std_20)
target_compile_options(forge-benchmark PRIVATE
    -Wall
    -Wextra
    -Wconversion
    -pedantic-errors
    -O3
    -ffast-math
    -march=native)

target_link_libraries(forge-benchmark PRIVATE
    fmt::fmt
    benchmark::benchmark)