/*****************************************************************/ /**
 * \file   Logger.inl.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#if defined(LOGGER_ENABLED) == RK_TRUE

#include <vector>

#include <RkSTL/Warnings.h>

DISABLE_ALL_WARNINGS
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/file_sinks.h>
RESTORE_ALL_WARNINGS

namespace Rake::Tools
{

class RAKE_API RkLogManager final
{
  private:
    static std::shared_ptr<spdlog::logger> defaultLogger;

  public:
    static void Init();
    static void Release();

  public:
    static inline std::shared_ptr<spdlog::logger> &GetDefaultLogger()
    {
        return defaultLogger;
    }
};

} // namespace Rake::Tools

#define CRITICAL(...) Rake::Tools::RkLogManager::GetDefaultLogger()->critical(#__VA_ARGS__)
#define ERROR(...)    Rake::Tools::RkLogManager::GetDefaultLogger()->error(#__VA_ARGS__)
#define WARN(...)     Rake::Tools::RkLogManager::GetDefaultLogger()->warn(#__VA_ARGS__)
#define INFO(...)     Rake::Tools::RkLogManager::GetDefaultLogger()->info(#__VA_ARGS__)

#ifdef RK_DEBUG
#define DEBUG(...) Rake::Tools::RkLogManager::GetDefaultLogger()->debug(#__VA_ARGS__)
#define TRACE(...) Rake::Tools::RkLogManager::GetDefaultLogger()->trace(#__VA_ARGS__)
#else
#define DEBUG(...) ((void)0)
#define TRACE(...) ((void)0)
#endif

#define REGISTER_LOGGER(newLogger)    spdlog::register_logger(newLogger);
#define UNREGISTER_LOGGER(loggerName) spdlog::drop(loggerName);

#else

#define CRITICAL(...) ((void)0)
#define ERROR(...)    ((void)0)
#define WARN(...)     ((void)0)
#define INFO(...)     ((void)0)
#define DEBUG(...)    ((void)0)
#define TRACE(...)    ((void)0)

#define REGISTER_LOGGER(newLogger)   ((void)0)
#define UNREGISTER_LOGGER(newLogger) ((void)0)

#endif
