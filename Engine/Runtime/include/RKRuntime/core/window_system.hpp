#pragma once

#include "RKRuntime/base.hpp"

#include <glm/vec2.hpp>

namespace Rake::core {

/**
 * @brief The Window class is an abstract class that represents a window in the windowing system.
 * 
 * @details
 * Like the WindowSystem class, the Window class is abstract. It is responsible for managing the window's state and data.
 * 
 * @note The Window class is not meant to be used directly. Instead, it is used by the WindowSystem class to manage the window's state and data.
 * @see WindowSystem
 */
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
    /**
	 * @brief Update the window at platform level.
	 * 
	 * @note This method is called by the WindowSystem class.
	 */
    virtual void Update() noexcept = 0;

   public:
    /**
     * @brief Toggle the visibility of the window. Saves to window state.
     * 
     * @param _visible Whether to make the window visible.
     */
    RK_API virtual void ToggleVisibility(bool _visible) noexcept = 0;

    /**
     * @brief Toggle the window capture. Saves to window state.
     * 
     * @param _disable Whether to disable the window capture.
	 */
    RK_API virtual void DisableWindowCapture(bool _disable) noexcept = 0;

    /**
     * @brief Request focus for the window.
     * 
     * This will bring the window to the front and give it focus.
     */
    RK_API virtual void RequestFocus() noexcept = 0;

    /**
     * @brief Toggle the minimization of the window. Saves to window state.
     * 
     * @param _minimize Whether to minimize the window.
     * @see ToggleMaximize
     */
    RK_API virtual void ToggleMinimize(bool _minimize) noexcept = 0;

    /**
     * @brief Toggle the maximization of the window. Saves to window state.
     * 
     * @param _maximize Whether to maximize the window.
     * @see ToggleMinimize
	 */
    RK_API virtual void ToggleMaximize(bool _maximize) noexcept = 0;

    /**
     * @brief Toggle the fullscreen mode of the window. Saves to window state.
     * 
     * @param _fullscreen Whether to make the window fullscreen.
     */
    RK_API virtual void ToggleFullscreen(bool _fullscreen) noexcept = 0;

    /**
     * @brief Makes the program icon blinking of the taskbar.
     * 
     * @note Works only on Windows.
	 */
    RK_API virtual void BlinkTaskbarIcon() noexcept = 0;

    /**
     * @brief Toggle the resizeability of the window. Saves to window state.
     * 
     * @param _resizeable Whether to make the window resizeable.
     * @see Resize
     */
    RK_API virtual void ToggleResizeability(bool _resizeable) noexcept = 0;

    /**
     * @brief Resize the window. Saves to the window data.
     * 
     * @param _size The new size of the window.
     * @see ToggleResizeability
     */
    RK_API virtual void Resize(const glm::ivec2 &_size) noexcept = 0;

    /**
     * @brief Move the window to a specific position. Saves to window data.
     * 
     * @param _position The new position of the window.
	 */
    RK_API virtual void MoveTo(const glm::ivec2 &_position) noexcept = 0;

    /**
     * @brief Set the title of the window. Saves to window data.
     * 
     * @param _title The new title of the window.
     */
    RK_API virtual void SetTitle(const std::wstring &_title) noexcept = 0;

    /**
     * @brief Set the icon of the window. Saves to window data.
     * 
     * @param _path The path to the icon.
     * @note The icon should be a square image.
	 */
    RK_API virtual void SetIcon(const std::wstring &_path) noexcept = 0;

    /**
     * @brief Toggle the visibility of the cursor. Saves to window state.
     * 
     * @param _show Whether to show the cursor.
     */
    RK_API virtual void ToggleCursorVisibility(bool _show) noexcept = 0;

    /**
     * @brief Set the cursor icon. Saves to the window data.
     * 
     * @param _path The path to the cursor icon.
	 */
    RK_API virtual void SetCursorIcon(const std::wstring &_path) noexcept = 0;

    /**
     * @brief Move the cursor to a specific position.
     * 
     * @param _position The position to move the cursor to.
     */
    RK_API virtual void MoveCursorTo(glm::ivec2 _position) noexcept = 0;

    /**
     * @brief Toggle the locking of the cursor to the window. Saves to window state.
     * 
     * @param _lock Whether to lock the cursor to the window.
	 */
    RK_API virtual void ToggleCursorLock(bool _lock) noexcept = 0;

