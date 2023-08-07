#ifndef FORGE_SIMD_MATH_HPP
#define FORGE_SIMD_MATH_HPP

#ifndef FORGE_ENABLE_SIMD
#error "SIMD support wasn't enabled!"
#endif

#ifndef __AVX2__
#error "AVX2 is not supported!"
#endif

#include "forge/cpp_math.hpp"
#include "forge/aligned_allocator.hpp"

#include "fmt/format.h"
#include <immintrin.h>

#include <memory>
#include <new>

namespace forge::simd {
    namespace detail {
        inline float dot_product(std::span<float const> lhs, std::span<float const> rhs) noexcept {
            if (lhs.empty() || rhs.empty()) [[unlikely]]
                return 0;

            assert(lhs.size() == rhs.size());

            __m256 ymm_sum = _mm256_setzero_ps();
            std::size_t const simd_size = 8;
            std::size_t const size = lhs.size();
            std::size_t index = 0;

            // Calculate simd portion
            for (; index < size - simd_size + 1; index += simd_size) {
                __m256 ymm_lhs = _mm256_load_ps(lhs.data() + index);
                __m256 ymm_rhs = _mm256_load_ps(rhs.data() + index);
                ymm_sum = _mm256_fmadd_ps(ymm_lhs, ymm_rhs, ymm_sum);
            }

            __m256 temp_lhs = _mm256_hadd_ps(ymm_sum, ymm_sum);
            __m256 temp_rhs = _mm256_hadd_ps(temp_lhs, temp_lhs);

            float sum = 0;
            _mm_store_ss(&sum, _mm256_castps256_ps128(temp_rhs));

            return sum + std::inner_product(
                lhs.begin() + static_cast<std::ptrdiff_t>(index),
                lhs.end(),
                rhs.begin() + static_cast<std::ptrdiff_t>(index),
                0.f
            );
        }

        constexpr double dot_product(std::span<double const> lhs, std::span<double const> rhs) noexcept {
            if (lhs.empty() || rhs.empty()) [[unlikely]]
                return 0;

            assert(lhs.size() == rhs.size());

            __m256d ymm_sum = _mm256_setzero_ps();
            std::size_t const simd_size = 8;
            std::size_t const size = lhs.size();
            std::size_t index = 0;

            // Calculate simd portion
            for (; index < size - simd_size + 1; index += simd_size) {
                __m256d ymm_lhs = _mm256_load_pd(lhs.data() + index);
                __m256d ymm_rhs = _mm256_load_pd(rhs.data() + index);
                ymm_sum = _mm256_fmadd_ps(ymm_lhs, ymm_rhs, ymm_sum);
            }

            __m256 temp_lhs = _mm256_hadd_pd(ymm_sum, ymm_sum);
            __m256 temp_rhs = _mm256_hadd_pd(temp_lhs, temp_lhs);

            double sum = 0;
            // TODO: Is this instruction right?
            _mm_store_sd(&sum, _mm256_castps256_ps128(temp_rhs));

            return sum + std::inner_product(
                lhs.begin() + static_cast<std::ptrdiff_t>(index),
                lhs.end(),
                rhs.begin() + static_cast<std::ptrdiff_t>(index),
                0.0
            );
        }
    }

    template<typename T>
    constexpr T dot_product(std::span<T const> lhs, std::span<T const> rhs) noexcept {
        if constexpr (std::same_as<T, float> || std::same_as<T, double>) {
            return detail::dot_product(lhs, rhs);
        }
        else {
            return forge::cpp::dot_product(lhs, rhs);
        }
    }
}

#endif // !FORGE_SIMD_MATH_HPP