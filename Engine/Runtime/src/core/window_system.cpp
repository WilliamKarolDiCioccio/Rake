#include "pch.hpp"

#include "core/window_system.hpp"

#include "application/app_callbacks.hpp"
#include "core/file_system.hpp"
#ifdef PLATFORM_WINDOWS
#include "platform/win32/win32_window_system.hpp"
#endif

namespace Rake::core {

WindowSystem::WindowSystem() {
    if (m_instance != nullptr) throw std::runtime_error("Window system already created!");

    m_instance = this;
};

WindowSystem::~WindowSystem() {
    m_instance = nullptr;
    delete (m_instance);
}

void WindowSystem::LoadState(const std::string &_name) noexcept {
    auto &window = m_windowRegistry[_name];

    try {
        if (!core::FileExists(L"WindowsState.json")) core::CreateFile(L"WindowsState.json");

        auto data = ReadJSON(L"WindowsState.json");

        window->Fullscreen(data[_name]["IsFullscreen"]);
        window->Maximize(data[_name]["IsMaximized"]);
    } catch (const std::exception &) {
        SaveState(_name);
    }
}

void WindowSystem::SaveState(const std::string &_name) noexcept {
    const auto &windowState = m_windowRegistry[_name]->GetState();

    nlohmann::json data;

    std::hash<std::string> hasher;

    data[_name] = {
        {"IsFullscreen", windowState.isFullscreen},
        {"IsMaximized", windowState.isMaximized},
    };

    if (!core::FileExists(L"WindowsState.json")) core::CreateFile(L"MenusState.json");

    WriteJSON(L"WindowsState.json", data);
}

Window *WindowSystem::RegisterWindow(const std::string &_name) noexcept {
#ifdef PLATFORM_WINDOWS
    auto window = std::make_shared<platform::Win32::Win32Window>();
#endif

    auto ptr = window.get();

    m_nativeWindowRegistry[window->GetNativeHandle()] = _name;
    m_windowRegistry[_name] = std::move(window);

    return ptr;
}

void WindowSystem::UnregisterWindow(const std::string &_name) noexcept {
    const auto &windowHandle = m_windowRegistry[_name]->GetNativeHandle();

    m_windowRegistry.erase(_name);
    m_nativeWindowRegistry.erase(windowHandle);
}

const WindowSystem *WindowSystem::Get() noexcept { return m_instance; }

Window *WindowSystem::GetWindowByTitle(const std::string &_title) noexcept { return m_windowRegistry[_title].get(); }

const std::unordered_map<void *, std::string> &WindowSystem::GetNativeWindowRegistry() noexcept {
    return m_nativeWindowRegistry;
}

const std::unordered_map<std::string, std::unique_ptr<Window>> &WindowSystem::GetWindowRegistry() noexcept {
    return m_windowRegistry;
}

std::unique_ptr<WindowSystem> WindowSystem::CreateNative() noexcept {
#ifdef PLATFORM_WINDOWS
    return std::make_unique<platform::Win32::Win32WindowSystem>();
#endif
}

}  // namespace Rake::core
