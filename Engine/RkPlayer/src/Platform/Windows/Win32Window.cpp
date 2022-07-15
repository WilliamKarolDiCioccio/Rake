#include "src/RkPch.h"

#if defined(PLATFORM_WINDOWS) == 1

#include "Platform/Windows/Win32Window.hpp"

namespace Rake::Platform
{

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (uMsg)
    {
    case WM_DPICHANGED: {
    }
    case WM_SIZE: {
    }
    case WM_SIZING: {
    }
    case WM_GETMINMAXINFO: {
        // LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
        // lpMMI->ptMinTrackSize.x = 300;
        // lpMMI->ptMinTrackSize.y = 300;
    }
    case WM_CLOSE: {
        ::PostQuitMessage(NULL);
    }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

Win32Window::Win32Window()
{
    WNDCLASSEX extendedWindow = {
        .cbSize = sizeof(WNDCLASSEX),
        .style = CS_HREDRAW | CS_VREDRAW,
        .lpfnWndProc = &WndProc,
        .hInstance = GetModuleHandle(NULL),
        .hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
        .lpszMenuName = NULL,
        .lpszClassName = L"RakeWindow",
    };

    if (RegisterClassEx(&extendedWindow) == NULL)
        throw RkException("Unable to register window class", NULL, __FILE__, __LINE__);

    m_handle = CreateWindowEx(NULL, L"RakeWindow", DEFAULT_WINDOW_TITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, NULL, NULL, NULL, NULL);

    RK_ASSERT(m_handle);

    RECT rect = {0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT};
    ::AdjustWindowRectEx(&m_savedProps.rect, WS_OVERLAPPEDWINDOW, FALSE, NULL);

    m_savedProps.rect = std::move(rect);
    m_savedProps.deviceContext = ::GetDC((HWND)m_handle);
    m_savedProps.scalingFactor = this->GetDPIScale();

    SetWindowLong((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);

    ::SetWindowDisplayAffinity((HWND)m_handle, WDA_NONE);
}

Win32Window::~Win32Window()
{
    ::ReleaseDC((HWND)m_handle, m_savedProps.deviceContext);
    ::DestroyWindow((HWND)m_handle);

    delete (m_handle);
}

void Win32Window::Refresh()
{
}

void Win32Window::Show(B8 _shouldShow)
{
    if (m_savedState.isShowing != _shouldShow)
    {
        m_savedState.isShowing = _shouldShow;

        if (_shouldShow)
            ::ShowWindow((HWND)m_handle, SW_SHOW);
        else
            ::ShowWindow((HWND)m_handle, SW_HIDE);
    }
    else
        return;
}

void Win32Window::Maximize(B8 _maximize)
{
    if (m_savedState.isMaximized != _maximize)
    {
        m_savedState.isMaximized = _maximize;

        if (_maximize)
            ::ShowWindow((HWND)m_handle, SW_SHOWMAXIMIZED);
        else
            ::ShowWindow((HWND)m_handle, SW_SHOWMINIMIZED);
    }
}

void Win32Window::Fullscreen(B8 _fullscreen)
{
    if (m_savedState.isFullscreen != _fullscreen)
    {
        if (!m_savedState.isFullscreen)
        {
            m_savedProps.style = GetWindowLong((HWND)m_handle, GWL_STYLE);
            m_savedProps.extendedStyle = GetWindowLong((HWND)m_handle, GWL_EXSTYLE);

            ::GetWindowRect((HWND)m_handle, &m_savedProps.rect);
        }

        m_savedState.isFullscreen = _fullscreen;

        if (_fullscreen)
        {
            SetWindowLong((HWND)m_handle, GWL_STYLE, m_savedProps.style & ~(WS_CAPTION | WS_THICKFRAME));
            SetWindowLong((HWND)m_handle, GWL_EXSTYLE, m_savedProps.extendedStyle & ~(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));

            if (m_savedState.isCursorClipped)
                ConfineCursor(true);
        }
        else
        {
            SetWindowLong((HWND)m_handle, GWL_STYLE, m_savedProps.style);
            SetWindowLong((HWND)m_handle, GWL_EXSTYLE, m_savedProps.extendedStyle);

            if (m_savedState.isMaximized)
                Maximize(true);

            if (m_savedState.isCursorClipped)
                ConfineCursor(true);
        }
    }
    else
        return;
}

void Win32Window::SetSize(long _newWidth, long _newHeight)
{
    ::SetWindowPos((HWND)m_handle, HWND_TOPMOST, NULL, NULL, _newWidth, _newHeight, SWP_NOMOVE);
}

void Win32Window::SetPos(B32 _newX, B32 _newY)
{
    ::SetWindowPos((HWND)m_handle, HWND_TOPMOST, _newX, _newY, NULL, NULL, SWP_NOSIZE);
}

void Win32Window::SetIcon(const char *_iconPath)
{
}

void Win32Window::SetTitle(const wchar_t *_title)
{
    ::SetWindowTextW((HWND)m_handle, reinterpret_cast<LPCWSTR>(_title));
}

void Win32Window::ShowCursor(B8 _shouldShow)
{
    ::ShowCursor(_shouldShow);
}

void Win32Window::SetCursor(char *_spritePath)
{
}

void Win32Window::SetCursorPos(B32 _newX, B32 _newY)
{
    ::SetCursorPos(_newX, _newY);
}

void Win32Window::ConfineCursor(B8 _isClipped)
{
}

UINT Win32Window::SetupPixelFormat()
{
    PIXELFORMATDESCRIPTOR pfd = {
        .nSize = sizeof(PIXELFORMATDESCRIPTOR),
        .nVersion = 1,
        .dwFlags = PFD_DRAW_TO_WINDOW,
        .iPixelType = PFD_TYPE_RGBA,
        .cColorBits = 24,
        .cAlphaBits = 8,
        .cDepthBits = 24,
        .cStencilBits = 8,
        .iLayerType = PFD_MAIN_PLANE,
    };

    UINT iPixelFormat = ::ChoosePixelFormat(m_savedProps.deviceContext, &pfd);

    if (!iPixelFormat)
        return NULL;

    if (!::SetPixelFormat(m_savedProps.deviceContext, iPixelFormat, &pfd))
        return NULL;

    ::DescribePixelFormat(m_savedProps.deviceContext, iPixelFormat, sizeof(iPixelFormat), &pfd);

    return iPixelFormat;
}

UINT Win32Window::GetDPIScale()
{
    F32 DPI = ::GetDpiForWindow((HWND)m_handle);
    return DPI / 96.0f;
}

} // namespace Rake::Platform

#endif
