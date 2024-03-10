#pragma once

#include <string>
#include <stack>
#include <unordered_map>
#include <mutex>
#include <thread>
#include <atomic>

#include "base.hpp"

#include "core/timer.hpp"
#include "core/file_system.hpp"
#include <RKSTL/string.hpp>

namespace Rake::tools {

enum class ProfileCategory : uint8_t {
    function = 0 << 0,
    scope = 1 << 1,
};

class RK_API Profiler final {
   private:
    static inline std::string m_categories[2] = {"function", "scope"};

    struct Profile {
        ProfileCategory category;
        std::wstring name;
        size_t threadID;
        int64_t start, end;
    };

    static nlohmann::json m_data;
    static std::wstring m_sessionName;
    static std::wstring m_profilesPath;
    static std::stack<Profile> m_activeProfiles;
    static std::mutex m_mutex;
    static bool m_initialized;

   private:
    Profiler() = delete;

   public:
    static void Initialize(const std::wstring &_sessionName, const std::wstring &_profilesDir) noexcept;
    static void Shutdown() noexcept;
    static void BeginProfile(const std::wstring &_name, ProfileCategory _category) noexcept;
    static void EndProfile() noexcept;
};

}  // namespace Rake::tools
