#pragma once

#include "RKRuntime/base.hpp"

#include <future>

namespace Rake::engine::scripting {

class PythonFFISystem final {
   private:
    static inline PythonFFISystem* m_instance = nullptr;

    struct Config {
        bool enabled;

        Config() : enabled(true) {}
    };

    static Config m_config;

   public:
    RK_API PythonFFISystem();
    RK_API ~PythonFFISystem();

   private:
    void InitializePython() const;
    void FinalizePython() const;

   public:
    RK_API bool ExecuteFromFile(const std::string& _path, const std::wstring& _args);
    RK_API bool ExecuteFromString(const std::string& _script, const std::wstring& _args);
    RK_API std::future<bool> ExecuteFromFileAsync(const std::string& _path, const std::wstring& _args);
    RK_API std::future<bool> ExecuteFromStringAsync(const std::string& _script, const std::wstring& _args);

   public:
    RK_API static bool ParseOptionArguments(const std::string& _arg) noexcept;

    NODISCARD static const Config& GetConfig() noexcept { return m_config; }

    RK_API NODISCARD static const PythonFFISystem* Get() noexcept;
};

}  // namespace Rake::engine::scripting
