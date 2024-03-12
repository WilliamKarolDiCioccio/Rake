#include "pch.hpp"

#ifdef PLATFORM_WINDOWS

#include "platform/win32/win32_window_system.hpp"

namespace Rake::platform::Win32 {

LRESULT CALLBACK
Win32WindowSystem::WndProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) noexcept {
    auto &windowName = GetWindowNameByNativeHandle(hWnd);
    auto &window = GetWindowHandleByName(windowName);
    auto &windowState = window->GetState();

    if (!window) return DefWindowProc(hWnd, uMsg, wParam, lParam);

    switch (uMsg) {
        case WM_CLOSE: {
            Get()->DestroyWindow(windowName);
        } break;
        case WM_ACTIVATE: {
            window->ToggleCursorVisibility(windowState.isCursorVisible);
            window->ToggleCursorLock(windowState.isCursorLocked);
            window->ToggleCursorClipping(windowState.isCursorClipped);
        } break;
        case WM_SIZE: {
            switch (wParam) {
                case SIZE_MINIMIZED: {
                    window->ToggleMinimize(true);
                } break;
                case SIZE_MAXIMIZED: {
                    window->ToggleMaximize(true);
                } break;
                case SIZE_RESTORED: {
                    window->ToggleMinimize(false);
                    window->ToggleMaximize(false);
                } break;
            }
        } break;
        case WM_GETMINMAXINFO: {
            LPMINMAXINFO minMaxInfo = (LPMINMAXINFO)lParam;
            minMaxInfo->ptMinTrackSize.x = 1280;
            minMaxInfo->ptMinTrackSize.y = 720;
        } break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Win32Window::Win32Window() {
    WNDCLASSEX extendedWindow = {};

    if (!GetClassInfoEx(GetModuleHandle(NULL), L"RkDefaultWindowClass", &extendedWindow)) {
        extendedWindow.cbSize = sizeof(WNDCLASSEX);
        extendedWindow.style = CS_HREDRAW | CS_VREDRAW;
        extendedWindow.lpfnWndProc = &Win32WindowSystem::WndProc;
        extendedWindow.hInstance = GetModuleHandle(NULL);
        extendedWindow.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        extendedWindow.hCursor = LoadCursor(NULL, IDC_ARROW);
        extendedWindow.hbrBackground = (HBRUSH)(NULL);
        extendedWindow.lpszMenuName = NULL;
        extendedWindow.lpszClassName = L"RkDefaultWindowClass";
        extendedWindow.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

        if (!RegisterClassEx(&extendedWindow)) throw std::runtime_error("Failed to register Win32 window class");
    }

    m_handle = CreateWindowExW(
        NULL,
        L"RkDefaultWindowClass",
        m_data.title.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        m_data.size.x,
        m_data.size.y,
        NULL,
        NULL,
        GetModuleHandle(NULL),
        NULL);

    if (!m_handle) throw std::runtime_error("Failed to create Win32 window");

    auto handle = reinterpret_cast<HWND>(m_handle);

    ::AdjustWindowRectEx(&m_styleProps.rect, WS_OVERLAPPEDWINDOW, FALSE, NULL);
    ::GetWindowRect(handle, &m_styleProps.rect);

    m_styleProps.style = GetWindowLong(handle, GWL_STYLE);
    m_styleProps.extendedStyle = GetWindowLong(handle, GWL_EXSTYLE);
    m_styleProps.scalingFactor = ::GetDpiForWindow(handle) / 96;

    SetWindowLong(handle, GWLP_USERDATA, reinterpret_cast<LONG>(this));

    ::SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    ::ShowWindow(handle, SW_HIDE);
}

Win32Window::~Win32Window() {
    ::DestroyWindow(reinterpret_cast<HWND>(m_handle));

    m_handle = nullptr;
    delete (m_handle);
}

void Win32Window::Update() noexcept {
    MSG msg = {};

    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Win32Window::ToggleVisibility(bool _show) noexcept {
    ::ShowWindow(reinterpret_cast<HWND>(m_handle), _show ? SW_SHOW : SW_HIDE);

    m_state.isVisible = _show;
}

void Win32Window::DisableWindowCapture(bool _hide) noexcept {
    ::SetWindowDisplayAffinity(reinterpret_cast<HWND>(m_handle), _hide ? WDA_MONITOR : WDA_NONE);

    m_state.isWindowCaptureDisabled = _hide;
}

void Win32Window::RequestFocus() noexcept { ::SetFocus(reinterpret_cast<HWND>(m_handle)); }

void Win32Window::ToggleMinimize(bool _minimize) noexcept {
    if (_minimize) {
        ::ShowWindow(reinterpret_cast<HWND>(m_handle), SW_SHOWMINIMIZED);
    } else {
        ::ShowWindow(reinterpret_cast<HWND>(m_handle), SW_SHOWDEFAULT);

        Resize(m_data.size);
    }

    m_state.isMinimized = _minimize;
}

void Win32Window::ToggleMaximize(bool _maximize) noexcept {
    if (_maximize) {
        ::ShowWindow(reinterpret_cast<HWND>(m_handle), SW_SHOWMAXIMIZED);
    } else {
        ::ShowWindow(reinterpret_cast<HWND>(m_handle), SW_SHOWDEFAULT);

        Resize(m_data.size);
    }

    m_state.isMaximized = _maximize;
}

void Win32Window::ToggleFullscreen(bool _fullscreen) noexcept {
    auto handle = reinterpret_cast<HWND>(m_handle);

    if (_fullscreen) {
        m_styleProps.style = GetWindowLong(handle, GWL_STYLE);
        m_styleProps.extendedStyle = GetWindowLong(handle, GWL_EXSTYLE);

        ::GetWindowRect(handle, &m_styleProps.rect);

        constexpr LONG mask = ~(WS_CAPTION | WS_THICKFRAME);

        SetWindowLong(handle, GWL_STYLE, m_styleProps.style & mask);

        constexpr LONG exMask = ~(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);

        SetWindowLong(handle, GWL_EXSTYLE, m_styleProps.extendedStyle & exMask);

        int fullClientSizeX = GetSystemMetrics(SM_CXSCREEN);
        int fullClientSizeY = GetSystemMetrics(SM_CYSCREEN);

        MoveTo({0, 0});
        Resize({fullClientSizeX, fullClientSizeY});

        ::ShowWindow(handle, SW_SHOW);
        ::SetWindowPos(handle, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    } else {
        SetWindowLong(handle, GWL_STYLE, m_styleProps.style);
        SetWindowLong(handle, GWL_EXSTYLE, m_styleProps.extendedStyle);

        ::ShowWindow(handle, SW_SHOW);
        ::SetWindowPos(handle, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

        ToggleMinimize(m_state.isMinimized);
        ToggleMaximize(m_state.isMaximized);
    }
}

void Win32Window::BlinkTaskbarIcon() noexcept {
    FLASHWINFO flashWndInfo = {
        .cbSize = sizeof(FLASHWINFO),
        .hwnd = reinterpret_cast<HWND>(m_handle),
        .dwFlags = FLASHW_TRAY,
        .uCount = 3,
        .dwTimeout = 1500,
    };

    ::FlashWindowEx(&flashWndInfo);
}

void Win32Window::ToggleResizeability(bool _resizeable) noexcept {
    if (_resizeable) {
        SetWindowLong(reinterpret_cast<HWND>(m_handle), GWL_EXSTYLE, m_styleProps.extendedStyle);
    } else {
        SetWindowLong(reinterpret_cast<HWND>(m_handle), GWL_EXSTYLE, m_styleProps.extendedStyle ^ WS_SIZEBOX);
    }

    m_state.isResizeable = _resizeable;
}

void Win32Window::Resize(const glm::ivec2 &_size) noexcept {
    if (m_state.isFullscreen) ToggleFullscreen(false);

    ::SetWindowPos(reinterpret_cast<HWND>(m_handle), HWND_TOP, NULL, NULL, _size.x, _size.y, SWP_NOMOVE);

    ::GetWindowRect(reinterpret_cast<HWND>(m_handle), &m_styleProps.rect);

    m_data.size = _size;
}

void Win32Window::MoveTo(const glm::ivec2 &_position) noexcept {
    ::SetWindowPos(reinterpret_cast<HWND>(m_handle), HWND_TOP, _position.x, _position.y, NULL, NULL, SWP_NOSIZE);

    m_data.position = _position;
}

void Win32Window::SetTitle(const std::wstring &_title) noexcept {
    ::SetWindowTextW(static_cast<HWND>(m_handle), (LPCWSTR)_title.c_str());

    m_data.title = _title;
}

void Win32Window::SetIcon(const std::wstring &_path) noexcept {
    HICON hIcon = (HICON)LoadImage(NULL, (LPCWSTR)_path.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

    // TODO: Implementing this need manifest tool

    m_data.iconRes = _path;
}

void Win32Window::ToggleCursorVisibility(bool _show) noexcept {
    ::ShowCursor(_show);

    m_state.isCursorVisible = _show;
}

void Win32Window::SetCursorIcon(const std::wstring &_path) noexcept {
    HCURSOR hCursor = (HCURSOR)LoadImage(NULL, (LPWSTR)_path.c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);

    // TODO: Implementing this need manifest tool

    m_data.cursorRes = _path;
}

void Win32Window::MoveCursorTo(glm::ivec2 _position) noexcept { ::SetCursorPos(_position.x, _position.y); }

void Win32Window::ToggleCursorLock(bool _lock) noexcept {
    if (_lock) {
        RECT clipRect;

        clipRect.left = 0;
        clipRect.top = 0;
        clipRect.right = 0;
        clipRect.bottom = 0;

        ::ClipCursor(&clipRect);
    } else {
        ToggleCursorClipping(m_state.isCursorClipped);
    }

    m_state.isCursorLocked = _lock;
}

void Win32Window::ToggleCursorClipping(bool _clip) noexcept {
    if (m_state.isCursorLocked) return;

    HWND handle = reinterpret_cast<HWND>(m_handle);

    if (_clip) {
        RECT rect;

        ::GetClientRect(handle, &rect);

        POINT topLeft;
        POINT bottomRight;

        topLeft.x = rect.left;
        topLeft.y = rect.top;
        bottomRight.x = rect.right;
        bottomRight.y = rect.bottom;

        ::ClientToScreen(handle, &topLeft);
        ::ClientToScreen(handle, &bottomRight);

        RECT clipRect;

        clipRect.left = topLeft.x;
        clipRect.top = topLeft.y;
        clipRect.right = bottomRight.x;
        clipRect.bottom = bottomRight.y;

        ::ClipCursor(&clipRect);

    } else {
        ::ClipCursor(NULL);
    }

    m_state.isCursorClipped = _clip;
}

const glm::uvec2 Win32Window::GetRenderTargetSize() const noexcept {
    RECT rect;

    ::GetClientRect(reinterpret_cast<HWND>(m_handle), &rect);

    auto width = rect.right - rect.left;
    auto height = rect.bottom - rect.top;

    return glm::uvec2(static_cast<uint32_t>(width), static_cast<uint32_t>(height));
}

}  // namespace Rake::platform::Win32

#endif
