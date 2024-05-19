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

    primaryWindow->SetTitle(L"Rake Engine - Multicontext Primary - x86_64 - WIN32 - Vulkan");

    m_rendererSystem->CreateContext("PrimaryContext", primaryWindow);
}

void Testbed::OnUpdate() noexcept {
    if (core::InputSystem::IsKeyboardKeyFirstPressed("EscapeApp")) {
        Stop();
    }
}

void Testbed::OnStop() noexcept {}

void Testbed::OnImGuiRender() noexcept {}

}  // namespace Testbed
