/*****************************************************************/ /**
 * \file   Logger.inl.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Core/EngineConfig.def.h"

#if defined(LOGGER_ENABLED) == RK_TRUE

#include "Types.h"

#include "Core/Errors/RkException.hpp"

#include <vector>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace Rake::Core
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

} // namespace Rake::Core

#define CRITICAL(...) Rake::Core::RkLogManager::GetDefaultLogger()->critical(#__VA_ARGS__)
#define ERROR(...)    Rake::Core::RkLogManager::GetDefaultLogger()->error(#__VA_ARGS__)
#define WARN(...)     Rake::Core::RkLogManager::GetDefaultLogger()->warn(#__VA_ARGS__)
#define INFO(...)     Rake::Core::RkLogManager::GetDefaultLogger()->info(#__VA_ARGS__)

#ifdef RK_DEBUG
#define DEBUG(...) Rake::Core::RkLogManager::GetDefaultLogger()->debug(#__VA_ARGS__)
#define TRACE(...) Rake::Core::RkLogManager::GetDefaultLogger()->trace(#__VA_ARGS__)
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
