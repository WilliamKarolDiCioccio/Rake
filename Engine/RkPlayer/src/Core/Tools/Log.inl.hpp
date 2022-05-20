/*****************************************************************/ /**
 * \file   Logger.inl.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Common.def.h"
#include "Core/EngineConfig.def.h"

#if defined(LOGGER_ENABLED) == RK_TRUE

#include <vector>
#include <string>

DISABLE_ALL_WARNINGS
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
RESTORE_ALL_WARNINGS

namespace Rake::Core
{

RAKE_API static class LogManager final
{
  private:
    std::vector<spdlog::sink_ptr> m_sinks;

  public:
    inline void Init() noexcept
    {
        try
        {
            auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(DEFAULT_LOG_FILE_NAME, MEBIBYTES(1), LOG_FILES_PER_SESSION, false);
            fileSink->set_pattern(DEFAULT_LOG_PATTERN);

            m_sinks.insert(m_sinks.begin(), fileSink);

            auto logger = std::make_shared<spdlog::logger>(DEFAULT_LOGGER_NAME, fileSink);
            spdlog::set_default_logger(logger);
            logger->set_level(spdlog::level::trace);
            logger->flush_on(spdlog::level::trace);

            logger->trace(__DATE__);
        }
        catch (const spdlog::spdlog_ex &e)
        {
        }
    }

    inline void Release() noexcept
    {
        spdlog::shutdown();
    }

    inline void AddLogger() noexcept
    {
    }

    inline void RemoveLogger() noexcept
    {
    }
};

} // namespace Rake::Core

#define CRITICAL(...)                                                                                                                                                                                                                                    \
    if (spdlog::get(DEFAULT_LOGGER_NAME) != NULL_PTR)                                                                                                                                                                                                    \
    spdlog::get(DEFAULT_LOGGER_NAME)->critical(#__VA_ARGS__)
#define ERROR(...)                                                                                                                                                                                                                                       \
    if (spdlog::get(DEFAULT_LOGGER_NAME) != NULL_PTR)                                                                                                                                                                                                    \
    spdlog::get(DEFAULT_LOGGER_NAME)->error(#__VA_ARGS__)
#define WARN(...)                                                                                                                                                                                                                                        \
    if (spdlog::get(DEFAULT_LOGGER_NAME) != NULL_PTR)                                                                                                                                                                                                    \
    spdlog::get(DEFAULT_LOGGER_NAME)->warn(#__VA_ARGS__)
#define INFO(...)                                                                                                                                                                                                                                        \
    if (spdlog::get(DEFAULT_LOGGER_NAME) != NULL_PTR)                                                                                                                                                                                                    \
    spdlog::get(DEFAULT_LOGGER_NAME)->info(#__VA_ARGS__)
#define DEBUG(...)                                                                                                                                                                                                                                       \
    if (spdlog::get(DEFAULT_LOGGER_NAME) != NULL_PTR)                                                                                                                                                                                                    \
    spdlog::get(DEFAULT_LOGGER_NAME)->debug(#__VA_ARGS__)
#define TRACE(...)                                                                                                                                                                                                                                       \
    if (spdlog::get(DEFAULT_LOGGER_NAME) != NULL_PTR)                                                                                                                                                                                                    \
    spdlog::get(DEFAULT_LOGGER_NAME)->trace(#__VA_ARGS__)

#else

#define LOG_FATAL(msg)   (void)0
#define LOG_ERROR(msg)   (void)0
#define LOG_WARNING(msg) (void)0
#define LOG_INFO(msg)    (void)0
#define LOG_DEBUG(msg)   (void)0
#define LOG_TRACE(msg)   (void)0

#endif
