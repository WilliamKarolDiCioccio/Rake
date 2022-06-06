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

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

namespace Rake::Core
{

RAKE_API class LogManager final
{
  public:
    static inline void Init(std::vector<spdlog::sink_ptr> &_sinks) noexcept
    {
        try
        {
            auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(DEFAULT_LOG_FILE_NAME, MEBIBYTES(1), LOG_FILES_PER_SESSION, false);
            fileSink->set_pattern(DEFAULT_LOG_PATTERN);

            _sinks.insert(_sinks.begin(), fileSink);

            auto logger = std::make_shared<spdlog::logger>(DEFAULT_LOGGER, fileSink);
            spdlog::set_default_logger(logger);
            logger->set_level(spdlog::level::trace);
            logger->flush_on(spdlog::level::trace);

            logger->trace(__DATE__);

            if (!spdlog::get(DEFAULT_LOGGER))
            {
                throw RkException("Unable to get DefaultLogger", __FILE__, __LINE__);
            }
        }
        catch (const spdlog::spdlog_ex &e)
        {
        }
    }

    static inline void Release() noexcept
    {
        spdlog::shutdown();
    }
};

} // namespace Rake::Core

#define CRITICAL(...) spdlog::get(DEFAULT_LOGGER)->critical(#__VA_ARGS__)
#define ERROR(...)    spdlog::get(DEFAULT_LOGGER)->error(#__VA_ARGS__)
#define WARN(...)     spdlog::get(DEFAULT_LOGGER)->warn(#__VA_ARGS__)
#define INFO(...)     spdlog::get(DEFAULT_LOGGER)->info(#__VA_ARGS__)
#define DEBUG(...)    spdlog::get(DEFAULT_LOGGER)->debug(#__VA_ARGS__)
#define TRACE(...)    spdlog::get(DEFAULT_LOGGER)->trace(#__VA_ARGS__)

#define REGISTER_LOGGER(newLogger)    spdlog::register_logger(newLogger);
#define UNREGISTER_LOGGER(loggerName) spdlog::drop(loggerName);

#define _CRITICAL(loggerName, ...) spdlog::get(loggerName)->critical(#__VA_ARGS__)
#define _ERROR(loggerName, ...)    spdlog::get(loggerName)->error(#__VA_ARGS__)
#define _WARN(loggerName, ...)     spdlog::get(loggerName)->warn(#__VA_ARGS__)
#define _INFO(loggerName, ...)     spdlog::get(loggerName)->info(#__VA_ARGS__)
#define _DEBUG(loggerName, ...)    spdlog::get(loggerName)->debug(#__VA_ARGS__)
#define _TRACE(loggerName, ...)    spdlog::get(loggerName)->trace(#__VA_ARGS__)

#else

#define CRITICAL(...) (void)0
#define ERROR(...)    (void)0
#define WARN(...)     (void)0
#define INFO(...)     (void)0
#define DEBUG(...)    (void)0
#define TRACE(...)    (void)0

#define REGISTER_LOGGER(newLogger)   (void)0
#define UNREGISTER_LOGGER(newLogger) (void)0

#define _CRITICAL(loggerName, ...) (void)0
#define _ERROR(loggerName, ...)    (void)0
#define _WARN(loggerName, ...)     (void)0
#define _INFO(loggerName, ...)     (void)0
#define _DEBUG(loggerName, ...)    (void)0
#define _TRACE(loggerName, ...)    (void)0

#endif
