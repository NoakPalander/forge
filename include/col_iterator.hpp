#ifndef FORGE_COL_ITERATOR_HPP
#define FORGE_COL_ITERATOR_HPP

#include <cassert>
#include <iterator>

namespace forge {
    template<typename T>
    class ColIterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using const_reference = T const&;
        using size_type = std::size_t;

    private:
        pointer ptr_ = nullptr;
        size_type cols_ = 0;

    public:
        constexpr ColIterator() = default;

        constexpr ColIterator(pointer ptr, size_type cols)
            : ptr_(ptr), cols_(cols) {}


        constexpr reference operator*() const noexcept {
            return *ptr_;
        }

        constexpr pointer operator->() const noexcept {
            return ptr_;
        }

        friend constexpr ColIterator operator+(ColIterator iter, int count) noexcept {
            return ColIterator(iter.ptr_ + static_cast<int>(iter.cols_) * count, iter.cols_);
        }

        friend constexpr ColIterator operator+(int count, ColIterator iter) noexcept {
            return ColIterator(iter.ptr_ + static_cast<int>(iter.cols_) * count, iter.cols_);
        }

        constexpr ColIterator& operator++() noexcept {
            ptr_ += cols_;
            return *this;
        }

        constexpr ColIterator operator++(int) & noexcept {
            auto copy = *this;
            ++(*this);
            return copy;
        }

        constexpr ColIterator operator+=(int count) noexcept {
            ptr_ =+ static_cast<int>(cols_) * count;
            return *this;
        }

        friend constexpr ColIterator operator-(ColIterator iter, int count) noexcept {
            return ColIterator(iter.ptr_ - static_cast<int>(iter.cols_) * count, iter.cols_);
        }

        friend constexpr ColIterator operator-(int count, ColIterator iter) noexcept {
            return ColIterator(iter.ptr_ - static_cast<int>(iter.cols_) * count, iter.cols_);
        }

        constexpr ColIterator& operator--() noexcept {
            ptr_ -= cols_;
            return *this;
        }

        constexpr ColIterator operator--(int) & noexcept {
            auto copy = *this;
            --(*this);
            return copy;
        }

        constexpr difference_type operator-(ColIterator other) const noexcept {
            assert(cols_ > 0);
            return (ptr_ - other.ptr_) / static_cast<difference_type>(cols_);
        }

        constexpr ColIterator operator-=(int count) noexcept {
            ptr_ =+ static_cast<int>(cols_) * count;
            return *this;
        }

        constexpr reference operator[](int index) noexcept {
            return *(ptr_ + static_cast<int>(cols_) * index);
        }

        constexpr const_reference operator[](int index) const noexcept {
            return *(ptr_ + static_cast<int>(cols_) * index);
        }

        constexpr auto operator<=>(ColIterator const&) const noexcept = default;
    };
}

#endif // !FORGE_COL_ITERATOR_HPP
