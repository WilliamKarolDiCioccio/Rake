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

/**
 * @brief The Logger class is responsible for logging messages to a file and to stderr, the latter only in debug builds. 
 * 
 * @details
 * The Logger class is responsible for providing logging for the application. It can log messages of different levels of severity, such as fatal, error, warning, info, debug, and trace and output them to a file and to stderr.
 * The file name is the session name followed by the date and time of the session with the .log extension (e.g. "sessionName_2021-01-01_00;00;00.log").
 * The file is saved in the directory specified by the _logsDir parameter of the Initialize function.
 * Different levels of severity have different colors in the console output for better readability.
 * 
 * @see The Logger class is a static class, so it doesn't need to be instantiated.
 */
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
    /**
	 * @brief Initializes the Logger class.
	 * 
	 * @param _sessionName The name of the session.
	 * @param _logsDir The directory where the log files will be saved.
     * 
     * @note This function must be called before any other function of the logger. The Application class is responsible for calling this function.
	 */
    static void Initialize(const std::wstring &_sessionName, const std::wstring &_logsDir) noexcept;

    /**
     * @brief Shuts down the logger.
     * 
     * @note This function should be called after all the other functions of the logger. The Application class is responsible for calling this function.
	 */
    static void Shutdown() noexcept;

   private:
    /**
	 * @brief Flushes the message pool to the log file.
	 * 
	 * @note This function is called automatically by the logging functions when the message pool reaches a certain size to avoid continuous writing to the file.
	 */
    static void Flush() noexcept;

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
