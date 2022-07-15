#include "src/RkPch.h"

#include "Log.hpp"

#if defined(LOGGER_ENABLED) == RK_TRUE

namespace Rake::Tools
{

std::shared_ptr<spdlog::logger> RkLogManager::m_defaultLogger = nullptr;

void RkLogManager::Init()
{
    try
    {
        std::shared_ptr<spdlog::logger> logger = spdlog::rotating_logger_mt("DefaultLogger", "logs/session.log", MEBIBYTES(4), 1);

        logger->set_pattern("[%H]-[%n]-[%l]: %v");
        logger->set_level(spdlog::level::info);
        logger->flush_on(spdlog::level::info);

        logger->trace("Starting session...");

        m_defaultLogger = logger;
    }
    catch (const spdlog::spdlog_ex &e)
    {
        std::cout << e.what() << '\n';
    }
}

void RkLogManager::Release()
{
    spdlog::drop_all();
}

} // namespace Rake::Tools

#endif
