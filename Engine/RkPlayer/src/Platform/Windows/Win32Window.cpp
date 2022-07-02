#include "src/RkPch.h"

#if defined(PLATFORM_WINDOWS) == 1

#include "Platform/Windows/Win32Window.hpp"

namespace Rake::Platform::Windows
{

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (uMsg)
    {
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
    this->GetMonitorMetrics(m_monitorList);

    WNDCLASSEX extendedWindow = {
        .cbSize = sizeof(WNDCLASSEX),
        .style = 0,
        .lpfnWndProc = &WindowProc,
        .lpszClassName = L"RakeWindow",
    };

    if (RegisterClassEx(&extendedWindow) == NULL)
        throw Core::Error::RkException("Unable to register window class", __FILE__, __LINE__);

    RECT rc = {0, 0, m_width, m_height};
    AdjustWindowRect(&rc, WS_SYSMENU, false);

    m_handle = CreateWindowEx(NULL, L"RakeWindow", reinterpret_cast<LPCWSTR>(m_title), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, NULL, NULL);

    if (!m_handle)
        throw Core::Error::RkException("Handle to the window is NULL!", __FILE__, __LINE__);

    hDC = GetDC((HWND)m_handle), m_context = hDC;
    m_pixelFormat = SetupPixelFormat();

    if (!hDC)
        throw Core::Error::RkException("Device context is a NULL value!", __FILE__, __LINE__);

    SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);
    SetWindowDisplayAffinity((HWND)m_handle, WDA_NONE);
}

Win32Window::~Win32Window()
{
    ReleaseDC((HWND)m_handle, hDC);
    RK_ASSERT(!hDC);
    DestroyWindow((HWND)m_handle);
    delete (m_handle);
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

    m_isMaximized = _maximize;
}

void Win32Window::Fullscreen(const B8 _fullscreen)
{
    DWORD hStyle = GetWindowLong((HWND)m_handle, GWL_STYLE);

    if (_fullscreen)
    {
    }
    else
    {
    }

    m_isFullscreen = _fullscreen;
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

void Win32Window::RkShowCursor(const B8 _shouldShow)
{
    ShowCursor(_shouldShow);
}

void Win32Window::SetSize(long _newWidth, long _newHeight)
{
    SetWindowPos((HWND)m_handle, HWND_TOPMOST, NULL, NULL, _newWidth, _newHeight, SWP_NOREPOSITION);

    m_width = _newWidth, m_height = _newHeight;
}

void Win32Window::SetPos(long _newX, long _newY)
{
    SetWindowPos((HWND)m_handle, HWND_TOPMOST, _newX, _newY, NULL, NULL, SWP_NOSIZE);

    m_posX = _newX, m_posY = _newY;
}

void Win32Window::RkSetCursorPos(long _newX, long _newY)
{
    SetCursorPos(_newX, _newY);

    m_cursor.posX = _newX, m_cursor.posY = _newY;
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

    const UINT iPixelFormat = ChoosePixelFormat(hDC, &pfd);

    if (!iPixelFormat)
    {
        throw Core::Error::RkException("iPixelFormat (int) is a NULL value!", __FILE__, __LINE__);
        return NULL;
    }

    if (!SetPixelFormat(hDC, iPixelFormat, &pfd))
    {
        throw Core::Error::RkException("Unable to set an adequate pixel format", __FILE__, __LINE__);
        return NULL;
    }

    DescribePixelFormat(hDC, iPixelFormat, sizeof(iPixelFormat), &pfd);

    return iPixelFormat;
}

void Win32Window::GetMonitorMetrics(std::vector<Application::GUI::Monitor> &_monitorList)
{
    DISPLAY_DEVICE displayDevice = {.cb = sizeof(displayDevice)};
    DWORD deviceIndex = NULL;

    while (EnumDisplayDevices(NULL, deviceIndex, &displayDevice, NULL))
    {
        Application::GUI::Monitor monitor;

        monitor.name = displayDevice.DeviceName;
        monitor.ID = displayDevice.DeviceID;
        _monitorList.push_back(monitor);

        U32 monitorIndex = NULL;

        while (EnumDisplayDevices(reinterpret_cast<LPCWSTR>(monitor.name), monitorIndex, &displayDevice, NULL))
        {
            monitorIndex++;
        }

        deviceIndex++;
    }
}

} // namespace Rake::Platform::Windows

#endif
