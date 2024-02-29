#pragma once

#include "base.hpp"

#include <future>

namespace Rake::engine::scripting {

class PythonFFISystem final {
   private:
    static inline PythonFFISystem* m_instance = nullptr;

    bool m_enabled;

   public:
    RK_API PythonFFISystem(bool _enabled);
    RK_API ~PythonFFISystem();

   private:
    void Setup() const;
    void Teardown() const;

   public:
    RK_API bool ExecuteFromFile(const std::string& _path, const std::wstring& _args);
    RK_API bool ExecuteFromString(const std::string& _script, const std::wstring& _args);
    RK_API std::future<bool> ExecuteFromFileAsync(const std::string& _path, const std::wstring& _args);
    RK_API std::future<bool> ExecuteFromStringAsync(const std::string& _script, const std::wstring& _args);

   public:
    RK_API NODISCARD static const PythonFFISystem* Get() noexcept;
};

}  // namespace Rake::engine::scripting
