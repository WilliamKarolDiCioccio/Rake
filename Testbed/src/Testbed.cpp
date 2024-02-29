#include "Testbed.hpp"

#include <thread>
#include <chrono>

#include <core/file_system.hpp>
#include <core/input_system.hpp>
#include <engine/entity/scene.hpp>
#include <platform/win32/win32_process.hpp>

using namespace std::chrono_literals;

namespace Testbed {

Testbed::Testbed(int _argc, const char* _argv[]) : application::Application(_argc, _argv) {}

Testbed::~Testbed() {}

void Testbed::OnStart() noexcept {
    auto window = m_windowSystem->RegisterWindow("MainWindow");

    window->SetSize({1280, 720});
    window->SetResizeable(false);
    window->SetTitle(L"WIN32 - Rake Engine - main window");

    window->Show(true);
    window->Highlight();

    m_windowSystem->LoadState("MainWindow");

    m_pythonFFISystem->ExecuteFromFile("test.py", L"");
}

void Testbed::OnUpdate() noexcept {
    if (core::InputSystem::IsKeyboardKeyFirstPressed("EscapeApp")) {
        Stop();
    }
}

void Testbed::OnStop() noexcept {
    m_windowSystem->SaveState("MainWindow");
    m_windowSystem->UnregisterWindow("MainWindow");
}

void Testbed::OnImGuiRender(core::Window* _windowHandle) noexcept {}

}  // namespace Testbed
