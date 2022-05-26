#include "src/RkPch.hpp"

#if defined(PLATFORM_WINDOWS)

#include "Platform/Windows/Win32Window.hpp"

#include <gl/glew.h>
#include <gl/wglew.h>

namespace Rake::Windows
{

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (uMsg)
    {
    case WM_PAINT: {
    }
    case WM_CREATE: {
    }
    case WM_DESTROY: {
    }
    case WM_SIZE: {
    }
    case WM_SIZING: {
    }
    case WM_CLOSE: {
        PostQuitMessage(NULL);
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return NULL;
}

Win32Window::Win32Window()
{
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = 0;
    wcex.lpszClassName = L"ApplicationWindow";
    wcex.lpfnWndProc = &WindowProc;

    RK_ASSERT(RegisterClassEx(&wcex) != NULL);

    rc = {0, 0, m_width, m_height};
    AdjustWindowRect(&rc, WS_SYSMENU, false);

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_GENERIC_ACCELERATED;

    m_handle = CreateWindowEx(NULL, L"ApplicationWindow", reinterpret_cast<LPCWSTR>(m_title), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, NULL, NULL);
    RK_ASSERT(m_handle != NULL);

    SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);

    UpdateWindow((HWND)m_handle);
}

Win32Window::~Win32Window()
{
    DestroyWindow((HWND)m_handle);
    RK_ASSERT(!m_handle);
    UnregisterClass(L"ApplicationWindow", wcex.hInstance);
    RK_ASSERT(!&wcex);
}

void Win32Window::Refresh()
{
    MSG msg;

    if (PeekMessage(&msg, (HWND)m_handle, NULL, NULL, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Win32Window::Minimize()
{
    if (m_state != Core::Window::State::IsMinimized)
    {
        ShowWindow((HWND)m_handle, SW_SHOWMINIMIZED);
        m_state = Core::Window::State::IsMinimized;
    }
}

void Win32Window::Maximize()
{
    if (m_state != Core::Window::State::IsMaximized)
    {
        ShowWindow((HWND)m_handle, SW_SHOWMAXIMIZED);
        m_state = Core::Window::State::IsMaximized;
    }
}

void Win32Window::Fullscreen()
{
    if (m_state != Core::Window::State::IsFullscreen)
    {
        m_state = Core::Window::State::IsFullscreen;
    }
}

void Win32Window::SetIcon(const char *_iconPath)
{
    DrawIcon(GetDC((HWND)m_handle), 10, 10, hIcon);
}

void Win32Window::SetTitle(const wchar_t *_title)
{
    SetWindowTextW((HWND)m_handle, reinterpret_cast<LPCWSTR>(_title));
}

void Win32Window::ShouldShow(const B8 _shouldShow)
{
    ShowWindow((HWND)m_handle, _shouldShow);
}

void Win32Window::SetSize(long _newWidth, long _newHeight)
{
    SetWindowPos((HWND)m_handle, HWND_TOPMOST, NULL, NULL, _newWidth, _newHeight, SWP_NOREPOSITION);

    m_width = _newWidth;
    m_height = _newHeight;
}

void Win32Window::SetPos(long _newX, long _newY)
{
    SetWindowPos((HWND)m_handle, HWND_TOPMOST, _newX, _newY, NULL, NULL, SWP_NOSIZE);

    m_posX = _newX;
    m_posY = _newY;
}

void Win32Window::MakeCurrentContext()
{
    wglCreateContext(GetDC((HWND)m_handle));
    wglMakeCurrent(GetDC((HWND)m_handle), (HGLRC)m_context);
}

void Win32Window::DestroyContext()
{
    wglDeleteContext((HGLRC)m_context);
}

} // namespace Rake::Windows

#endif
