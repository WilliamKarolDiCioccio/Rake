#pragma once

#include <iostream>

#include "RKRuntime/base.hpp"

#include "RKRuntime/core/timer.hpp"
#include "RKRuntime/core/file_system.hpp"

#include <RKSTL/string.hpp>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

namespace Rake::tools {

class RK_API Logger final {
   private:
    static std::wstring m_sessionName;
    static std::wstring m_logsPath;
    static std::wstringstream m_msgPool;
    static size_t m_msgPoolSize;
    static bool m_initialized;

   private:
    Logger() = delete;

   public:
    static void Initialize(const std::wstring &_sessionName, const std::wstring &_logsDir) noexcept;
    static void Shutdown() noexcept;
    static void Flush() noexcept;

    template <typename... _Args>
    static void Fatal(const std::wstring &_format, _Args &&..._args) noexcept;

    template <typename... _Args>
    static void Error(const std::wstring &_format, _Args &&..._args) noexcept;

    template <typename... _Args>
    static void Warn(const std::wstring &_format, _Args &&..._args) noexcept;

    template <typename... _Args>
    static void Info(const std::wstring &_format, _Args &&..._args) noexcept;

#ifdef RK_LOG_DEBUG_ENABLED
    template <typename... _Args>
    static void Debug(const std::wstring &_format, _Args &&..._args) noexcept;
#endif

#ifdef RK_LOG_TRACE_ENABLED
    template <typename... _Args>
    static void Trace(const std::wstring &_format, _Args &&..._args) noexcept;
#endif
};

template <typename... _Args>
void Logger::Fatal(const std::wstring &_format, _Args &&..._args) noexcept {
    const auto msg = libraries::FormatWideString(_format, std::make_wformat_args(_args...)) + L'\n';

#ifdef RK_DEBUG
    std::wcerr << MAGENTA << msg << RESET;
#endif

    m_msgPool << msg;
    m_msgPoolSize += msg.size();

    Flush();
}

template <typename... _Args>
void Logger::Error(const std::wstring &_format, _Args &&..._args) noexcept {
    const auto msg = libraries::FormatWideString(_format, std::make_wformat_args(_args...)) + L'\n';

#ifdef RK_DEBUG
    std::wcerr << RED << msg << RESET;
#endif

    m_msgPool << msg;
    m_msgPoolSize += msg.size();

    Flush();
}

template <typename... _Args>
void Logger::Warn(const std::wstring &_format, _Args &&..._args) noexcept {
    const auto msg = libraries::FormatWideString(_format, std::make_wformat_args(_args...)) + L'\n';

#ifdef RK_DEBUG
    std::wcerr << YELLOW << msg << RESET;
#endif

    m_msgPool << msg;
    m_msgPoolSize += msg.size();

    Flush();
}

template <typename... _Args>
void Logger::Info(const std::wstring &_format, _Args &&..._args) noexcept {
    const auto msg = libraries::FormatWideString(_format, std::make_wformat_args(_args...)) + L'\n';

#ifdef RK_DEBUG
    std::wcout << BLUE << msg << RESET;
#endif

    m_msgPool << msg;
    m_msgPoolSize += msg.size();

    Flush();
}

#ifdef RK_LOG_DEBUG_ENABLED

template <typename... _Args>
void Logger::Debug(const std::wstring &_format, _Args &&..._args) noexcept {
    const auto msg = libraries::FormatWideString(_format, std::make_wformat_args(_args...)) + L'\n';

#ifdef RK_DEBUG
    std::wcout << GREEN << msg << RESET;
#endif

    m_msgPool << msg;
    m_msgPoolSize += msg.size();

    Flush();
}

#endif

#ifdef RK_LOG_TRACE_ENABLED

template <typename... _Args>
void Logger::Trace(const std::wstring &_format, _Args &&..._args) noexcept {
    const auto msg = libraries::FormatWideString(_format, std::make_wformat_args(_args...)) + L'\n';

#ifdef RK_DEBUG
    std::wcout << msg;
#endif

    m_msgPool << msg;
    m_msgPoolSize += msg.size();

    Flush();
}

#endif

}  // namespace Rake::tools

#define RK_LOG_FATAL(fmt, ...) Rake::tools::Logger::Fatal(fmt, __VA_ARGS__);
#define RK_LOG_ERROR(fmt, ...) Rake::tools::Logger::Error(fmt, __VA_ARGS__)
#define RK_LOG_WARN(fmt, ...)  Rake::tools::Logger::Warn(fmt, __VA_ARGS__)
#define RK_LOG_INFO(fmt, ...)  Rake::tools::Logger::Info(fmt, __VA_ARGS__)

#ifdef RK_LOG_DEBUG_ENABLED
#define RK_LOG_DEBUG(fmt, ...) Rake::tools::Logger::Debug(fmt, __VA_ARGS__)
#define RK_LOG_TRACE(fmt, ...) Rake::tools::Logger::Trace(fmt, __VA_ARGS__)
#else
#define RK_LOG_DEBUG(fmt, ...)
#define RK_LOG_TRACE(fmt, ...)
#endif
