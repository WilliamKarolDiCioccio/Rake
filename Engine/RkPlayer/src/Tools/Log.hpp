/*****************************************************************/ /**
 * \file   Log.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include <unordered_map>

#include "Core/Config.h"
#include "Core/Base.hpp"

namespace Rake::Tools
{

class Logger;

RAKE_API class LoggersRegistry final
{
  public:
    static inline void RegisterInstance(const char *_key, Logger *_ptr)
    {
        m_instanceRegistry.insert({_key, _ptr});
    }
    static inline void UnregisterInstance(const char *_key)
    {
        m_instanceRegistry.erase(_key);
    }

  public:
    static inline const std::unordered_map<const char *, Logger *> &GetRegistry()
    {
        return m_instanceRegistry;
    }

  private:
    static inline std::unordered_map<const char *, Logger *> &Registry()
    {
        return m_instanceRegistry;
    }

  private:
    static inline std::unordered_map<const char *, Logger *> m_instanceRegistry = {};
};

RAKE_API class Logger
{
  protected:
    const char *m_levels[6] = {"FATAL", "ERROR", "WARN", "INFO", "DEBUG", "TRACE"};

  public:
    Logger()
    {
        LoggersRegistry::RegisterInstance("", this);
    }
    virtual ~Logger() = default;

  public:
    virtual inline void Fatal(const char *_msg) = 0;
    virtual inline void Error(const char *_msg) = 0;
    virtual inline void Warn(const char *_msg) = 0;
    virtual inline void Info(const char *_msg) = 0;
    virtual inline void Debug(const char *_msg) = 0;
    virtual inline void Trace(const char *_msg) = 0;
};

RAKE_API class ConsoleLogger final : public Logger
{
  public:
    ConsoleLogger(){};

  public:
    inline void Fatal(const char *_msg) override
    {
    }
    inline void Error(const char *_msg) override
    {
    }
    inline void Warn(const char *_msg) override
    {
    }
    inline void Info(const char *_msg) override
    {
    }
    inline void Debug(const char *_msg) override
    {
    }
    inline void Trace(const char *_msg) override
    {
    }
};

} // namespace Rake::Tools

#define LogFatal(...)
#define LogError(...)
#define LogWarn(...)
#define LogInfo(...)

#if DEBUG_ENABLED
#define LogDebug(...)
#else
#define LogDebug(...) ((void)0)
#endif

#if TRACE_ENABLED
#define LogTrace(...)
#else
#define LogTrace(...) ((void)0)
#endif
