#include "Testbed.hpp"

#include <thread>
#include <chrono>

#include <RKRuntime/core/file_system.hpp>
#include <RKRuntime/core/input_system.hpp>

using namespace std::chrono_literals;

namespace Testbed {

Testbed::Testbed() {}

Testbed::~Testbed() {}

void Testbed::OnStart() noexcept {
    auto& primaryWindow = m_windowSystem->CreateWindow("PrimaryWindow");
    auto& secondaryWindow = m_windowSystem->CreateWindow("SecondaryWindow");

    m_windowSystem->LoadWindowState("PrimaryWindow");
    m_windowSystem->LoadWindowState("SecondaryWindow");

    primaryWindow->SetTitle(L"Rake Engine - Multicontext Primary - x86_64 - WIN32 - Vulkan");
    secondaryWindow->SetTitle(L"Rake Engine - Multicontext Secondary - x86_64 - WIN32 - Vulkan");

    m_rendererSystem->CreateContext("PrimaryContext", primaryWindow);
    m_rendererSystem->CreateContext("SecondaryContext", secondaryWindow);
}

void Testbed::OnUpdate() noexcept {
    if (core::InputSystem::IsKeyboardKeyFirstPressed("EscapeApp")) {
        Stop();
    }
}

void Testbed::OnStop() noexcept {
    m_windowSystem->SaveWindowState("SecondaryWindow");
    m_windowSystem->DestroyWindow("SecondaryWindow");
    m_windowSystem->SaveWindowState("PrimaryWindow");
    m_windowSystem->DestroyWindow("PrimaryWindow");
}

void Testbed::OnImGuiRender() noexcept {}

}  // namespace Testbed
