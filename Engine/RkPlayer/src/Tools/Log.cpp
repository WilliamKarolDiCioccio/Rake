#include "src/RkPch.h"

#include "Log.hpp"

#if defined(LOGGER_ENABLED) == RK_TRUE

namespace Rake::Tools
{

std::shared_ptr<spdlog::logger> RkLogManager::defaultLogger = nullptr;

void RkLogManager::Init()
{
    try
    {
        std::vector<spdlog::sink_ptr> sinks;

        sinks.emplace_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(DEFAULT_LOG_FILE_NAME, MEBIBYTES(1), LOG_FILES_PER_SESSION, false));
        // sinks[0]->set_pattern("[%c]");

        defaultLogger = std::make_shared<spdlog::logger>(DEFAULT_LOGGER, sinks.begin(), sinks.end());
        // spdlog::set_default_logger(defaultLogger);
        defaultLogger->set_level(spdlog::level::trace);
        defaultLogger->flush_on(spdlog::level::trace);

        defaultLogger->trace("");

        // sinks[0]->set_pattern(DEFAULT_LOG_PATTERN);
    }
    catch (const spdlog::spdlog_ex e)
    {
        RK_SIGTERM;
    }
}

void RkLogManager::Release()
{
    // spdlog::shutdown();
}

} // namespace Rake::Tools

#endif
