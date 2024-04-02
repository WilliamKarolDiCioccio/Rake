#pragma once

#include <memory>

namespace Rake::libraries {

template <typename T>
concept Pointer = std::is_pointer_v<T>;

template <typename T>
concept NonPointer = !std::is_pointer_v<T>;

/**
     * @brief Swaps the values of two variables without using additional memory.
     *
     * This function swaps the values of two variables of the same type `T` without
     * using additional memory. It does so by performing three bitwise XOR operations.
     *
     * @tparam T The type of the variables to be swapped.
     * @param[in,out] _left Reference to the first variable.
     * @param[in,out] _right Reference to the second variable.
     *
     * @note This implementation is not faster than std::swap, but it uses less memory.
     *
     * @see std::swap
     */
template <typename T, typename U>
constexpr void Swap(T &_left, T &_right) noexcept {
    _left ^= _right;
    _right ^= _left;
    _left ^= _right;
}

}  // namespace Rake::libraries
