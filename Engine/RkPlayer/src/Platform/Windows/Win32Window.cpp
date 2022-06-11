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
    case WM_SETICON: {
    }
    case WM_SETCURSOR: {
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
    {
        m_monIn.height = GetSystemMetrics(SM_CXSCREEN);
        m_monIn.width = GetSystemMetrics(SM_CYSCREEN);

        DISPLAY_DEVICE dispDevice = {};

        while (EnumDisplayDevices(NULL, reinterpret_cast<DWORD>(m_monIn.Id), &dispDevice, DISPLAY_DEVICE_PRIMARY_DEVICE))
            m_monIn.Id++;
    }

    WNDCLASSEX wcex = {
        .cbSize = sizeof(WNDCLASSEX),
        .style = 0,
        .lpfnWndProc = &WindowProc,
        .hIcon = LoadIcon(NULL, IDI_WINLOGO),
        .hCursor = LoadCursor(NULL, IDC_ARROW),
        .lpszClassName = L"ApplicationWindow",
    };

    if (RegisterClassEx(&wcex) == NULL)
        throw Core::RkException("Unable to register window class", __FILE__, __LINE__);

    RECT rc = {0, 0, m_winIn.width, m_winIn.height};
    AdjustWindowRect(&rc, WS_SYSMENU, false);

    m_handle = CreateWindowEx(NULL, L"ApplicationWindow", reinterpret_cast<LPCWSTR>(m_winIn.title), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, NULL, NULL);

    if (!m_handle)
        throw Core::RkException("Handle to the window is NULL!", __FILE__, __LINE__);

    hDC = GetDC((HWND)m_handle);
    m_pixelFormat = SetupPixelFormat();

    if (!hDC)
        throw Core::RkException("Device context is a NULL value!", __FILE__, __LINE__);

    SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);
    SetWindowDisplayAffinity((HWND)m_handle, WDA_NONE);
}

Win32Window::~Win32Window()
{
    ReleaseDC((HWND)m_handle, hDC);
    RK_ASSERT(!hDC);
    DestroyWindow((HWND)m_handle);
    RK_ASSERT(!m_handle);
}

void Win32Window::Refresh()
{
}

void Win32Window::Maximize(const B8 _maximize)
{
    if (_maximize)
        ShowWindow((HWND)m_handle, SW_SHOWMAXIMIZED);
    else
        ShowWindow((HWND)m_handle, SW_SHOWMINIMIZED);

    m_isMaximized = true;
}

void Win32Window::Fullscreen(const B8 _fullscreen)
{
    DWORD hStyle = GetWindowLong((HWND)m_handle, GWL_STYLE);

    if (_fullscreen)
    {
        m_isFullscreen = true;
    }
    else
    {
        m_isFullscreen = false;
    }
}

void Win32Window::SetTitle(const wchar_t *_title)
{
    SetWindowTextW((HWND)m_handle, reinterpret_cast<LPCWSTR>(_title));
}

void Win32Window::SetIcon(const char *_iconPath)
{
}

void Win32Window::RkSetCursor(const char *_spritePath)
{
}

void Win32Window::Show(const B8 _shouldShow)
{
    ShowWindow((HWND)m_handle, _shouldShow);
}

void Win32Window::SetSize(long _newWidth, long _newHeight)
{
    SetWindowPos((HWND)m_handle, HWND_TOPMOST, NULL, NULL, _newWidth, _newHeight, SWP_NOREPOSITION);

    m_winIn.width = _newWidth, m_winIn.height = _newHeight;
}

void Win32Window::SetPos(long _newX, long _newY)
{
    SetWindowPos((HWND)m_handle, HWND_TOPMOST, _newX, _newY, NULL, NULL, SWP_NOSIZE);

    m_winIn.posX = _newX, m_winIn.posY = _newY;
}

UINT Win32Window::SetupPixelFormat()
{
    PIXELFORMATDESCRIPTOR pfd = {
        .nSize = sizeof(PIXELFORMATDESCRIPTOR),
        .nVersion = 1,
        .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        .iPixelType = PFD_TYPE_RGBA,
        .cColorBits = 24,
        .cAlphaBits = 8,
        .cDepthBits = 24,
        .cStencilBits = 8,
        .iLayerType = PFD_MAIN_PLANE,
    };

    const UINT iPixelFormat = ChoosePixelFormat(hDC, &pfd);

    if (!iPixelFormat)
    {
        throw Core::RkException("iPixelFormat (int) is a NULL value!", __FILE__, __LINE__);
        return NULL;
    }

    if (!SetPixelFormat(hDC, iPixelFormat, &pfd))
    {
        throw Core::RkException("Unable to set an adequate pixel format", __FILE__, __LINE__);
        return NULL;
    }

    DescribePixelFormat(hDC, iPixelFormat, sizeof(iPixelFormat), &pfd);

    return iPixelFormat;
}

void Win32Window::MakeCurrentContext()
{
    hRC = wglCreateContext(hDC);

    if (!hRC)
        throw Core::RkException("hRC (HGLRC) is a NULL value!", __FILE__, __LINE__);

    if (!wglMakeCurrent(hDC, hRC))
        throw Core::RkException("Unable to make the context current", __FILE__, __LINE__);
}

void Win32Window::DestroyContext()
{
    wglDeleteContext(hRC);
    RK_ASSERT(!hRC);
}

} // namespace Rake::Windows

#endif
