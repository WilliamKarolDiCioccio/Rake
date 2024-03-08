#include "pch.hpp"

#include "tools/logger.hpp"

namespace Rake::tools {

std::wstring Logger::m_sessionName;
std::wstring Logger::m_logsPath;
std::wstringstream Logger::m_msgPool;
size_t Logger::m_msgPoolSize = 0;
bool Logger::m_initialized = false;

void Logger::Initialize(const std::wstring &_sessionName, const std::wstring &_logsDir) noexcept {
    if (m_initialized) return;

    m_initialized = true;
    const auto dateAndTime = core::Timer::GetTimestamp("%d-%B-%Y_%H;%M;%S");

    m_sessionName = _sessionName;
    m_logsPath = _logsDir + L"/" + m_sessionName + L"_" + libraries::ByteToWideString(dateAndTime) + L".log";

    const auto header = L"<<<<<<<<<< Beginning session >>>>>>>>>>\n";

    core::CreateDirectory(_logsDir);
    core::CreateFile(m_logsPath);
    core::WriteFile(m_logsPath, header, core::FileOpenMode::truncate);
}

void Logger::Shutdown() noexcept {
    if (!m_initialized) return;

    m_initialized = false;

    core::WriteFile(m_logsPath, m_msgPool.str(), core::FileOpenMode::truncate);

    const auto footer = L"<<<<<<<<<< Ending session >>>>>>>>>>\n";

    core::WriteFile(m_logsPath, footer, core::FileOpenMode::append);
}

void Logger::Flush() noexcept {
    if (!m_initialized) return;

    if (m_msgPoolSize >= RK_KIBIBYTES(10)) {
        core::WriteFile(m_logsPath, m_msgPool.str(), core::FileOpenMode::append);
        m_msgPool.clear();
        m_msgPoolSize = 0;
        std::wcout.flush();
    }
}

}  // namespace Rake::tools
