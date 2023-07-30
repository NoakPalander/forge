cmake_minimum_required(VERSION 3.26)
project(forge-test)

include(${CMAKE_SOURCE_DIR}/deps/CMakeLists.txt)

add_executable(forge-test
    ${FORGE_SOURCES}
    test.cpp)

target_include_directories(forge-test PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(forge-test PRIVATE cxx_std_20)
target_compile_options(forge-test PRIVATE
    -Wall
    -Wextra
    -Wconversion
    -pedantic-errors
    -ggdb3
    -O0
    -fsanitize=address,undefined,
    -fno-omit-frame-pointer)

target_link_options(forge-test PRIVATE -fsanitize=address,undefined)
target_link_libraries(forge-test PRIVATE
    fmt::fmt
    Catch2::Catch2WithMain)