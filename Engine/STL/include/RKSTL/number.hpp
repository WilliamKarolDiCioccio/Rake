#pragma once

#include <limits>
#include <cstdint>
#include <numeric>

namespace Rake::libraries {

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <typename T>
concept SignedArithmetic = Arithmetic<T> && std::is_signed_v<T>;

template <typename T>
concept UnsignedArithmetic = Arithmetic<T> && !std::is_signed_v<T>;

template <typename T>
concept IntegralArithmetic = Arithmetic<T> && std::is_integral_v<T>;

template <typename T>
concept FloatingArithmetic = Arithmetic<T> && std::is_floating_point_v<T>;

/**
     * @brief Checks the sign of an integer value.
     *
     * Given an integral value, this function determines whether it's positive or negative.
     *
     * @tparam T The type of the value.
     * @param _value The input value.
     * @return true if the value is negative, false if it's non-negative.
     *
     * @note Branchless variant
     */
template <typename T>
[[nodiscard("")]] constexpr bool BitSign(const T &_value) noexcept
    requires IntegralArithmetic<T>
{
    const size_t size = sizeof(T);
    return (0 ^ ((size_t)_value >> (size * CHAR_BIT - 1)));
}

/**
     * @brief Computes the absolute value of an integral number.
     *
     * This function calculates the absolute value of an integral number, effectively removing its sign.
     *
     * @tparam T The type of the value.
     * @param _value The input value.
     * @return The absolute value of the input.
     *
     * @note Branchless variant
     */
template <typename T>
[[nodiscard("")]] constexpr auto BitAbsolute(const T &_value) noexcept
    requires IntegralArithmetic<T>
{
    const T mask = _value >> (sizeof(T) * CHAR_BIT - 1);
    return (_value + mask) ^ mask;
}

/**
     * @brief Finds the minimum of two values.
     *
     * Given two comparable values, this function returns the smaller of the two.
     *
     * @tparam T The type of the values.
     * @param _left The first value.
     * @param _right The second value.
     * @return The minimum of the two input values.
     *
     * @note Branchless variant
     */
template <typename T>
[[nodiscard("")]] constexpr auto BitMinimum(const T &_left, const T &_right) noexcept
    requires Arithmetic<T>
{
    return _right ^ ((_left ^ _right) & -(_left < _right));
}

/**
     * @brief Finds the maximum of two values.
     *
     * Given two comparable values '_left' and '_right', this function returns the larger of the two.
     *
     * @tparam T The type of the values.
     * @param _left The first value.
     * @param _right The second value.
     * @return The maximum of the two input values.
     *
     * @note Branchless variant
     */
template <typename T>
[[nodiscard("")]] constexpr auto BitMaximum(const T &_left, const T &_right) noexcept
    requires Arithmetic<T>
{
    return _left ^ ((_left ^ _right) & -(_left < _right));
}

/**
     * @brief Checks if an integer value is odd.
     *
     * Given an integral value, this function determines whether it's an odd number.
     *
     * @tparam T The type of the value.
     * @param _value The input value.
     * @return true if the value is odd, false if it's even.
     *
     * @note Branchless variant
     */
template <typename T>
[[nodiscard("")]] constexpr bool BitOdd(const T &_value) noexcept
    requires Arithmetic<T>
{
    return ((_value & 1) != 0);
}

/**
     * @brief Checks if an integer value is even.
     *
     * Given an integral value, this function determines whether it's an even number.
     *
     * @tparam T The type of the value.
     * @param _value The input value.
     * @return true if the value is even, false if it's odd.
     *
     * @note Branchless variant
     */
template <typename T>
[[nodiscard("")]] constexpr bool BitEven(const T &_value) noexcept
    requires Arithmetic<T>
{
    return ((_value & 1) == 0);
}

/**
     * @brief Checks if an integer value is a power of two.
     *
     * Given an integral value, this function determines whether it's a power of two.
     *
     * @tparam T The type of the value.
     * @param _value The input value.
     * @return true if the value is a power of two, false otherwise.
     *
     * @note Branchless variant
     */
template <typename T>
[[nodiscard("")]] constexpr bool BitTwoPow(const T &_value) noexcept
    requires Arithmetic<T>
{
    return _value && !(_value & (_value - 1));
}

/**
     * @brief Merges bits from two values using a mask.
     *
     * This function takes two values, `_left` and `_right`, and a mask `_mask`, and
     * merges them by flipping the bits of `_left` that are set in `_mask` to match the
     * corresponding bits in `_right`, while leaving other bits unchanged.
     *
     * @tparam T The type of values.
     * @param _left The first value.
     * @param _right The second value.
     * @param _mask The mask indicating which bits to merge.
     * @return The result of merging using the specified mask.
     *
     * @note Branchless variant
     */
template <typename T>
[[nodiscard("")]] constexpr T BitMerge(const T &_left, const T &_right, const T &_mask) noexcept
    requires Arithmetic<T>
{
    return _left ^ ((_left ^ _right) & _mask);
}

/**
     * @brief Clamps an integral value inclusively within a range.
     *
     * This function clamps an integral value inclusively within a specified range defined by '_minValue' and '_maxValue'.
     *
     * @tparam T The type of the values.
     * @param _value The input value.
     * @param _minValue The minimum value of the range.
     * @param _maxValue The maximum value of the range.
     * @return The clamped value within the specified range.
     *
     * @note Branchless variant
     */
template <typename T>
[[nodiscard("")]] constexpr auto InclusiveBitClamp(const T &_value, const T &_minValue, const T &_maxValue) noexcept
    requires IntegralArithmetic<T>
{
    const T maskMin = (_value - _minValue) >> (sizeof(T) * CHAR_BIT - 1);
    const T maskMax = (_maxValue - _value) >> (sizeof(T) * CHAR_BIT - 1);

    T clampedValue = (_value & ~maskMin) | (_minValue & maskMin);
    clampedValue = (clampedValue & ~maskMax) | (_maxValue & maskMax);

    return clampedValue;
}

/**
     * @brief Clamps an integral value exclusively within a range.
     *
     * This function clamps an integral value exclusively within a specified range defined by '_minValue' and '_maxValue'.
     *
     * @tparam T The type of the values.
     * @param _value The input value.
     * @param _minValue The minimum value of the range.
     * @param _maxValue The maximum value of the range.
     * @return The clamped value within the specified range.
     *
     * @note Branchless variant
     */
template <typename T>
[[nodiscard("")]] constexpr auto ExclusiveBitClamp(const T &_value, const T &_minValue, const T &_maxValue) noexcept
    requires IntegralArithmetic<T>
{
    const T maskMin = (_value - _minValue) >> (sizeof(T) * CHAR_BIT - 1);
    const T maskMax = (_maxValue - _value) >> (sizeof(T) * CHAR_BIT - 1);

    T clampedValue = (_value & ~maskMin) | (_minValue & maskMin);
    clampedValue = (clampedValue & ~maskMax) | (_maxValue & maskMax);

    return clampedValue + maskMax - maskMin;
}

/**
     * @brief Reverses the digits of an integer number.
     *
     * Given an integer number, this function reverses the order of its digits.
     *
     * @tparam T The type of the value.
     * @param _value The input value to reverse.
     * @return The reversed value.
     */
template <typename T>
[[nodiscard("")]] inline auto ReverseNumber(T _value) noexcept
    requires Arithmetic<T>
{
    auto numStr = std::to_string(_value);

    std::reverse(numStr.begin(), numStr.end());

    if constexpr (FloatingArithmetic<T>) {
        return std::stod(numStr);
    } else {
        return std::stoi(numStr);
    }
}

}  // namespace Rake::libraries

#define RK_SIGNED(value)                    Rake::libraries::BitSign(value)
#define RK_ABSOLUTE(value)                  Rake::libraries::BitAbsolute(value)
#define RK_MINIMUM(left, right)             Rake::libraries::BitMinimum(left, right)
#define RK_MAXIMUM(left, right)             Rake::libraries::BitMaximum(left, right)
#define RK_IS_ODD(value)                    Rake::libraries::BitOdd(value)
#define RK_IS_EVEN(value)                   Rake::libraries::BitEven(value)
#define RK_IS_TWO_POW(value)                Rake::libraries::BitTwoPow(value)
#define RK_INCLUSIVE_CLAMP(value, min, max) Rake::libraries::InclusiveBitClamp(value, min, max)
#define RK_EXCLUSIVE_CLAMP(value, min, max) Rake::libraries::ExclusiveBitClamp(value, min, max)
