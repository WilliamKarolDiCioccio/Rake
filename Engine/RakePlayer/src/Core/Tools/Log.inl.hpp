/*****************************************************************/ /**
 * \file   Logger.inl.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Common.h"
#include "Core/EngineConfig.h"

DISABLE_ALL_WARNINGS

#if defined(LOGGER_ENABLED) == RK_TRUE

#include <vector>
#include <string>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

#include "Core/Error/RkSignal.hpp"

namespace Rake::Core
{

static class RkLogManager final
{
  public:
    static inline std::shared_ptr<spdlog::logger> Init(std::vector<spdlog::sink_ptr> _sinks) noexcept
    {
        try
        {
            auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(DEFAULT_LOG_FILE_NAME, MEBIBYTES(1), LOG_FILES_PER_SESSION, false);
            fileSink->set_pattern("[%l][%H:%M:%S.%e] %v");

            auto logger = std::make_shared<spdlog::logger>(DEFAULT_LOGGER_NAME, fileSink);
            spdlog::set_default_logger(logger);
            logger->set_level(spdlog::level::trace);
            logger->flush_on(spdlog::level::trace);

            logger->trace(__DATE__);

            return logger;
        }
        catch (const spdlog::spdlog_ex &e)
        {
            return nullptr;

            RK_SIGABRT;
        }
    }

    static inline void Release() noexcept
    {
        spdlog::shutdown();
    }
};

} // namespace Rake::Core

#define CRITICAL(...)                                                                                                                                                                                                                                    \
    if (spdlog::get(DEFAULT_LOGGER_NAME) != NULL_PTR)                                                                                                                                                                                                    \
    spdlog::get(DEFAULT_LOGGER_NAME)->critical(__VA_ARGS__)
#define ERROR(...)                                                                                                                                                                                                                                       \
    if (spdlog::get(DEFAULT_LOGGER_NAME) != NULL_PTR)                                                                                                                                                                                                    \
    spdlog::get(DEFAULT_LOGGER_NAME)->error(__VA_ARGS__)
#define WARN(...)                                                                                                                                                                                                                                        \
    if (spdlog::get(DEFAULT_LOGGER_NAME) != NULL_PTR)                                                                                                                                                                                                    \
    spdlog::get(DEFAULT_LOGGER_NAME)->warn(__VA_ARGS__)
#define INFO(...)                                                                                                                                                                                                                                        \
    if (spdlog::get(DEFAULT_LOGGER_NAME) != NULL_PTR)                                                                                                                                                                                                    \
    spdlog::get(DEFAULT_LOGGER_NAME)->info(__VA_ARGS__)
#define DEBUG(...)                                                                                                                                                                                                                                       \
    if (spdlog::get(DEFAULT_LOGGER_NAME) != NULL_PTR)                                                                                                                                                                                                    \
    spdlog::get(DEFAULT_LOGGER_NAME)->debug(__VA_ARGS__)
#define TRACE(...)                                                                                                                                                                                                                                       \
    if (spdlog::get(DEFAULT_LOGGER_NAME) != NULL_PTR)                                                                                                                                                                                                    \
    spdlog::get(DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__)

#else

#define LOG_FATAL(msg)   (void)0
#define LOG_ERROR(msg)   (void)0
#define LOG_WARNING(msg) (void)0
#define LOG_INFO(msg)    (void)0
#define LOG_DEBUG(msg)   (void)0
#define LOG_TRACE(msg)   (void)0

#endif

RESTORE_ALL_WARNINGS
