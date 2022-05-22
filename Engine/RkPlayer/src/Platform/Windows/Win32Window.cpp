#include "src/RkPch.hpp"

#if defined(PLATFORM_WINDOWS)

#include "Platform/Windows/Win32Window.hpp"

namespace Rake::GUI::Windows
{

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (uMsg)
    {
    case WM_CREATE: {
    }
    case WM_DESTROY: {
    }
    case WM_SIZE: {
    }
    case WM_SIZING: {
    }
    case WM_CLOSE: {
    }
    default:
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

Win32Window::Win32Window()
{
    WNDCLASSEX wcex = {};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = 0;
    wcex.lpszClassName = L"ApplicationWindow";
    wcex.lpfnWndProc = &WindowProc;

    RK_ASSERT(RegisterClassEx(&wcex) != NULL);

    RECT rc = {0, 0, m_props.width, m_props.height};
    AdjustWindowRect(&rc, WS_SYSMENU, false);

    m_handle = CreateWindowEx(NULL, L"ApplicationWindow", L"Rake", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, NULL, NULL);
    RK_ASSERT(m_handle);

    SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);

    UpdateWindow((HWND)m_handle);
}

Win32Window::~Win32Window()
{
    DestroyWindow((HWND)m_handle);
    RK_ASSERT(!m_handle);
}

void Win32Window::Refresh()
{
    MSG msg;

    if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Win32Window::MinimizeWindow()
{
}

void Win32Window::MaximizeWindow()
{
}

void Win32Window::FullscreenWindow()
{
}

void Win32Window::SetIcon(const char *_iconPath)
{
}

void Win32Window::SetTitle(const char *_title)
{
}

void Win32Window::ShouldShow(const B8 _shouldShow)
{
    if (_shouldShow == true)
        ShowWindow((HWND)m_handle, SW_SHOW);
    else
        ShowWindow((HWND)m_handle, SW_HIDE);
}

} // namespace Rake::GUI::Windows

#endif
