#pragma once

#include "RKRuntime/base.hpp"

#ifdef PLATFORM_WINDOWS

#include "RKRuntime/core/window_system.hpp"

#include "win32_common.hpp"

namespace Rake::platform::Win32 {

class Win32Window final : public core::Window {
   private:
    struct StyleProps {
        RECT rect;
        LONG style;
        LONG extendedStyle;
        UINT scalingFactor;
        HICON icon;
        HCURSOR cursor;
    };

    StyleProps m_styleProps = {};

   public:
    Win32Window();
    ~Win32Window();

   public:
    void Update() noexcept override;

   public:
    void ToggleVisibility(bool _visible) noexcept override;
    void DisableWindowCapture(bool _disable) noexcept override;
    void RequestFocus() noexcept;
    void ToggleMinimize(bool _minimize) noexcept override;
    void ToggleMaximize(bool _maximize) noexcept override;
    void ToggleFullscreen(bool _fullscreen) noexcept override;
    void BlinkTaskbarIcon() noexcept;
    void ToggleResizeability(bool _resizeable) noexcept override;
    void Resize(const glm::ivec2 &_size) noexcept override;
    void MoveTo(const glm::ivec2 &_position) noexcept override;
    void SetTitle(const std::wstring &_title) noexcept override;
    void SetIcon(const std::wstring &_path) noexcept override;
    void ToggleCursorVisibility(bool _show) noexcept override;
    void SetCursorIcon(const std::wstring &_path) noexcept override;
    void MoveCursorTo(glm::ivec2 _position) noexcept override;
    void ToggleCursorLock(bool _lock) noexcept override;
    void ToggleCursorClipping(bool _clip) noexcept override;
    const glm::uvec2 GetRenderTargetSize() const noexcept override;
};

class Win32WindowSystem final : public core::WindowSystem {
    friend class Win32Window;

   public:
    Win32WindowSystem() = default;
    ~Win32WindowSystem() override = default;

   private:
    static LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) noexcept;
};

}  // namespace Rake::platform::Win32

#endif
