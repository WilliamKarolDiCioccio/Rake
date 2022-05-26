/*****************************************************************/ /**
 * \file   WindowsWindow.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Common.def.h"

#if defined(PLATFORM_WINDOWS)

#include "Core/GUI/Window.hpp"

namespace Rake::Windows
{

class Win32Window final : public Core::Window
{
  public:
    Win32Window();
    ~Win32Window();

  public:
    void Refresh() override;

  public:
    void Minimize() override;
    void Maximize() override;
    void Fullscreen() override;
    void ShouldShow(const B8 _shouldShow) override;
    void SetIcon(const char *_iconPath) override;
    void SetTitle(const wchar_t *_title) override;
    void SetSize(long _newWidth, long _newHeight) override;
    void SetPos(long _newX, long _newY) override;

    void MakeCurrentContext() override;
    void DestroyContext() override;

  private:
    WNDCLASSEX wcex = {};
    RECT rc = {};
    PIXELFORMATDESCRIPTOR pfd = {};
    HMONITOR hMonitor = MonitorFromWindow((HWND)m_handle, MONITOR_DEFAULTTONEAREST);
    MONITORINFOEX hMonitorInfo;
    HRSRC hFindRes;
    HRSRC hLoadRes;
    HICON hIcon;
    BYTE *lpRes;
    B32 currentResID;
};

} // namespace Rake::Windows

#endif
