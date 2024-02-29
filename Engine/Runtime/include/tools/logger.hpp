#pragma once

#include <fstream>
#include <iostream>

#include "base.hpp"

#include "core/timer.hpp"
#include "core/exception.hpp"
#include "core/file_system.hpp"
#include "RKSTL/string.hpp"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

namespace Rake::tools {

class Logger final : public NonCopyable, public NonMovable {
   private:
    static inline Logger *m_instance = nullptr;

   public:
    Logger() {
        if (m_instance != nullptr) throw std::runtime_error("Logger already created!");

        m_instance = this;

        if (!core::FileExists(L"Session.log")) core::CreateFile(L"Session.log");

        const auto dateAndTime = core::Timer::GetTimestamp("date: %d-%B-%Y time: %H:%M:%S ");

        const auto header =
            L"<<<<<<<<<< Beginning session at " + libraries::ByteToWideString(dateAndTime) + L" >>>>>>>>>>\n";

        core::WriteFile(L"Session.log", header, core::FileOpenMode::truncate);
    }

    ~Logger() {
        const auto dateAndTime = core::Timer::GetTimestamp("date: %d-%B-%Y time: %H:%M:%S ");

        const auto footer =
            L"<<<<<<<<<< Ending session at " + libraries::ByteToWideString(dateAndTime) + L" >>>>>>>>>>\n";

        core::WriteFile(L"Session.log", footer, core::FileOpenMode::append);

        m_instance = nullptr;
        delete (m_instance);
    }

   public:
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
    std::wcout << MAGENTA << msg << RESET;
#endif

    core::WriteFile(L"Session.log", msg, core::FileOpenMode::append);
}

template <typename... _Args>
void Logger::Error(const std::wstring &_format, _Args &&..._args) noexcept {
    const auto msg = libraries::FormatWideString(_format, std::make_wformat_args(_args...)) + L'\n';

#ifdef RK_DEBUG
    std::wcout << RED << msg << RESET;
#endif

    core::WriteFile(L"Session.log", msg, core::FileOpenMode::append);
}

template <typename... _Args>
void Logger::Warn(const std::wstring &_format, _Args &&..._args) noexcept {
    const auto msg = libraries::FormatWideString(_format, std::make_wformat_args(_args...)) + L'\n';

#ifdef RK_DEBUG
    std::wcout << YELLOW << msg << RESET;
#endif

    core::WriteFile(L"Session.log", msg, core::FileOpenMode::append);
}

template <typename... _Args>
void Logger::Info(const std::wstring &_format, _Args &&..._args) noexcept {
    const auto msg = libraries::FormatWideString(_format, std::make_wformat_args(_args...)) + L'\n';

#ifdef RK_DEBUG
    std::wcout << BLUE << msg << RESET;
#endif

    core::WriteFile(L"Session.log", msg, core::FileOpenMode::append);
}

#ifdef RK_LOG_DEBUG_ENABLED

template <typename... _Args>
void Logger::Debug(const std::wstring &_format, _Args &&..._args) noexcept {
    const auto msg = libraries::FormatWideString(_format, std::make_wformat_args(_args...)) + L'\n';

#ifdef RK_DEBUG
    std::wcout << GREEN << msg << RESET;
#endif

    core::WriteFile(L"Session.log", msg, core::FileOpenMode::append);
}

#endif

#ifdef RK_LOG_TRACE_ENABLED

template <typename... _Args>
void Logger::Trace(const std::wstring &_format, _Args &&..._args) noexcept {
    const auto msg = libraries::FormatWideString(_format, std::make_wformat_args(_args...)) + L'\n';

#ifdef RK_DEBUG
    std::wcout << msg;
#endif

    core::WriteFile(L"Session.log", msg, core::FileOpenMode::append);
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
