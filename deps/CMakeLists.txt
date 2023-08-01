include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt
    GIT_TAG master
)

set(BENCHMARK_ENABLE_GTEST_TESTS OFF)

FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark
    GIT_TAG v1.8.2
)

FetchContent_MakeAvailable(Catch2)
FetchContent_MakeAvailable(fmt)
FetchContent_MakeAvailable(benchmark)