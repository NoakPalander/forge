#ifndef FORGE_ROW_ITERATOR_HPP
#define FORGE_ROW_ITERATOR_HPP

#include <iterator>
#include <ranges>

namespace forge {
    template<typename T>
    class RowIterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using const_reference = T const&;

    private:
        pointer ptr_ = nullptr;

    public:
        constexpr RowIterator() = default;

        constexpr explicit RowIterator(pointer ptr) : ptr_(ptr) {}

        constexpr reference operator*() const noexcept {
            return *ptr_;
        }

        constexpr pointer operator->() const noexcept {
            return ptr_;
        }

        friend constexpr RowIterator operator+(RowIterator iter, int count) noexcept {
            return RowIterator(iter.ptr_ + count);
        }

        friend constexpr RowIterator operator+(int count, RowIterator iter) noexcept {
            return RowIterator(iter.ptr_ + count);
        }

        constexpr RowIterator& operator++() noexcept {
            ++ptr_;
            return *this;
        }

        constexpr RowIterator operator++(int) & noexcept {
            auto copy = *this;
            ++(*this);
            return copy;
        }

        constexpr reference operator+=(int count) noexcept {
            return ptr_ += count;
        }

        constexpr RowIterator operator--() noexcept {
            --ptr_;
            return *this;
        }

        constexpr RowIterator operator--(int) & noexcept {
            auto copy = *this;
            --(*this);
            return copy;
        }

        friend constexpr RowIterator operator-(RowIterator iter, int count) noexcept {
            return RowIterator(iter.ptr_ - count);
        }

        friend constexpr RowIterator operator-(int count, RowIterator iter) noexcept {
            return RowIterator(iter.ptr_ - count);
        }

        constexpr difference_type operator-(RowIterator const& other) const noexcept {
            return ptr_ - other.ptr_;
        }

        constexpr reference operator-=(int count) noexcept {
            return ptr_ -= count;
        }

        constexpr reference operator[](int index) noexcept {
            return ptr_[index];
        }

        constexpr const_reference operator[](int index) const noexcept {
            return ptr_[index];
        }

        constexpr auto operator<=>(RowIterator const&) const noexcept = default;
    };
}

#endif // !FORGE_ROW_ITERATOR_HPP
