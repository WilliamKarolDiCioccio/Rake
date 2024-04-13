#pragma once

#include <string>
#include <stack>
#include <unordered_map>
#include <mutex>
#include <thread>
#include <atomic>

#include "RKRuntime/base.hpp"

#include "RKRuntime/core/timer.hpp"
#include "RKRuntime/core/file_system.hpp"

#include <RKSTL/string.hpp>

namespace Rake::tools {

/**
 * @brief The ProfileCategory flags.
 */
enum class ProfileCategory : uint8_t {
    function = 0 << 0,
    scope = 1 << 1,
};

/**
 * @brief The Profiler class is responsible for profiling the application.
 * 
 * @details
 * The Profiler class is responsible for profiling the application. It can profile functions and scopes, and save the data to a file.
 * The file name is the session name followed by the date and time of the session with the .json extension (e.g. "sessionName_2021-01-01_00;00;00.json").
 * The file is saved in the directory specified by the _profilesDir parameter of the Initialize function.
 * 
 * @see The Profiler class is a static class, so it doesn't need to be instantiated.
 */
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
    /**
	 * @brief Initializes the profiler.
	 * 
	 * @param _sessionName The name of the session.
	 * @param _profilesDir The directory where the profiles will be saved.
     * 
     * @note This function should be called before any other function of the profiler. The Application class is responsible for calling this function.
	 */
    static void Initialize(const std::wstring &_sessionName, const std::wstring &_profilesDir) noexcept;

    /**
     * @brief Shuts down the profiler.
     * 
     * @note This function should be called after all the other functions of the profiler. The Application class is responsible for calling this function.
	 */
    static void Shutdown() noexcept;

    /**
     * @brief Begins profiling a function or scope.
     * 
     * @details
     * This function should follow the stack pattern, where each call to BeginProfile should be followed by a call to EndProfile for the relative scope, otherwise an error will be thrown.
     * 
     * @param _name The name of the function or scope.
     * @param _category The category of the profile.
	 */
    static void BeginProfile(const std::wstring &_name, ProfileCategory _category) noexcept;

    /**
     * @brief Ends profiling a function or scope.
     */
    static void EndProfile() noexcept;
};

}  // namespace Rake::tools
