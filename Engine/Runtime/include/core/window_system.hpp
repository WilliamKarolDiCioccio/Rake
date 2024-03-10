#pragma once

#include "base.hpp"

#include <glm/vec2.hpp>

namespace Rake::core {

class Window {
   protected:
    void *m_handle = nullptr;

    struct State {
        bool isVisible;
        bool isMinimized;
        bool isMaximized;
        bool isFullscreen;
        bool isResizeable;
        bool isCursorVisible;
        bool isCursorLocked;
        bool isCursorClipped;
        bool isWindowCaptureDisabled;

        State()
            : isVisible(true),
              isMaximized(false),
              isMinimized(false),
              isFullscreen(false),
              isResizeable(true),
              isCursorVisible(true),
              isCursorLocked(false),
              isCursorClipped(false),
              isWindowCaptureDisabled(false) {}
    };

    State m_state;

    struct Data {
        std::wstring title;
        std::wstring iconRes;
        std::wstring cursorRes;
        glm::ivec2 size;
        glm::ivec2 position;

        Data() : title(L""), iconRes(L""), cursorRes(L""), size({1280, 720}), position({0, 0}) {}
    };

    Data m_data;

   public:
    Window() = default;
    virtual ~Window() = default;

   public:
    virtual void Update() noexcept = 0;

   public:
    RK_API virtual void ToggleVisibility(bool _visible) noexcept = 0;
    RK_API virtual void DisableWindowCapture(bool _disable) noexcept = 0;
    RK_API virtual void RequestFocus() noexcept = 0;
    RK_API virtual void ToggleMinimize(bool _minimize) noexcept = 0;
    RK_API virtual void ToggleMaximize(bool _maximize) noexcept = 0;
    RK_API virtual void ToggleFullscreen(bool _fullscreen) noexcept = 0;
    RK_API virtual void BlinkTaskbarIcon() noexcept = 0;
    RK_API virtual void ToggleResizeability(bool _resizeable) noexcept = 0;
    RK_API virtual void Resize(const glm::ivec2 &_size) noexcept = 0;
    RK_API virtual void MoveTo(const glm::ivec2 &_position) noexcept = 0;
    RK_API virtual void SetTitle(const std::wstring &_title) noexcept = 0;
    RK_API virtual void SetIcon(const std::wstring &_path) noexcept = 0;
    RK_API virtual void ToggleCursorVisibility(bool _show) noexcept = 0;
    RK_API virtual void SetCursorIcon(const std::wstring &_path) noexcept = 0;
    RK_API virtual void MoveCursorTo(glm::ivec2 _position) noexcept = 0;
    RK_API virtual void ToggleCursorLock(bool _lock) noexcept = 0;
    RK_API virtual void ToggleCursorClipping(bool _clip) noexcept = 0;
    RK_API virtual const glm::uvec2 GetRenderTargetSize() const noexcept = 0;

   public:
    NODISCARD inline void *GetNativeHandle() const noexcept { return m_handle; }

    NODISCARD inline const Data &GetData() const noexcept { return m_data; }

    NODISCARD inline const State &GetState() const noexcept { return m_state; }
};

class WindowSystem : public NonCopyable, NonMovable {
   private:
    static inline WindowSystem *m_instance = nullptr;

   protected:
    std::unordered_map<std::string, std::shared_ptr<Window>> m_windowRegistry;
    std::unordered_map<void *, std::string> m_nativeWindowRegistry;

   public:
    WindowSystem();
    virtual ~WindowSystem();

   public:
    void Update() noexcept;

   public:
    RK_API void LoadWindowState(const std::string &_name) noexcept;
    RK_API void SaveWindowState(const std::string &_name) noexcept;
    RK_API virtual const std::shared_ptr<Window> &CreateWindow(const std::string &_name) noexcept;
    RK_API virtual void DestroyWindow(const std::string &_name) noexcept;

   public:
    RK_API NODISCARD static WindowSystem *Get() noexcept;

    RK_API NODISCARD static const std::shared_ptr<Window> GetWindowHandleByName(const std::string &_name) noexcept;

    RK_API NODISCARD static const std::string GetWindowNameByNativeHandle(void *_nativeHandle) noexcept;

    RK_API NODISCARD static const std::unordered_map<std::string, std::shared_ptr<Window>> &
    GetWindowRegistry() noexcept;

    RK_API NODISCARD static const std::unordered_map<void *, std::string> &GetNativeWindowRegistry() noexcept;

    static std::unique_ptr<WindowSystem> CreateNative() noexcept;
};

}  // namespace Rake::core
