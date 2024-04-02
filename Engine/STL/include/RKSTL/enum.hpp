#pragma once

#include <type_traits>

namespace Rake::libraries {

/**
 * @brief A template class for handling bit flags using C++ enum classes.
 *
 * The EnumFlags class allows you to work with C++ enum classes as if they were bit flags,
 * enabling bitwise operations such as AND, OR, XOR, and assignment on enum values.
 *
 * @tparam _Enum The enum class type to be used as bit flags.
 */
template <typename _Enum>
class EnumFlags final {
    static_assert(std::is_enum_v<_Enum>, "Type is not an enum!");

    using UnderlyingType = std::underlying_type_t<_Enum>;

    static_assert(std::is_integral_v<UnderlyingType>, "Type is not integral!");
    static_assert(std::is_unsigned_v<UnderlyingType>, "Type is not unsigned!");

   private:
    UnderlyingType m_flags; /**< The underlying integer value representing the combined bit flags. */

   public:
    /**
    * @brief Default constructor initializes the flags to zero.
    */
    EnumFlags() : m_flags(0){};
    EnumFlags(_Enum _enum) : m_flags(UnderlyingType(_enum)){};

   public:
    /**
    * @brief Assignment operator for setting the flags using an enum value.
    *
    * @param _enum The enum value to set the flags to.
    */
    [[nodiscard("")]] constexpr void operator=(_Enum _enum) noexcept { m_flags = (UnderlyingType)_enum; }

    /**
    * @brief Bitwise AND assignment operator to perform AND operation with an enum value.
    *
    * @param _enum The enum value to AND with the existing flags.
    */
    [[nodiscard("")]] constexpr void operator&=(_Enum _enum) noexcept { m_flags &= (UnderlyingType)_enum; }

    /**
    * @brief Bitwise OR assignment operator to perform OR operation with an enum value.
    *
    * @param _enum The enum value to OR with the existing flags.
    */
    [[nodiscard("")]] constexpr void operator|=(_Enum _enum) noexcept { m_flags |= (UnderlyingType)_enum; }

    /**
    * @brief Bitwise XOR assignment operator to perform XOR operation with an enum value.
    *
    * @param _enum The enum value to XOR with the existing flags.
    */
    [[nodiscard("")]] constexpr void operator^=(_Enum _enum) noexcept { m_flags ^= (UnderlyingType)_enum; }

    /**
    * @brief Bitwise AND operator to check if a specific flag is set.
    *
    * @param _enum The enum value to check.
    * @return bool True if the specified flag is set; otherwise, false.
    */
    [[nodiscard("")]] constexpr bool operator&(_Enum _enum) noexcept { return m_flags & (UnderlyingType)_enum; }

    /**
    * @brief Bitwise OR operator to check if a specific flag is set.
    * 
    * @param _enum The enum value to check.
    * @return bool True if the specified flag is set; otherwise, false.
    */
    [[nodiscard("")]] constexpr bool operator|(_Enum _enum) const noexcept { return m_flags & (UnderlyingType)_enum; }

    /**
    * @brief Bitwise XOR operator to check if a specific flag is set.
    * 
    * @param _enum The enum value to check.
    * @return bool True if the specified flag is set; otherwise, false.
	*/
    [[nodiscard("")]] constexpr bool operator^(_Enum _enum) const noexcept { return m_flags & (UnderlyingType)_enum; }

    /**
    * @bried Comparison operator to check if the flags are equal to a specific enum value.
    * 
    * @param _enum The enum value to compare with.
    * @ return bool True if the flags are equal to the specified enum value; otherwise, false.
    */
    [[nodiscard("")]] constexpr bool operator==(_Enum _enum) const noexcept { return m_flags == (UnderlyingType)_enum; }

    /**
    * @bried Comparison operator to check if the flags are not equal to a specific enum value.
    * 
    * @param _enum The enum value to compare with.
    * @ return bool True if the flags are not equal to the specified enum value; otherwise, false.
    */
    [[nodiscard("")]] constexpr bool operator!=(_Enum _enum) const noexcept { return m_flags != (UnderlyingType)_enum; }

   public:
    /**
    * @brief Get the combined bit flags as an underlying integral type.
    *
    * @return UnderlyingType The combined bit flags as an integral type.
    */
    [[nodiscard("")]] UnderlyingType GetFlags() const noexcept { return (UnderlyingType)m_flags; }
};

}  // namespace Rake::libraries
