#pragma(suppress : 4189)

#include "pch.hpp"

#include "application/application.hpp"
#include "application/app_callbacks.hpp"

#include "Core/ImGUI_manager.hpp"

using namespace std::chrono_literals;

namespace Rake::application {

Application::Application() {
    if (m_instance != nullptr) throw std::runtime_error("Application already created!");

    m_instance = this;

    tools::Logger::Initialize(L"DebugSession", L"./logs");
    tools::Profiler::Initialize(L"DebugSession", L"./profiles");

    if (args.size() > 1 && args.size() < 32) {
        if (args[1] == "--LICENSE") {
            std::wcout << core::ReadFile(L"LICENSE.md") << '\n';
            m_config.optionTerminatesPrematurely = true;
        } else if (args[1] == "--README") {
            std::wcout << core::ReadFile(L"README.md") << '\n';
            m_config.optionTerminatesPrematurely = true;
        } else {
            for (const auto& arg : args) {
                if (arg == "--disable-python-interpreter") {
                    m_config.disablePythonInterpreter = false;
                    RK_LOG_INFO(L"Python interpreter disabled!");
                }
            }
        }
    }

    if (!m_config.optionTerminatesPrematurely) {
        StopCallback::callback = [this]() { Stop(); };
        PauseCallback::callback = [this]() { Pause(); };
        ResumeCallback::callback = [this]() { Resume(); };

        m_cVarSystem = std::make_unique<core::CVarSystem>();
        m_windowSystem = core::WindowSystem::CreateNative();
        m_inputSystem = core::InputSystem::CreateNative();
        m_scene = std::make_unique<engine::entity::Scene>();
        m_renderer = std::make_unique<engine::graphics::Renderer>();
    m_pythonFFISystem = std::make_unique<engine::scripting::PythonFFISystem>();

        if (!m_config.disablePythonInterpreter) {
            m_pythonFFISystem = std::make_unique<engine::scripting::PythonFFISystem>(m_config.disablePythonInterpreter);
        }
    }
}

Application::~Application() {
    tools::Profiler::Shutdown();
    tools::Logger::Shutdown();

    m_instance = nullptr;
    delete (m_instance);
}

void Application::Start() noexcept {
    if (!m_state.isRunning) {
        std::lock_guard<std::mutex> lock(m_state.mutex);

        m_state.isRunning = true;

        OnStart();
    }
}

void Application::Pause() noexcept {
    if (!m_state.isPaused) {
        std::lock_guard<std::mutex> lock(m_state.mutex);

        m_state.isPaused = true;

        OnPause();
    }
}

void Application::Resume() noexcept {
    if (m_state.isPaused) {
        std::lock_guard<std::mutex> lock(m_state.mutex);

        m_state.isPaused = false;

        OnResume();
    }
}

void Application::Update() noexcept {
    while (m_state.isRunning) {
        if (m_state.isPaused) continue;

        m_timer.Tick();

        OnUpdate();

        m_windowSystem->Update();

        m_inputSystem->Poll();
    }
}

void Application::Stop() noexcept {
    if (m_state.isRunning) {
        std::lock_guard<std::mutex> lock(m_state.mutex);

        m_state.isRunning = false;

        OnStop();
    }
}

}  // namespace Rake::application
