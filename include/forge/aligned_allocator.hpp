#ifndef FORGE_ALIGNED_ALLOCATOR_HPP
#define FORGE_ALIGNED_ALLOCATOR_HPP

#include <algorithm>
#include <cassert>

#ifdef __AVX2__
constexpr std::size_t ALIGNMENT = 32;
#elif __SSE2__
constexpr std::size_t ALIGNMENT = 16;
#else
constexpr std::size_t ALIGNMENT = 0;
#endif

namespace forge {
    template<typename T>
    class AlignedAllocator {
    public:
        using pointer = T*;
        using const_pointer = T const*;
        using value_type = T;

    private:
        static constexpr auto alignment = static_cast<std::align_val_t>(std::max(alignof(T), ALIGNMENT));
    public:

        [[nodiscard("Discarding allocation result will induce in a memory leak")]]
        constexpr T* allocate(std::size_t count) {
            auto ptr = static_cast<T*>(::operator new(count * sizeof(T), alignment));
            assert(ptr != nullptr);

            return ptr;
        }

        constexpr void deallocate(T* p, std::size_t count) {
            ::operator delete(p, count * sizeof(T), alignment);
        }
    };
}

#endif // !FORGE_ALIGNED_ALLOCATOR_HPP
