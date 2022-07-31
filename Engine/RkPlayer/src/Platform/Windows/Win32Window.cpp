#include "RkPch.h"

#if defined(PLATFORM_WINDOWS) == 1

#include "Platform/Windows/Win32Window.hpp"

namespace Rake::Win32
{

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (uMsg)
    {
    case WM_CLOSE: {
        ::PostQuitMessage(NULL);
        break;
    }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
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
        .lpszClassName = L"RkWindowClass",
    };
    RK_ASSERT(RegisterClassEx(&extendedWindow));

    m_handle = CreateWindowExW(NULL, L"RkWindowClass", L"RkDefaultWindow", WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, NULL, NULL, NULL, NULL);
    RK_ASSERT(m_handle);

    ::AdjustWindowRectEx(&m_savedProps.rect, WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX, FALSE, NULL);
    ::GetWindowRect((HWND)m_handle, &m_savedProps.rect);

    m_savedProps.style = GetWindowLong((HWND)m_handle, GWL_STYLE);
    m_savedProps.extendedStyle = GetWindowLong((HWND)m_handle, GWL_EXSTYLE);
    m_savedProps.deviceContext = ::GetDC((HWND)m_handle);
    m_savedProps.scalingFactor = ::GetDpiForWindow((HWND)m_handle) / 96;

    SetWindowLong((HWND)m_handle, GWLP_USERDATA, (LONG)this);

    ::SetWindowDisplayAffinity((HWND)m_handle, WDA_NONE);
    ::ShowWindow((HWND)m_handle, SW_SHOW);
}

Win32Window::~Win32Window()
{
    ::ReleaseDC((HWND)m_handle, m_savedProps.deviceContext);
    ::DestroyWindow((HWND)m_handle);

    delete (m_handle);
}

void Win32Window::Refresh()
{
    MSG msg;

    if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
    {
        ::TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
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

            int fullClientSizeX = GetSystemMetrics(SM_CXSCREEN), fullClientSizeY = GetSystemMetrics(SM_CYSCREEN);

            this->SetPos(0, 0);
            this->SetSize(fullClientSizeX, fullClientSizeY);

            if (m_savedState.isCursorClipped)
                this->ConfineCursor(true);
        }
        else
        {
            SetWindowLong((HWND)m_handle, GWL_STYLE, m_savedProps.style);
            SetWindowLong((HWND)m_handle, GWL_EXSTYLE, m_savedProps.extendedStyle);

            if (m_savedState.isMaximized)
                this->Maximize(true);

            if (m_savedState.isCursorClipped)
                this->ConfineCursor(true);
        }
    }
    else
        return;
}

void Win32Window::SetSize(long _newWidth, long _newHeight)
{
    ::SetWindowPos((HWND)m_handle, HWND_TOP, NULL, NULL, _newWidth, _newHeight, SWP_NOMOVE);

    ::GetWindowRect((HWND)m_handle, &m_savedProps.rect);

    if (m_savedState.isCursorClipped)
        this->ConfineCursor(true);
}

void Win32Window::SetPos(B32 _newX, B32 _newY)
{
    ::SetWindowPos((HWND)m_handle, HWND_TOP, _newX, _newY, NULL, NULL, SWP_NOSIZE);

    ::GetWindowRect((HWND)m_handle, &m_savedProps.rect);

    if (m_savedState.isCursorClipped)
        this->ConfineCursor(true);
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

void Win32Window::ConfineCursor(B8 _clip)
{
    if (m_savedState.isCursorClipped != _clip)
        m_savedState.isCursorClipped = _clip;

    ::ClipCursor(&m_savedProps.rect);
}

void Win32Window::Highlight() const
{
    FLASHWINFO flashWndInfo = {
        .cbSize = sizeof(FLASHWINFO),
        .hwnd = (HWND)m_handle,
        .dwFlags = FLASHW_TRAY,
        .uCount = 3,
        .dwTimeout = 1500,
    };

    FlashWindowEx(&flashWndInfo);
}

} // namespace Rake::Win32

#endif
