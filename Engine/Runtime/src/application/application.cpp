#include "pch.hpp"

#include "application/application.hpp"

#include "core/event_system.hpp"

using namespace std::chrono_literals;

namespace Rake::application {

Application::Application() {
    if (m_instance != nullptr) throw std::runtime_error("Application already created!");

    m_instance = this;

    tools::Logger::Initialize(L"DebugSession", L"./logs");
    tools::Profiler::Initialize(L"DebugSession", L"./profiles");

    Rake::tools::Profiler::BeginProfile(L"Initialization - Global", Rake::tools::ProfileCategory::function);

    m_cVarSystem = std::make_unique<core::CVarSystem>();
    m_windowSystem = core::WindowSystem::CreateNative();
    m_inputSystem = core::InputSystem::CreateNative();
    m_scene = std::make_unique<engine::entity::Scene>();
    m_rendererSystem = engine::graphics::RendererSystem::CreateWithBackend();
    m_pythonFFISystem = std::make_unique<engine::scripting::PythonFFISystem>();

    tools::Profiler::EndProfile();
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
        m_rendererSystem->Render();
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
