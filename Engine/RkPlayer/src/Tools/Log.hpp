/*****************************************************************/ /**
 * \file   Logger.inl.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Core/Config.h"

#if defined(LOGGER_ENABLED) == RK_TRUE

#include <vector>

#include <RkSTL/internal/DisableWarnings.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/file_sinks.h>
#include <spdlog/details/registry.h>

#include <RkSTL/internal/RestoreWarnings.h>

namespace Rake::Tools
{

class RAKE_API RkLogManager final
{
  private:
    static std::shared_ptr<spdlog::logger> m_defaultLogger;

  public:
    static void Init();
    static void Release();

  public:
    static inline std::shared_ptr<spdlog::logger> &GetDefaultLogger()
    {
        return m_defaultLogger;
    }
};

} // namespace Rake::Tools

#define Critical(...) Rake::Tools::RkLogManager::GetDefaultLogger()->critical(#__VA_ARGS__)
#define Error(...)    Rake::Tools::RkLogManager::GetDefaultLogger()->error(#__VA_ARGS__)
#define Warn(...)     Rake::Tools::RkLogManager::GetDefaultLogger()->warn(#__VA_ARGS__)
#define Info(...)     Rake::Tools::RkLogManager::GetDefaultLogger()->info(#__VA_ARGS__)

#ifdef RK_DEBUG
#define Debug(...) Rake::Tools::RkLogManager::GetDefaultLogger()->debug(#__VA_ARGS__)
#define Trace(...) Rake::Tools::RkLogManager::GetDefaultLogger()->trace(#__VA_ARGS__)
#else
#define Debug(...) ((void)0)
#define Trace(...) ((void)0)
#endif

#else

#define Critical(...) ((void)0)
#define Error(...)    ((void)0)
#define Warn(...)     ((void)0)
#define Info(...)     ((void)0)
#define Debug(...)    ((void)0)
#define Trace(...)    ((void)0)

#endif
