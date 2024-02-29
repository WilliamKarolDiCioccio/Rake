#include "pch.hpp"

#include "engine/scripting/Python/PythonFFI.hpp"

#include "platform/win32/win32_process.hpp"

RK_DISABLE_WARNINGS
#define PY_SSIZE_T_CLEAN
#include <Python.h>
RK_RESTORE_WARNINGS

namespace Rake::engine::scripting {

PythonFFISystem::PythonFFISystem(bool _enabled) : m_enabled(_enabled) {
    if (m_instance != nullptr) throw std::runtime_error("Python FFI system already created!");

    m_instance = this;

    if (m_enabled) {
        Setup();
    }
}

PythonFFISystem::~PythonFFISystem() {
    if (m_enabled) {
        Teardown();
    }
}

void PythonFFISystem::Setup() const {
    platform::CreateConsole(L"PythonScript");

    PyConfig config = {};
    PyConfig_InitPythonConfig(&config);

    config.program_name = Py_DecodeLocale("RkRuntime", NULL);

    auto status = Py_InitializeFromConfig(&config);

    if (PyStatus_Exception(status)) throw std::runtime_error("Failed to initialize Python interpreter!");

    PyConfig_Clear(&config);
}

void PythonFFISystem::Teardown() const {
    Py_Finalize();

    platform::DestroyConsole();
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
        if (!m_enabled) return false;

        Setup();

        if (!ExecuteFromFile(_path, _args)) {
            Teardown();
            return false;
        }

        Teardown();
        return true;
    };

    return std::async(std::launch::async, runScript);
}

std::future<bool> PythonFFISystem::ExecuteFromStringAsync(const std::string& _script, const std::wstring& _args) {
    auto runScript = [=]() {
        if (!m_enabled) return false;

        Setup();

        if (!ExecuteFromString(_script, _args)) {
            Teardown();
            return false;
        }

        Teardown();
        return true;
    };

    return std::async(std::launch::async, runScript);
}

NODISCARD const PythonFFISystem* PythonFFISystem::Get() noexcept { return m_instance; }

}  // namespace Rake::engine::scripting
