#include "pch.hpp"

#include "core/window_system.hpp"

#include "core/file_system.hpp"
#ifdef PLATFORM_WINDOWS
#include "platform/win32/win32_window_system.hpp"
#endif

namespace Rake::core {

WindowSystem::WindowSystem() {
    if (m_instance != nullptr) throw std::runtime_error("Window system already created!");

    m_instance = this;

    m_windowRegistry.reserve(8);
    m_nativeWindowRegistry.reserve(8);
};

WindowSystem::~WindowSystem() {
    m_instance = nullptr;
    delete (m_instance);
}

void WindowSystem::Update() noexcept {
    for (auto &[name, window] : m_windowRegistry) {
        window->Update();
    }
}

void WindowSystem::LoadWindowState(const std::string &_name) noexcept {
    auto &window = m_windowRegistry[_name];

    try {
        auto data = ReadJSON(L"WindowStates.json");

        window->ToggleVisibility(data[_name]["isVisible"]);
        window->ToggleMinimize(data[_name]["IsMinimized"]);
        window->ToggleMaximize(data[_name]["IsMaximized"]);
        window->ToggleFullscreen(data[_name]["IsFullscreen"]);
        window->ToggleResizeability(data[_name]["IsResizeable"]);
        window->ToggleCursorVisibility(data[_name]["isCursorVisible"]);
        window->ToggleCursorLock(data[_name]["IsCursorLocked"]);
        window->ToggleCursorClipping(data[_name]["IsCursorClipped"]);
        window->DisableWindowCapture(data[_name]["IsHiddenFromCapture"]);
    } catch (const std::exception &) {
        auto &windowState = window->GetState();

        window->ToggleVisibility(windowState.isVisible);
        window->ToggleMinimize(windowState.isMinimized);
        window->ToggleMaximize(windowState.isMaximized);
        window->ToggleFullscreen(windowState.isFullscreen);
        window->ToggleResizeability(windowState.isResizeable);
        window->ToggleCursorVisibility(windowState.isCursorVisible);
        window->ToggleCursorLock(windowState.isCursorLocked);
        window->ToggleCursorClipping(windowState.isCursorClipped);
        window->DisableWindowCapture(windowState.isWindowCaptureDisabled);

        SaveWindowState(_name);
    }
}

void WindowSystem::SaveWindowState(const std::string &_name) noexcept {
    const auto &windowState = m_windowRegistry[_name]->GetState();

    nlohmann::json data;

    data[_name] = {
        {"isVisible", windowState.isVisible},
        {"IsMinimized", windowState.isMinimized},
        {"IsMaximized", windowState.isMaximized},
        {"IsFullscreen", windowState.isFullscreen},
        {"IsResizeable", windowState.isResizeable},
        {"isCursorVisible", windowState.isCursorVisible},
        {"IsCursorLocked", windowState.isCursorLocked},
        {"IsCursorClipped", windowState.isCursorClipped},
        {"isWindowCaptureDisabled", windowState.isWindowCaptureDisabled},
    };

    core::CreateFile(L"WindowStates.json");
    WriteJSON(L"WindowStates.json", data);
}

const std::shared_ptr<Window> &WindowSystem::CreateWindow(const std::string &_name) noexcept {
#ifdef PLATFORM_WINDOWS
    auto window = std::make_shared<platform::Win32::Win32Window>();
#endif

    m_nativeWindowRegistry[window->GetNativeHandle()] = _name;
    m_windowRegistry[_name] = std::move(window);

    return m_windowRegistry[_name];
}

void WindowSystem::DestroyWindow(const std::string &_name) noexcept {
    const auto &windowHandle = m_windowRegistry[_name]->GetNativeHandle();

    m_windowRegistry.erase(_name);
    m_nativeWindowRegistry.erase(windowHandle);
}

WindowSystem *WindowSystem::Get() noexcept { return m_instance; }

const std::shared_ptr<Window> WindowSystem::GetWindowHandleByName(const std::string &_name) noexcept {
    auto it = m_instance->m_windowRegistry.find(_name);

    if (it != m_instance->m_windowRegistry.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

const std::string WindowSystem::GetWindowNameByNativeHandle(void *_nativeHandle) noexcept {
    auto it = m_instance->m_nativeWindowRegistry.find(_nativeHandle);

    if (it != m_instance->m_nativeWindowRegistry.end()) {
        return it->second;
    } else {
        return "";
    }
}

const std::unordered_map<std::string, std::shared_ptr<Window>> &WindowSystem::GetWindowRegistry() noexcept {
    return m_instance->m_windowRegistry;
}

const std::unordered_map<void *, std::string> &WindowSystem::GetNativeWindowRegistry() noexcept {
    return m_instance->m_nativeWindowRegistry;
}

std::unique_ptr<WindowSystem> WindowSystem::CreateNative() noexcept {
#ifdef PLATFORM_WINDOWS
    return std::make_unique<platform::Win32::Win32WindowSystem>();
#endif
}

}  // namespace Rake::core
