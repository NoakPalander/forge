#ifndef FORGE_MATRIX_HPP
#define FORGE_MATRIX_HPP

#include "row_iterator.hpp"
#include "col_iterator.hpp"

#include <vector>
#include <ranges>
#include <span>
#include <cassert>
#include <algorithm>
#include <fmt/format.h>

namespace forge {
    template<typename T>
    class Matrix {
    public:
        using value_type = T;
        using iterator_category = RowIterator<value_type>::iterator_category;
        using difference_type = RowIterator<value_type>::difference_type;
        using pointer = T*;
        using const_pointer = T const*;
        using reference = T&;
        using const_reference = T const&;
        using size_type = std::size_t;

    private:
        size_type rows_;
        size_type cols_;
        std::vector<T> buffer_;

    public:
        constexpr Matrix(size_type rows, size_type cols, T const& value = T{})
            : rows_(rows), cols_(cols), buffer_(rows * cols, value) {}

        constexpr Matrix(std::initializer_list<T> data, size_type rows, size_type cols)
            : rows_(rows), cols_(cols)
        {
            assert(rows * cols == data.size());
            std::ranges::copy(data, std::back_inserter(buffer_));
        }

        constexpr Matrix(std::vector<T> data, size_type rows, size_type cols)
            : rows_(rows), cols_(cols), buffer_(std::move(data))
        {
            assert(rows * cols == buffer_.size());
        }

        constexpr Matrix(std::span<T> span, size_type rows, size_type cols)
            : rows_(rows), cols_(cols)
        {
            assert(rows * cols == span.size());
            std::ranges::copy(span, std::back_inserter(buffer_));
        }

        constexpr Matrix(Matrix const&) = default;
        constexpr Matrix(Matrix&&) noexcept = default;

        [[nodiscard]] constexpr size_type rows() const noexcept {
            return rows_;
        }

        [[nodiscard]] constexpr size_type cols() const noexcept {
            return cols_;
        }

        [[nodiscard]] constexpr size_type size() const noexcept {
            return buffer_.size();
        }

        constexpr pointer data() noexcept {
            return buffer_.data();
        }

        constexpr const_pointer data() const noexcept {
            return buffer_.data();
        }

        constexpr RowIterator<T> begin() noexcept {
            return RowIterator(buffer_.data());
        }

        constexpr RowIterator<T const> begin() const noexcept {
            return RowIterator(buffer_.data());
        }

        constexpr RowIterator<T> end() noexcept {
            return RowIterator(buffer_.data() + buffer_.size());
        }

        constexpr RowIterator<value_type const> end() const noexcept {
            return RowIterator(buffer_.data() + buffer_.size());
        }

        constexpr reference at(int row, int col) noexcept {
            assert(row >= 0 && static_cast<size_type>(row) < rows_);
            assert(col >= 0 && static_cast<size_type>(col) < cols_);

            return buffer_[static_cast<size_type>(row) * cols_ + static_cast<size_type>(col)];
        }

        constexpr const_reference at(int row, int col) const noexcept {
            assert(row >= 0 && static_cast<size_type>(row) < rows_);
            assert(col >= 0 && static_cast<size_type>(col) < cols_);

            return buffer_[static_cast<size_type>(row) * cols_ + static_cast<size_type>(col)];
        }

        constexpr auto row(size_type index) noexcept {
            assert(index < rows_);

            RowIterator<value_type> it = begin() + static_cast<int>(index * cols_);
            return std::views::counted(it, static_cast<difference_type>(cols_));
        }

        constexpr auto row(size_type index) const noexcept {
            assert(index < rows_);

            RowIterator<value_type> it = begin() + static_cast<int>(index * cols_);
            return std::views::counted(it, static_cast<difference_type>(cols_));
        }

        constexpr auto col(size_type index) noexcept {
            assert(index < cols_);

            auto first = std::to_address(begin() + static_cast<int>(index));
            return std::views::counted(ColIterator(first, cols_), static_cast<difference_type>(rows_));
        }

        constexpr auto col(size_type index) const noexcept {
            assert(index < cols_);

            auto first = std::to_address(begin() + static_cast<int>(index));
            return std::views::counted(ColIterator(first, cols_), static_cast<difference_type>(rows_));
        }
    };
}

#endif // !FORGE_MATRIX_HPP