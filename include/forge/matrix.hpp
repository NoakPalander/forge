#ifndef FORGE_MATRIX_HPP
#define FORGE_MATRIX_HPP

#include "row_iterator.hpp"
#include "col_iterator.hpp"

#include <vector>
#include <ranges>
#include <span>
#include <cassert>
#include <algorithm>
#include <optional>

#include "fmt/format.h"

namespace forge {
    template<typename T>
    class Matrix {
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = T const*;
        using reference = T&;
        using const_reference = T const&;

    private:
        int rows_;
        int cols_;
        std::vector<T> buffer_;

    public:
        constexpr Matrix(int rows, int cols, T const& value = T{})
            : rows_(rows), cols_(cols), buffer_(static_cast<std::size_t>(rows * cols), value) {}

        constexpr Matrix(std::initializer_list<T> data, int rows, int cols)
            : rows_(rows), cols_(cols)
        {
            assert(rows * cols == static_cast<int>(data.size()));
            std::ranges::copy(data, std::back_inserter(buffer_));
        }

        constexpr Matrix(std::vector<T> data, int rows, int cols)
            : rows_(rows), cols_(cols), buffer_(std::move(data))
        {
            assert(rows * cols == buffer_.size());
        }

        constexpr Matrix(std::span<T> span, int rows, int cols)
            : rows_(rows), cols_(cols)
        {
            assert(rows * cols == span.size());
            std::ranges::copy(span, std::back_inserter(buffer_));
        }

        [[nodiscard]] constexpr int rows() const noexcept {
            return rows_;
        }

        [[nodiscard]] constexpr int cols() const noexcept {
            return cols_;
        }

        [[nodiscard]] constexpr int size() const noexcept {
            return static_cast<int>(buffer_.size());
        }

        constexpr pointer data() noexcept {
            return buffer_.data();
        }

        constexpr const_pointer data() const noexcept {
            return buffer_.data();
        }

        constexpr auto rows_view() noexcept {
            return std::views::iota(0, static_cast<int>(rows_)) | std::views::transform([this](int index) {
                return row(index);
            });
        }

        constexpr auto rows_view() const noexcept {
            return std::views::iota(0, static_cast<int>(rows_)) | std::views::transform([this](int index) {
                return row(index);
            });
        }

        constexpr auto cols_view() noexcept {
            return std::views::iota(0, cols_) | std::views::transform([this](int index){
                return col(index);
            });
        }

        constexpr auto cols_view() const noexcept {
            return std::views::iota(0, cols_) | std::views::transform([this](int index){
                return col(index);
            });
        }

        constexpr auto flat_view() noexcept {
            return std::views::counted(buffer_.begin(), buffer_.size());
        }

        constexpr auto flat_view() const noexcept {
            return std::views::counted(buffer_.begin(), buffer_.size());
        }

        constexpr auto diag_view() noexcept {
            auto view = std::views::iota(0, rows_) | std::views::transform([this](int index) -> decltype(auto) {
                return at(index, index);
            });

            if (rows_ != cols_)
                return std::optional<decltype(view)>(std::nullopt);

            return std::make_optional(view);
        }

        constexpr auto diag_view() const noexcept {
            auto view = std::views::iota(0, rows_) | std::views::transform([this](int index) -> decltype(auto) {
                return at(index, index);
            });

            if (cols_ != rows_)
                return std::optional<decltype(view)>(std::nullopt);

            return std::make_optional(view);
        }

        constexpr reference at(int row, int col) noexcept {

            assert(row >= 0 && row < rows_);
            assert(col >= 0 && col < cols_);

            return buffer_[static_cast<std::size_t>(row * cols_ + col)];
        }

        constexpr const_reference at(int row, int col) const noexcept {
            assert(row >= 0 && row < rows_);
            assert(col >= 0 && col < cols_);

            return buffer_[static_cast<std::size_t>(row * cols_ + col)];
        }

        constexpr auto row(int index) noexcept {
            assert(index >= 0 && index < rows_);

            auto it = RowIterator(buffer_.data()) + index * static_cast<int>(cols_);
            return std::views::counted(it, static_cast<std::ptrdiff_t>(cols_));
        }

        constexpr auto row(int index) const noexcept {
            assert(index >= 0 && index < rows_);

            auto it = RowIterator(buffer_.data()) + static_cast<int>(index * cols_);
            return std::views::counted(it, static_cast<std::ptrdiff_t>(cols_));
        }

        constexpr auto col(int index) noexcept {
            assert(index >= 0 && index < cols_);

            auto first = ColIterator(buffer_.data() + index, static_cast<std::size_t>(cols_));
            return std::views::counted(first, static_cast<std::ptrdiff_t>(rows_));
        }

        constexpr auto col(int index) const noexcept {
            assert(index >= 0 && index < cols_);

            auto first = ColIterator(buffer_.data() + index, static_cast<std::size_t>(cols_));
            return std::views::counted(first, static_cast<std::ptrdiff_t>(rows_));
        }

        constexpr bool operator==(Matrix const& other) const noexcept {
            return rows_ == other.rows_ && cols_ == other.cols_ && buffer_ == other.buffer_;
        }

        constexpr bool operator!=(Matrix const& other) const noexcept {
            return !operator==(other);
        }
    };
}

#endif // !FORGE_MATRIX_HPP