cmake_minimum_required(VERSION 3.26)
project(forge)

set(FORGE_SOURCES
    ${CMAKE_SOURCE_DIR}/include/forge/matrix.hpp
    ${CMAKE_SOURCE_DIR}/include/forge/row_iterator.hpp
    ${CMAKE_SOURCE_DIR}/include/forge/col_iterator.hpp
    ${CMAKE_SOURCE_DIR}/include/forge/math.hpp
    ${CMAKE_SOURCE_DIR}/include/forge/elem.hpp)

include(${CMAKE_SOURCE_DIR}/deps/CMakeLists.txt)
add_subdirectory(test)
add_subdirectory(benchmark)

add_executable(forge
    ${FORGE_SOURCES}
    src/main.cpp)

target_include_directories(forge PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(forge PRIVATE cxx_std_20)
target_compile_options(forge PRIVATE
    -Wall
    -Wextra
    -Wconversion
    -pedantic-errors
    -ggdb3
    -O0
    -fsanitize=address,undefined,
    -fno-omit-frame-pointer)

target_link_options(forge PRIVATE -fsanitize=address,undefined)
target_link_libraries(forge PRIVATE fmt::fmt)