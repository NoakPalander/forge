#include <benchmark/benchmark.h>
#include <forge/matrix.hpp>
#include <forge/math.hpp>

static void matrix_multiplication(benchmark::State& state) {
    forge::Matrix<int> lhs({1, 2, 3, 4, 5, 6}, 2, 3);
    forge::Matrix<int> rhs({7, 8, 9, 10, 11, 12}, 3, 2);

    for (auto _ : state) {
        auto r = forge::math::multiply(lhs, rhs);
    }
}

static void matrix_multiplication_loop(benchmark::State& state) {
    forge::Matrix<int> lhs({1, 2, 3, 4, 5, 6}, 2, 3);
    forge::Matrix<int> rhs({7, 8, 9, 10, 11, 12}, 3, 2);

    for (auto _ : state) {
        auto r = forge::math::multiply_loop(lhs, rhs);
    }
}

BENCHMARK(matrix_multiplication);
BENCHMARK(matrix_multiplication_loop);

BENCHMARK_MAIN();