#pragma once

#include "base.hpp"

#ifdef PLATFORM_WINDOWS

#include "core/window_system.hpp"

#include "win32_common.hpp"

namespace Rake::platform::Win32 {

class Win32Window final : public core::Window {
   private:
    struct WindowStyleProps {
        RECT rect;
        LONG style;
        LONG extendedStyle;
        UINT scalingFactor;
        HICON icon;
        HCURSOR cursor;
    };

    WindowStyleProps m_styleProps = {};

   public:
    Win32Window();
    ~Win32Window();

   public:
    void BeginContext() noexcept override;
    void EndContext() noexcept override;
    void Show(bool _show) noexcept override;
    void HideFromCapture(bool _hide) noexcept override;
    void SetFocus() noexcept override;
    void Maximize(bool _maximize) noexcept override;
    void Fullscreen(bool _fullscreen) noexcept override;
    void Highlight() noexcept override;
    void SetResizeable(bool _resizeable) noexcept override;
    void SetSize(glm::ivec2 _size) noexcept override;
    void SetPosition(glm::ivec2 _position) noexcept override;
    void SetTitle(const std::wstring &_title) noexcept override;
    void SetIcon(const std::string &_path) noexcept override;
    void ShowCursor(bool _show) noexcept override;
    void SetCursor(const std::string &_path) noexcept override;
    void SetCursorPosition(glm::ivec2 _position) noexcept override;
    void LockCursor(bool _lock) noexcept override;
    void ClipCursorInside(bool _clip) noexcept override;
    const glm::uvec2 GetFramebufferSize() const noexcept override;
};

class Win32WindowSystem final : public core::WindowSystem {
    friend class Win32Window;

   public:
    Win32WindowSystem() = default;
    ~Win32WindowSystem() override = default;

   public:
    void Update() noexcept override;

   private:
    static LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) noexcept;
};

}  // namespace Rake::platform::Win32

#endif
