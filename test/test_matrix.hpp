#ifndef FORGE_TEST_MATRIX_HPP
#define FORGE_TEST_MATRIX_HPP

#include "forge/matrix.hpp"

#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <span>


TEST_CASE("Matrix dimensions", "[matrix]") {
    forge::Matrix<int> mat(3, 2);
    REQUIRE(mat.cols() == 2);
    REQUIRE(mat.rows() == 3);
    REQUIRE(mat.size() == 3 * 2);
}

TEST_CASE("Matrix cell retrieval", "[matrix]") {
    constexpr std::size_t rows = 3;
    constexpr std::size_t cols = 4;
    std::vector data{
        1, 2, 3, -1,
        4, 5, 6, -1,
        7, 8, 9, 0
    };

    forge::Matrix mat(std::span<int>(data), rows, cols);

    // First row
    REQUIRE(mat.at(0, 0) == 1);
    REQUIRE(mat.at(0, 1) == 2);
    REQUIRE(mat.at(0, 2) == 3);
    REQUIRE(mat.at(0, 3) == -1);

    // Second row
    REQUIRE(mat.at(1, 0) == 4);
    REQUIRE(mat.at(1, 1) == 5);
    REQUIRE(mat.at(1, 2) == 6);
    REQUIRE(mat.at(1, 3) == -1);

    // Third row
    REQUIRE(mat.at(2, 0) == 7);
    REQUIRE(mat.at(2, 1) == 8);
    REQUIRE(mat.at(2, 2) == 9);
    REQUIRE(mat.at(2, 3) == 0);
}

TEST_CASE("Row retrieval", "[matrix]") {
    forge::Matrix mat({1, 2, 3, 4}, 2, 2);

    REQUIRE(std::ranges::equal(mat.row(0), std::ranges::subrange(mat.begin(), mat.begin() + 2)));
    REQUIRE(std::ranges::equal(mat.row(1), std::ranges::subrange(mat.begin() + 2, mat.end())));
}

TEST_CASE("Matrix row iteration", "[matrix]") {
    constexpr std::size_t rows = 3;
    constexpr std::size_t cols = 4;
    std::vector data{
        1, 2, 3, -1,
        4, 5, 6, -1,
        7, 8, 9, 0
    };

    forge::Matrix mat(std::span<int>(data), rows, cols);

    for (std::size_t i = 0; auto val : mat) {
        REQUIRE(data[i++] == val);
    }
}

TEST_CASE("Matrix col retrieval", "[matrix]") {
    constexpr std::size_t rows = 3;
    constexpr std::size_t cols = 4;
    std::vector data{
        1, 2, 3, -1,
        4, 5, 6, -1,
        7, 8, 9, 0
    };

    forge::Matrix mat(std::span<int>(data), rows, cols);

    REQUIRE(std::ranges::equal(mat.col(0), std::vector{1, 4, 7}));
    REQUIRE(std::ranges::equal(mat.col(1), std::vector{2, 5, 8}));
    REQUIRE(std::ranges::equal(mat.col(2), std::vector{3, 6, 9}));
    REQUIRE(std::ranges::equal(mat.col(3), std::vector{-1, -1, 0}));
}

TEST_CASE("Matrix comparison", "[matrix]") {
    forge::Matrix lhs{{1, 2, 3}, 1, 3};
    forge::Matrix rhs{{3, 4, 5}, 1, 3};

    REQUIRE(lhs == lhs);
    REQUIRE(!(lhs != lhs));

    REQUIRE(rhs == rhs);
    REQUIRE(!(rhs != rhs));

    REQUIRE(lhs != rhs);
    REQUIRE(!(lhs == rhs));
}

#endif // !FORGE_TEST_MATRIX_HPP