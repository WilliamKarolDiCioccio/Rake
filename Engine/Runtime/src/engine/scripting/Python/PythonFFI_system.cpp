#include "pch.hpp"

#include "engine/scripting/Python/PythonFFI_system.hpp"

#include "platform/win32/win32_process.hpp"

RK_DISABLE_WARNINGS
#define PY_SSIZE_T_CLEAN
#include <Python.h>
RK_RESTORE_WARNINGS

namespace Rake::engine::scripting {

PythonFFISystem::Config PythonFFISystem::m_config;

PythonFFISystem::PythonFFISystem() {
    if (m_instance != nullptr) throw std::runtime_error("Python FFI system already created!");

    m_instance = this;

    if (m_config.enabled) {
        InitializePython();
    }
}

PythonFFISystem::~PythonFFISystem() {
    if (m_config.enabled) {
        FinalizePython();
    }
}

void PythonFFISystem::InitializePython() const {
#ifdef PLATFORM_WINDOWS
    platform::Win32::CreateConsole(L"PythonScript");
#endif

    PyConfig config = {};
    PyConfig_InitPythonConfig(&config);

    config.program_name = Py_DecodeLocale("RkRuntime", NULL);

    auto status = Py_InitializeFromConfig(&config);

    if (PyStatus_Exception(status)) throw std::runtime_error("Failed to initialize Python interpreter!");

    PyConfig_Clear(&config);
}

void PythonFFISystem::FinalizePython() const {
    Py_Finalize();

#ifdef PLATFORM_WINDOWS
    platform::Win32::DestroyConsole();
#endif
}

bool PythonFFISystem::ParseOptionArguments(const char* _arg) noexcept {
    if (strncmp(_arg, "enable", 7) == NULL) {
        m_config.enabled = true;
    } else if (strncmp(_arg, "disable", 8) == NULL) {
        m_config.enabled = false;
    } else {
        return false;
    }

    return true;
}

bool PythonFFISystem::ExecuteFromFile(const std::string& _path, const std::wstring& _args) {
    if (!Py_IsInitialized()) {
        return false;
    }

    FILE* file = fopen(_path.c_str(), "r");
    if (file == nullptr) {
        PyErr_Print();
        return false;
    }

    int result = PyRun_SimpleFile(file, _path.c_str());

    if (result != 0) {
        PyErr_Print();
        fclose(file);
        return false;
    }

    fclose(file);

    return true;
}

bool PythonFFISystem::ExecuteFromString(const std::string& _script, const std::wstring& _args) {
    if (!Py_IsInitialized()) {
        return false;
    }

    int result = PyRun_SimpleString(_script.c_str());

    if (result != 0) {
        PyErr_Print();
        return false;
    }

    return true;
}

std::future<bool> PythonFFISystem::ExecuteFromFileAsync(const std::string& _path, const std::wstring& _args) {
    auto runScript = [=]() {
        if (!m_config.enabled) return false;

        InitializePython();

        if (!ExecuteFromFile(_path, _args)) {
            FinalizePython();
            return false;
        }

        FinalizePython();
        return true;
    };

    return std::async(std::launch::async, runScript);
}

std::future<bool> PythonFFISystem::ExecuteFromStringAsync(const std::string& _script, const std::wstring& _args) {
    auto runScript = [=]() {
        if (!m_config.enabled) return false;

        InitializePython();

        if (!ExecuteFromString(_script, _args)) {
            FinalizePython();
            return false;
        }

        FinalizePython();
        return true;
    };

    return std::async(std::launch::async, runScript);
}

NODISCARD const PythonFFISystem* PythonFFISystem::Get() noexcept { return m_instance; }

}  // namespace Rake::engine::scripting
