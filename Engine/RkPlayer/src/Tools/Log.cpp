#include "src/RkPch.h"

#include "Log.hpp"

#if defined(LOGGER_ENABLED) == RK_TRUE

namespace Rake::Tools
{

ConsoleLogger::ConsoleLogger()
{
}

FileLogger::FileLogger(const char *_fileName, B32 _fileSize)
{
}

void LogManager::RegisterLogger()
{
}

std::shared_ptr<Logger> LogManager::GetLogger(B32 _key)
{
    return std::shared_ptr<Logger>();
}

void Logger::Fatal(const wchar_t *_msg, ...)
{
    std::wstringstream wss;
    wss << m_logLevel[1] << _msg;
    std::wcout << wss.str();
}

void Logger::Error(const wchar_t *_msg, ...)
{
}

void Logger::Warn(const wchar_t *_msg, ...)
{
}

void Logger::Info(const wchar_t *_msg, ...)
{
}

void Logger::Debug(const wchar_t *_msg, ...)
{
}

void Logger::Trace(const wchar_t *_msg, ...)
{
}

} // namespace Rake::Tools

#endif
