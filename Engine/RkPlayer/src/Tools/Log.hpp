/*****************************************************************/ /**
 * \file   Log.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Core/Config.h"

#if defined(LOGGER_ENABLED) == RK_TRUE

#define LevelFatal 1
#define LevelError 2
#define LevelWarn  3
#define LevelInfo  4
#define LevelDebug 5
#define LevelTrace 6

namespace Rake::Tools
{

class Logger
{
  private:
    const char *m_logLevel[6] = {"FATAL", "ERROR", "WARN", "INFO", "DEBUG", "TRACE"};

  public:
    virtual ~Logger() = default;

  public:
    void Fatal(const wchar_t *_msg, ...);
    void Error(const wchar_t *_msg, ...);
    void Warn(const wchar_t *_msg, ...);
    void Info(const wchar_t *_msg, ...);
    void Debug(const wchar_t *_msg, ...);
    void Trace(const wchar_t *_msg, ...);
};

class ConsoleLogger final : public Logger
{
  public:
    ConsoleLogger();
};

class FileLogger final : public Logger
{
  public:
    FileLogger(const char *_fileName, B32 _fileSize);
};

class LogManager final
{
  private:
    LogManager() = default;

  public:
    void RegisterLogger();
    std::shared_ptr<Logger> GetLogger(B32 _key);
};

} // namespace Rake::Tools

#define LogFatal(...)
#define LogError(...)
#define LogWarn(...)
#define LogInfo(...)

#ifdef RK_DEBUG
#define LogDebug(...)
#define LogTrace(...)
#else
#define LogDebug(...) ((void)0)
#define LogTrace(...) ((void)0)
#endif

#else

#define LogFatal(...) ((void)0)
#define LogError(...) ((void)0)
#define LogWarn(...)  ((void)0)
#define LogInfo(...)  ((void)0)
#define LogDebug(...) ((void)0)
#define LogTrace(...) ((void)0)

#endif
