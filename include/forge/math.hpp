#ifndef FORGE_MATH_HPP
#define FORGE_MATH_HPP

#include "matrix.hpp"

#include <cassert>
#include <algorithm>

namespace forge::math {
    template<typename T>
    constexpr forge::Matrix<T> identity(int size) noexcept {
        assert(size > 0);

        forge::Matrix<T> out(size, size);
        std::ranges::fill(*out.diag_view(), 1);

        return out;
    }
}

#endif // !FORGE_MATH_HPP