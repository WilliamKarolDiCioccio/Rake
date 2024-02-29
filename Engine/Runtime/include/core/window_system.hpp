#pragma once

RK_DISABLE_WARNINGS
#include <imgui.h>
#include <glm/vec2.hpp>
RK_RESTORE_WARNINGS

#include "base.hpp"

namespace Rake::core {

class Window {
   protected:
    void *m_handle = nullptr;
    ImGuiContext *m_imGuiContext = nullptr;

    struct WindowState {
        bool isShowing;
        bool isMaximized;
        bool isFullscreen;
        bool isResizeable;
        bool isCursorShowing;
        bool isCursorLocked;
        bool isCursorClipped;
        bool isHiddenFromCapture;
    };

    WindowState m_state = {};

    struct WindowData {
        std::wstring title;
        std::string iconRes;
        std::string cursorRes;
        glm::ivec2 pos;
        glm::ivec2 size;
    };

    WindowData m_data = {};

   public:
    Window() = default;
    virtual ~Window() = default;

   public:
    virtual void BeginContext() noexcept = 0;
    virtual void EndContext() noexcept = 0;

   public:
    RK_API virtual void Show(bool _show) noexcept = 0;
    RK_API virtual void HideFromCapture(bool _hide) noexcept = 0;
    RK_API virtual void SetFocus() noexcept = 0;
    RK_API virtual void Maximize(bool _maximize) noexcept = 0;
    RK_API virtual void Fullscreen(bool _fullscreen) noexcept = 0;
    RK_API virtual void Highlight() noexcept = 0;
    RK_API virtual void SetResizeable(bool _resizeable) noexcept = 0;
    RK_API virtual void SetSize(glm::ivec2 _size) noexcept = 0;
    RK_API virtual void SetPosition(glm::ivec2 _pos) noexcept = 0;
    RK_API virtual void SetTitle(const std::wstring &_title) noexcept = 0;
    RK_API virtual void SetIcon(const std::string &_path) noexcept = 0;
    RK_API virtual void ShowCursor(bool _show) noexcept = 0;
    RK_API virtual void SetCursor(const std::string &_path) noexcept = 0;
    RK_API virtual void SetCursorPosition(glm::ivec2 _position) noexcept = 0;
    RK_API virtual void LockCursor(bool _lock) noexcept = 0;
    RK_API virtual void ClipCursorInside(bool _clip) noexcept = 0;
    RK_API virtual const glm::uvec2 GetFramebufferSize() const noexcept = 0;

   public:
    NODISCARD inline void *GetNativeHandle() const noexcept { return m_handle; }

    NODISCARD inline ImGuiContext *GetImGuiContext() noexcept { return m_imGuiContext; }

    NODISCARD inline const WindowData &GetData() const noexcept { return m_data; }

    NODISCARD inline const WindowState &GetState() const noexcept { return m_state; }
};

class WindowSystem : public NonCopyable, NonMovable {
   private:
    static inline WindowSystem *m_instance = nullptr;

   protected:
    static inline std::unordered_map<std::string, std::unique_ptr<Window>> m_windowRegistry = {};
    static inline std::unordered_map<void *, std::string> m_nativeWindowRegistry = {};

   public:
    WindowSystem();
    virtual ~WindowSystem();

   public:
    virtual void Update() noexcept = 0;

   public:
    RK_API static void LoadState(const std::string &_name) noexcept;
    RK_API static void SaveState(const std::string &_name) noexcept;
    RK_API static Window *RegisterWindow(const std::string &_name) noexcept;
    RK_API static void UnregisterWindow(const std::string &_name) noexcept;

   public:
    RK_API NODISCARD static const WindowSystem *Get() noexcept;

    RK_API NODISCARD static Window *GetWindowByTitle(const std::string &_title) noexcept;

    RK_API NODISCARD static const std::unordered_map<void *, std::string> &GetNativeWindowRegistry() noexcept;

    RK_API NODISCARD static const std::unordered_map<std::string, std::unique_ptr<Window>> &
    GetWindowRegistry() noexcept;

    static std::unique_ptr<WindowSystem> CreateNative() noexcept;
};

}  // namespace Rake::core
