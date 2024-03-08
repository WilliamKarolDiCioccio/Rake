#include "pch.hpp"

#ifdef PLATFORM_WINDOWS

#include "platform/win32/win32_window_system.hpp"

#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_win32.cpp>

namespace Rake::platform::Win32 {

void Win32WindowSystem::Update() noexcept {
    MSG msg;

    if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
        ::TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK
Win32WindowSystem::WndProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) noexcept {
    ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

    switch (uMsg) {
        case WM_CLOSE: {
            Win32WindowSystem::UnregisterWindow(Win32WindowSystem::m_nativeWindowRegistry[hWnd]);

            PostQuitMessage(NULL);
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
    m_imGuiContext = ImGui::CreateContext();

    ImGui::SetCurrentContext(m_imGuiContext);

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

        RK_ASSERT(RegisterClassEx(&extendedWindow));
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

    RK_ASSERT(m_handle);

    auto handle = reinterpret_cast<HWND>(m_handle);

    ImGui_ImplWin32_Init(handle);

    ::AdjustWindowRectEx(&m_styleProps.rect, WS_OVERLAPPEDWINDOW, FALSE, NULL);
    ::GetWindowRect(handle, &m_styleProps.rect);

    m_styleProps.style = GetWindowLong(handle, GWL_STYLE);
    m_styleProps.extendedStyle = GetWindowLong(handle, GWL_EXSTYLE);
    m_styleProps.scalingFactor = ::GetDpiForWindow(handle) / 96;

    SetWindowLong(handle, GWLP_USERDATA, reinterpret_cast<LONG>(this));

    ::SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    ImGui_ImplWin32_EnableDpiAwareness();

    ::ShowWindow(handle, SW_HIDE);
}

Win32Window::~Win32Window() {
    ImGui::SetCurrentContext(m_imGuiContext);

    ImGui_ImplWin32_Shutdown();

    ImGui::DestroyContext(m_imGuiContext);

    ::DestroyWindow(reinterpret_cast<HWND>(m_handle));

    m_handle = nullptr;
    delete (m_handle);
}

void Win32Window::BeginContext() noexcept {
    ImGui::SetCurrentContext(m_imGuiContext);

    auto extent = GetFramebufferSize();

    ImGuiIO &io = ImGui::GetIO();

    io.DisplaySize = ImVec2(static_cast<float>(extent.x), static_cast<float>(extent.y));

    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();
}

void Win32Window::EndContext() noexcept {
    ImGui::SetCurrentContext(m_imGuiContext);

    ImGui::Render();
}

void Win32Window::Show(bool _show) noexcept {
    if (m_state.isShowing != _show) {
        ::ShowWindow(reinterpret_cast<HWND>(m_handle), _show ? SW_SHOW : SW_HIDE);

        m_state.isShowing = _show;
    }
}

void Win32Window::HideFromCapture(bool _hide) noexcept {
    ::SetWindowDisplayAffinity(reinterpret_cast<HWND>(m_handle), _hide ? WDA_MONITOR : WDA_NONE);

    m_state.isHiddenFromCapture = _hide;
}

void Win32Window::SetFocus() noexcept {
    if (reinterpret_cast<HWND>(m_handle) != GetActiveWindow()) {
        ::SetFocus(reinterpret_cast<HWND>(m_handle));
    }
}

void Win32Window::Maximize(bool _maximize) noexcept {
    if (m_state.isMaximized != _maximize) {
        ::ShowWindow(reinterpret_cast<HWND>(m_handle), _maximize ? SW_SHOWMAXIMIZED : SW_SHOWMINIMIZED);

        m_state.isMaximized = _maximize;
    }
}

void Win32Window::Fullscreen(bool _fullscreen) noexcept {
    if (m_state.isFullscreen != _fullscreen) {
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

            SetPosition({0, 0});
            SetSize({fullClientSizeX, fullClientSizeY});

            ::ShowWindow(handle, SW_SHOW);

            ::SetWindowPos(handle, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        } else {
            SetWindowLong(handle, GWL_STYLE, m_styleProps.style);
            SetWindowLong(handle, GWL_EXSTYLE, m_styleProps.extendedStyle);

            if (m_state.isMaximized) {
                Maximize(true);
            }

            ::ShowWindow(handle, SW_SHOW);

            ::SetWindowPos(handle, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        }

        m_state.isFullscreen = _fullscreen;
    }
}

void Win32Window::Highlight() noexcept {
    FLASHWINFO flashWndInfo = {
        .cbSize = sizeof(FLASHWINFO),
        .hwnd = reinterpret_cast<HWND>(m_handle),
        .dwFlags = FLASHW_TRAY,
        .uCount = 3,
        .dwTimeout = 1500,
    };

    ::FlashWindowEx(&flashWndInfo);
}

void Win32Window::SetResizeable(bool _resizeable) noexcept {
    if (m_state.isResizeable != _resizeable && !m_state.isMaximized) {
        if (_resizeable) {
            SetWindowLong(reinterpret_cast<HWND>(m_handle), GWL_EXSTYLE, m_styleProps.extendedStyle);
        } else {
            SetWindowLong(reinterpret_cast<HWND>(m_handle), GWL_EXSTYLE, m_styleProps.extendedStyle ^ WS_SIZEBOX);
        }

        m_state.isResizeable = _resizeable;
    }
}

void Win32Window::SetSize(glm::ivec2 _size) noexcept {
    ::SetWindowPos(reinterpret_cast<HWND>(m_handle), HWND_TOP, NULL, NULL, _size.x, _size.y, SWP_NOMOVE);

    ::GetWindowRect(reinterpret_cast<HWND>(m_handle), &m_styleProps.rect);

    if (m_state.isFullscreen) Fullscreen(false);
}

void Win32Window::SetPosition(glm::ivec2 _position) noexcept {
    ::SetWindowPos(reinterpret_cast<HWND>(m_handle), HWND_TOP, _position.x, _position.y, NULL, NULL, SWP_NOSIZE);
}

void Win32Window::SetTitle(const std::wstring &_title) noexcept {
    ::SetWindowTextW(static_cast<HWND>(m_handle), (LPCWSTR)_title.c_str());
}

void Win32Window::SetIcon(const std::string &_path) noexcept {
    HICON hIcon = (HICON)LoadImage(NULL, (LPCWSTR)_path.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

    if (hIcon != NULL) {
        SendMessage(reinterpret_cast<HWND>(m_handle), WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
        SendMessage(reinterpret_cast<HWND>(m_handle), WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    }
}

void Win32Window::ShowCursor(bool _show) noexcept {
    ::ShowCursor(_show);

    m_state.isCursorShowing = _show;
}

void Win32Window::SetCursor(const std::string &_path) noexcept {
    HCURSOR hCursor = (HCURSOR)LoadImage(NULL, (LPWSTR)_path.c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);

    if (hCursor != NULL) {
        SetCursor(_path);
    }
}

void Win32Window::SetCursorPosition(glm::ivec2 _position) noexcept { ::SetCursorPos(_position.x, _position.y); }

void Win32Window::LockCursor(bool _lock) noexcept {
    if (!_lock) {
        m_state.isCursorLocked = false;

        ClipCursorInside(m_state.isCursorClipped);
    } else {
        m_state.isCursorLocked = true;

        RECT clipRect;

        clipRect.left = 0;
        clipRect.top = 0;
        clipRect.right = 0;
        clipRect.bottom = 0;

        ::ClipCursor(&clipRect);
    }
}

void Win32Window::ClipCursorInside(bool _clip) noexcept {
    if (m_state.isCursorLocked) return;

    HWND handle = reinterpret_cast<HWND>(m_handle);

    if (!_clip) {
        ::ClipCursor(NULL);
    } else {
        RECT rect;

        if (::GetClientRect(handle, &rect)) {
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
        }
    }

    m_state.isCursorClipped = _clip;
}

const glm::uvec2 Win32Window::GetFramebufferSize() const noexcept {
    RECT rect;

    ::GetClientRect(reinterpret_cast<HWND>(m_handle), &rect);

    auto width = rect.right - rect.left;
    auto height = rect.bottom - rect.top;

    return glm::uvec2(static_cast<uint32_t>(width), static_cast<uint32_t>(height));
}

}  // namespace Rake::platform::Win32

#endif
