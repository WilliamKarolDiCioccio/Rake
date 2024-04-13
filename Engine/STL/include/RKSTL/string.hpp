#pragma once

#include <string>
#include <string_view>
#include <format>
#include <codecvt>

#include "defines.hpp"

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

// Note: We are using the std::codecvt_utf8_utf16 class to convert between byte strings and wide strings even though it is deprecated in C++17.

namespace Rake::libraries {

template <typename T>
concept CString = std::same_as<T, char *> || std::same_as<T, const char *> || std::same_as<T, wchar_t *> ||
                  std::same_as<T, const wchar_t *>;

template <typename T>
concept StandardString = std::same_as<T, std::string> || std::same_as<T, std::wstring>;

/**
 * @brief Returns the size of a byte string.
 * @param _string The byte string to get the size of.
 * @return The size of the byte string.
 */
inline consteval size_t ByteStringSize(char *_string) { return std::string::traits_type::length(_string); }

/**
 * @brief Returns the size of a wide string.
 * @param _string The wide string to get the size of.
 * @return The size of the wide string.
 */
inline consteval size_t WideStringSize(wchar_t *_string) { return std::wstring::traits_type::length(_string); }

/**
 * @brief Converts a byte string to a wide string.
 * @param _string The byte string to convert.
 * @return The converted wide string.
 */
inline std::wstring ByteToWideString(const std::string &_string) noexcept {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    return converter.from_bytes(_string);
}

/**
 * @brief Converts a wide string to a byte string.
 * @param _string The wide string to convert.
 * @return The converted byte string.
 */
inline std::string WideToByteString(const std::wstring &_string) noexcept {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    return converter.to_bytes(_string);
}

/**
 * @brief Converts a byte string to a wide string.
 * @param _string The byte string to convert.
 * @return The converted wide string.
 */
inline std::string FormatByteString(const std::string_view &format, std::format_args &&args) noexcept {
    return std::vformat(format, args);
}

/**
 * @brief Converts a wide string to a byte string.
 * @param _string The wide string to convert.
 * @return The converted byte string.
 */
inline std::wstring FormatWideString(const std::wstring_view &format, std::wformat_args &&args) noexcept {
    return std::vformat(format, args);
}

}  // namespace Rake::libraries
