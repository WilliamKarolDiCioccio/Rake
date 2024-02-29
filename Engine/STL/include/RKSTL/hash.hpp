#pragma once

#include "string.hpp"

constexpr auto fnvOffset32 = 0x811c9dc5;
constexpr auto fnvPrime32 = 0x01000193;
constexpr auto fnvOffset64 = 0xcbf29ce484222325;
constexpr auto fnvPrime64 = 0x100000001b3;

namespace Rake::libraries {
/**
     * @see [How do I combine hash values in C++0x](https://stackoverflow.com/a/57595105/17345580)
     * @see [hash_combine() Again](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0814r0.pdf)
     */
template <typename T, typename... R>
void HashCombine(std::size_t &_seed, const T &_value, const R &..._rest) {
    _seed ^= std::hash<T>{}(_value) + 0x9e3779b9 + (_seed << 6) + (_seed >> 2);
    (HashCombine(_seed, _rest), ...);
};

/**
     * @brief Computes the SHA-256 hash of a given string.
     *
     * This function computes and returns the SHA-256 hash of the input string `_string`.
     *
     * @param _string The string for which to compute the SHA-256 hash.
     * @return The SHA-256 hash as a hexadecimal string.
     */
const std::string sha256(const std::string &_string) noexcept;

/**
     * @brief Computes the SHA-512 hash of a given string.
     *
     * This function computes and returns the SHA-512 hash of the input string `_string`.
     *
     * @param _string The string for which to compute the SHA-512 hash.
     * @return The SHA-512 hash as a hexadecimal string.
     */
const std::string sha512(const std::string &_string) noexcept {}

/**
     * @brief Computes the MurmurHash3 hash of a given data array with a seed value.
     *
     * This function computes and returns the MurmurHash3 hash of the input data array `_data`
     * of length `_length` with the specified `_seed`.
     *
     * @param _data The data array to hash.
     * @param _length The length of the data array.
     * @param _seed The seed value for the MurmurHash3 algorithm.
     * @return The MurmurHash3 hash value.
     */
const uint32_t MurmurHash3(const unsigned char *_data, uint64_t _lenght, uint64_t _seed) noexcept {
    const uint32_t m = 0x5bd1e995;
    const int r = 24;

    uint32_t h = _seed ^ _lenght;

    while (_lenght >= 4) {
        uint32_t k = *(uint32_t *)_data;
        k *= m;
        k ^= k >> r;
        k *= m;
        h *= m;
        h ^= k;
        _data += 4;
        _lenght -= 4;
    }

    switch (_lenght) {
        case 3:
            h ^= _data[2] << 16;
            [[fallthrough]];
        case 2:
            h ^= _data[1] << 8;
            [[fallthrough]];
        case 1:
            h ^= _data[0];
            h *= m;
    }

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}

// clang-format off

/**
 * @brief Computes the FNV-1 hash of a given string with an optional initial hash value.
 *
 * This function computes and returns the FNV-1 hash of the input string `_string`.
 * An optional initial hash value `_hash` can be provided for custom hash chaining.
 *
 * @tparam T The type of the hash value.
 * @tparam StringType The type of the input string.
 * @param _string The string for which to compute the FNV-1 hash.
 * @param _hash The initial hash value (default is FNV-1 offset value).
 * @return The FNV-1 hash value of the input string.
 */
template <typename T, typename StringType>
inline const T FNV1Hash(const StringType& _string, T _hash = (sizeof(T)==4) ? fnvOffset32 : fnvOffset64) noexcept requires StandardString<StringType>
{
    constexpr T prime = (sizeof(T) == 4) ? static_cast<T>(fnvPrime32) : static_cast<T>(fnvPrime64);


   for(const auto& c: _string) {
        _hash ^= static_cast<T>(c);
        _hash *= prime;
    }

    return _hash;
}

/**
 * @brief Computes the FNV-1a hash of a given string with an optional initial hash value.
 *
 * This function computes and returns the FNV-1a hash of the input string `_string`.
 * An optional initial hash value `_hash` can be provided for custom hash chaining.
 *
 * @tparam T The type of the hash value.
 * @tparam StringType The type of the input string.
 * @param _string The string for which to compute the FNV-1a hash.
 * @param _hash The initial hash value (default is FNV-1 offset value).
 * @return The FNV-1a hash value of the input string.
 */
template <typename T, typename StringType>
inline consteval T FNV1aHash(StringType _string, T _hash = (sizeof(T)==4) ? fnvOffset32 : fnvOffset64) noexcept requires CString<StringType>
{
    return (*_string == '\0') ? _hash : FNV1aHash<T>(_string + 1, (_hash ^ static_cast<T>(*_string)) * ((sizeof(T)==4) ? fnvPrime32 : fnvPrime64));
}

// clang-format on

}  // namespace Rake::libraries