    /**
     * @brief Toggle the clipping of the cursor to the window. Saves to window state.
     * 
     * @param _clip Whether to clip the cursor to the window.
     */
    RK_API virtual void ToggleCursorClipping(bool _clip) noexcept = 0;

    /**
     * @brief Get the size of the window framebuffer.
     * 
     * @return The size of the window framebuffer.
	 */
    RK_API virtual const glm::uvec2 GetRenderTargetSize() const noexcept = 0;

   public:
    /**
     * @brief Get the native handle of the window.
     * 
     * @return The native handle of the window as void pointer, which can be casted to the appropriate type.
     */
    NODISCARD inline void *GetNativeHandle() const noexcept { return m_handle; }

    /**
	 * @brief Get the data of the window.
	 * 
	 * @return The data of the window.
     * @see Data
	 */
    NODISCARD inline const Data &GetData() const noexcept { return m_data; }

    /**
     * @brief Get the state of the window.
     * 
     * @return The state of the window.
     * @see State
     */
    NODISCARD inline const State &GetState() const noexcept { return m_state; }
};

/**
 * @brief The WindowSystem class is an abstract class that represents a windowing system.
 * 
 * @details
 * The WindowSystem class is responsible for creating, managing, and destroying windows. It keeps track of all windows and their native handles.
 * 
 * @note This class is a singleton instantiated by the Application class method and should be accessed through the Get() method.
 * @see Application
 * @see Window
 */
class WindowSystem : public NonCopyable, NonMovable {
   protected:
    static inline WindowSystem *m_instance = nullptr;

    std::vector<std::string> m_windowsToDestroy;
    std::unordered_map<std::string, std::shared_ptr<Window>> m_windowRegistry;
    std::unordered_map<void *, std::string> m_nativeWindowRegistry;

   public:
    WindowSystem();
    virtual ~WindowSystem();

   public:
    /**
     * @brief Update the window system at platform level.
     * 
     * @note This method is called by the Application class.
     * @see Application
     */
    void Update() noexcept;

    /**
     * @brief Check wether all windows are closed and act accordingly.
     * 
     * @note This method is called by the Application class.
     * @see Application
     */
    bool ShouldClose() noexcept;

   public:
    RK_API virtual const std::shared_ptr<Window> &CreateWindow(const std::string &_name) noexcept;
    RK_API virtual void DestroyWindow(const std::string &_name) noexcept;

   private:
    /**
     * @brief Load the window state from WindowStates.json file.
     * 
     * @param _name The name of the window state to load.
     * @see SaveWindowState
     */
    RK_API void LoadWindowState(const std::string &_name) noexcept;

    /**
     * @brief Save the window state to WindowStates.json file.
     * 
     * @param _name The name of the window state to save.
     * @see LoadWindowState
	 */
    RK_API void SaveWindowState(const std::string &_name) noexcept;

   public:
    /**
     * @brief Get the singleton instance of the WindowSystem class.
     * 
     * @return The WindowSystem instance.
     */
    RK_API NODISCARD static WindowSystem *Get() noexcept;

    /**
	 * @brief Get the window handle by name.
	 * 
	 * @param _name The name of the window.
	 * @return The window handle as a shared pointer.
	 */
    RK_API NODISCARD static const std::shared_ptr<Window> GetWindowHandleByName(const std::string &_name) noexcept;

    /**
     * @brief Get the window name by native handle.
     * 
     * @param _nativeHandle The native handle of the window.
     * @return The name of the window.
	 */
    RK_API NODISCARD static const std::string GetWindowNameByNativeHandle(void *_nativeHandle) noexcept;

    /**
     * @brief Get the window registry.
     * 
     * @return The window registry.
     * @note The window registry is a map of window names and their corresponding window handles.
	 */
    RK_API NODISCARD static const std::unordered_map<std::string, std::shared_ptr<Window>> &
    GetWindowRegistry() noexcept;

    /**
     * @brief Get the native window registry.
     * 
     * @return The native window registry.
     * @note The native window registry is a map of native window handles and their corresponding window names.
     */
    RK_API NODISCARD static const std::unordered_map<void *, std::string> &GetNativeWindowRegistry() noexcept;

    /**
     * @brief Create a native window system.
     * 
     * @return The native window system as a unique pointer.
     * @note This method is called by the Application class.
     * @see Application
     */
    static std::unique_ptr<WindowSystem> CreateNative() noexcept;
};

}  // namespace Rake::core
