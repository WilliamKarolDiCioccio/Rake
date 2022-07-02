/*****************************************************************/ /**
 * \file   WindowsWindow.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Core/Base.hpp"

#if defined(PLATFORM_WINDOWS) == 1

#include "Application/GUI/Window.hpp"

namespace Rake::Platform::Windows
{

class Win32Window final : public Application::GUI::Window
{
  public:
    Win32Window();
    ~Win32Window();

  public:
    void Refresh() override;

  public:
    void Maximize(const B8 _maximize) override;
    void Fullscreen(const B8 _fullscreen) override;
    void Show(const B8 _shouldShow) override;
    void RkShowCursor(const B8 _shouldShow) override;
    void SetTitle(const wchar_t *_title) override;
    void SetIcon(const char *_iconPath) override;
    void RkSetCursor(const char *_spritePath) override;
    void SetSize(long _newWidth, long _newHeight) override;
    void SetPos(long _newX, long _newY) override;
    void RkSetCursorPos(long _newX, long _newY) override;

  private:
    void GetMonitorMetrics(std::vector<Application::GUI::Monitor> &_monitor) override;

  private:
    UINT SetupPixelFormat();

  private:
    HDC hDC;
    UINT m_pixelFormat;
};

} // namespace Rake::Platform::Windows

#endif
