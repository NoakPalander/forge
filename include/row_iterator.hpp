#ifndef FORGE_ROW_ITERATOR_HPP
#define FORGE_ROW_ITERATOR_HPP

#include <iterator>

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

        constexpr RowIterator operator+(difference_type count) const noexcept {
            return RowIterator(ptr_ + count);
        }

        friend constexpr RowIterator operator+(difference_type count, RowIterator const& iter) noexcept {
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

        constexpr RowIterator& operator+=(difference_type count) noexcept {
            ptr_ += count;
            return *this;
        }

        constexpr RowIterator operator-(difference_type count) const noexcept {
            return RowIterator(ptr_ - count);
        }

        friend constexpr RowIterator operator-(difference_type count, RowIterator const& iter) noexcept {
            return RowIterator(iter.ptr_ - count);
        }

        constexpr RowIterator& operator--() noexcept {
            --ptr_;
            return *this;
        }

        constexpr RowIterator operator--(int) & noexcept {
            auto copy = *this;
            --(*this);
            return copy;
        }

        constexpr difference_type operator-(RowIterator const& other) const noexcept {
            return ptr_ - other.ptr_;
        }

        constexpr RowIterator& operator-=(difference_type count) noexcept {
            ptr_ -= count;
            return *this;
        }

        constexpr reference operator[](difference_type index) const noexcept {
            return ptr_[index];
        }

        constexpr auto operator<=>(RowIterator const&) const noexcept = default;
    };
}

#endif // !FORGE_ROW_ITERATOR_HPP
