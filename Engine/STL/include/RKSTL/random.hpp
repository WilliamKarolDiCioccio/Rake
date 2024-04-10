#pragma once

#include <random>
#include <string>

#include "defines.hpp"

#include "number.hpp"
#include "string.hpp"

namespace Rake::libraries {

/**
 * @brief Generates a random number within a given range using the Mersenne Twister 19937 algorithm.
 *
 * This function generates a random number of type `T` within the specified range
 * `[_min, _max]` using the Mersenne Twister 19937 pseudo-random number generator.
 *
 * @tparam T The type of the random number to generate, which must be an arithmetic type.
 * @param _min The minimum value of the range (inclusive).
 * @param _max The maximum value of the range (inclusive).
 * @return A random number within the specified range `[min, max]`.
 *
 * @note This function requires a valid random device for seeding, so ensure that
 *       a suitable device is available before calling this function.
 */
template <typename T>
inline T mt19937(T _min, T _max) noexcept
    requires Arithmetic<T>
{
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<T> distribution(_min, _max);

    return distribution(generator);
}

/**
 * @brief Generates a pseudo-random number using the XOR-Shift algorithm.
 *
 * This function generates a pseudo-random number of type `T` using the XOR-Shift algorithm.
 * It takes a seed value and repeatedly applies XOR and bit-shifting operations to produce
 * a sequence of random-like values.
 *
 * @tparam T The type of the seed and generated random number, which must be an arithmetic type.
 * @param _seed The initial seed value for the XOR-Shift algorithm.
 * @return A pseudo-random number generated using the XOR-Shift algorithm.
 */
template <typename T>
inline T XORShift(T _seed) noexcept
    requires Arithmetic<T>
{
    _seed ^= _seed << 13;
    _seed ^= _seed >> 17;
    _seed ^= _seed << 5;

    return _seed;
}

/**
 * @brief Generates a random string of a specified length using a character set.
 *
 * This function generates a random string of the specified `_length` using characters
 * from the given `_charset`. The characters are randomly selected from `_charset` to
 * form the resulting string.
 *
 * @tparam StringType The type of the string to generate, which must be a standard string type.
 * @param _length The length of the random string to generate.
 * @param _charset The character set from which to randomly select characters for the string.
 * @return A random string of length `_length` composed of characters from `_charset`.
 */
template <typename StringType>
StringType RandomString(uint32_t _length, const StringType &_charset) noexcept
    requires StandardString<StringType>
{
    StringType result;
    result.reserve(_length);

    for (int i = 0; i < _length; i++) result += _charset[rand() % _charset.length()];

    return result;
}

}  // namespace Rake::libraries
