#include "pch.hpp"

#include "tools/profiler.hpp"

namespace Rake::tools {

nlohmann::json Profiler::m_data;
std::wstring Profiler::m_sessionName;
std::wstring Profiler::m_profilesPath;
std::stack<Profiler::Profile> Profiler::m_activeProfiles;
std::mutex Profiler::m_mutex;
bool Profiler::m_initialized;

void Profiler::Initialize(const std::wstring &_sessionName, const std::wstring &_profilesDir) noexcept {
    if (m_initialized) return;

    std::lock_guard<std::mutex> lock(m_mutex);

    m_initialized = true;

    const auto dateAndTime = core::Timer::GetTimestamp("%d-%B-%Y_%H;%M;%S");

    m_sessionName = _sessionName;
    m_profilesPath = _profilesDir + L"/" + m_sessionName + L"_" + libraries::ByteToWideString(dateAndTime) + L".json";

    core::CreateDirectory(_profilesDir);
    core::CreateFile(m_profilesPath);

    m_data["otherData"] = nlohmann::json::object();
    m_data["traceEvents"] = nlohmann::json::array();
}

void Profiler::Shutdown() noexcept {
    if (!m_initialized) return;

    m_initialized = false;

    std::lock_guard<std::mutex> lock(m_mutex);

    core::WriteJSON(m_profilesPath, m_data);

    m_initialized = false;
}

void Profiler::BeginProfile(const std::wstring &_name, ProfileCategory _category) noexcept {
    auto threadID = std::this_thread::get_id();
    const auto start = std::chrono::high_resolution_clock::now();

    Profile profile = {
        .category = _category,
        .name = _name,
        .threadID = std::hash<std::thread::id>{}(threadID),
        .start = std::chrono::time_point_cast<std::chrono::microseconds>(start).time_since_epoch().count(),
    };

    std::lock_guard<std::mutex> lock(m_mutex);

    m_activeProfiles.push(profile);
}

void Profiler::EndProfile() noexcept {
    RK_ASSERT(!m_activeProfiles.empty());

    auto &profile = m_activeProfiles.top();

    const auto end = std::chrono::high_resolution_clock::now();
    profile.end = std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch().count();

    nlohmann::json traceEvent;
    traceEvent["cat"] = m_categories[(uint8_t)profile.category];
    traceEvent["dur"] = profile.end - profile.start;
    traceEvent["name"] = libraries::WideToByteString(profile.name);
    traceEvent["ph"] = "X";
    traceEvent["pid"] = 0;
    traceEvent["tid"] = profile.threadID;
    traceEvent["ts"] = profile.start;

    std::lock_guard<std::mutex> lock(m_mutex);

    m_data["traceEvents"].push_back(traceEvent);

    m_activeProfiles.pop();
}

}  // namespace Rake::tools
