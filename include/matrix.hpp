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
        // TODO: These
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using const_pointer = T const*;
        using reference = T&;
        using iterator_category = RowIterator<value_type>::iterator_category;
        using size_type = std::size_t;

    private:
        size_type rows_;
        size_type cols_;
        std::vector<T> buffer_;

    public:
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

        constexpr auto row(size_type index) noexcept {
            assert(index < rows_);

            RowIterator<value_type> first = begin() + static_cast<int>(index * cols_);
            RowIterator<value_type> last = first + static_cast<int>(cols_);

            return std::ranges::subrange(first, last, cols_);
        }

        constexpr std::ranges::subrange<RowIterator<value_type>> row(size_type index) const noexcept {
            assert(index < rows_);

            RowIterator<value_type> first = begin() + static_cast<int>(index * cols_);
            RowIterator<value_type> last = first + static_cast<int>(cols_);

            return std::ranges::subrange(first, last, cols_);
        }

        /*constexpr std::ranges::subrange<ColIterator<value_type>> col(size_type index) noexcept {
            assert(index < cols_);

            auto first = begin() + index;
            auto last = first + cols_ * (rows_ - 1);

            return std::ranges::subrange(first, last);
        }*/
    };
}

#endif // !FORGE_MATRIX_HPP