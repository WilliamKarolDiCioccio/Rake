#pragma once

#include "base.hpp"

#include <string>
#include <stack>
#include <unordered_map>
#include <mutex>
#include <thread>
#include <atomic>

#include <RKSTL/string.hpp>
#include "core/file_system.hpp"
#include "RKSTL/string.hpp"

namespace Rake::tools {

enum class ProfileCategory : uint8_t {
    function = 1 << 0,
    scope = 1 << 1,
};

class Profiler final {
   private:
    static inline std::string m_categories[2] = {"functioin", "scope"};

    struct Profile {
        ProfileCategory category;
        std::wstring name;
        size_t threadID;
        int64_t start, end;
    };

    static inline nlohmann::json m_data;
    static inline std::wstring m_sessionName;
    static inline std::wstring m_profilesPath;
    static inline std::stack<Profile> m_activeProfiles;
    static inline std::mutex m_mutex;
    static inline bool m_initialized;

   public:
    static void Initialize(const std::wstring &_sessionName, const std::wstring &_profilesPath) noexcept;
    static void Shutdown() noexcept;
    static void BeginProfile(const std::wstring &_name, ProfileCategory _category) noexcept;
    static void EndProfile() noexcept;
    static std::size_t Hasher(const Profile &_profile) noexcept;
};

void Profiler::Initialize(const std::wstring &_sessionName, const std::wstring &_profilesPath) noexcept {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_initialized) {
        m_initialized = true;

        core::CreateDirectory(_profilesPath);

        m_sessionName = _sessionName;
        m_profilesPath = _profilesPath;
        m_data["otherData"] = nlohmann::json::object();
        m_data["traceEvents"] = nlohmann::json::array();
    }
}

void Profiler::Shutdown() noexcept {
    std::lock_guard<std::mutex> lock(m_mutex);

    core::WriteJSON(m_profilesPath + L"/" + m_sessionName, m_data);

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
