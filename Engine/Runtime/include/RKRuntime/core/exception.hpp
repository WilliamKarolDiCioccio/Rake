#pragma once

#include "RKRuntime/base.hpp"

#ifdef RK_EXCEPTIONS_ENABLED

#include <exception>

#include "RKSTL/string.hpp"

namespace Rake::core {

/**
 * @brief Exception class for the engine.
 * @details 
 * This class is used to throw exceptions in the with special formatting needs.
 */
class Exception final : public std::exception {
   private:
    std::wstring m_msg;

   public:
    template <typename... _Args>
    explicit Exception(const std::string &_format, _Args &&..._args) noexcept {
        m_msg = libraries::ByteToWideString(libraries::FormatByteString(_format, std::make_format_args(_args...)));
    };

    template <typename... _Args>
    explicit Exception(const std::wstring &_format, _Args &&..._args) noexcept {
        m_msg = libraries::FormatWideString(_format, std::make_wformat_args(_args...));
    };

   public:
    /**
	 * @brief UNICODE version of the what() function.
	 * @return The message of the exception.
	 */
    const wchar_t *WWhat() const noexcept { return m_msg.c_str(); }
};

}  // namespace Rake::core

#define RkException(msg, ...) Rake::core::Exception(msg, __VA_ARGS__)

#else

#define RkException(msg, forUser) std::terminate();

#endif
