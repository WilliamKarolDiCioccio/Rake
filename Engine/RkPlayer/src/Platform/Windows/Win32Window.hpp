/*****************************************************************/ /**
 * \file   WindowsWindow.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Types.h"

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
    void Maximize(const B8 _maximize) override;
    void Fullscreen(const B8 _fullscreen) override;
    void Show(const B8 _shouldShow) override;
    void SetTitle(const wchar_t *_title) override;
    void SetIcon(const char *_iconPath) override;
    void RkSetCursor(const char *_spritePath) override;
    void SetSize(long _newWidth, long _newHeight) override;
    void SetPos(long _newX, long _newY) override;

  private:
    UINT SetupPixelFormat();

  public:
    void MakeCurrentContext() override;
    void DestroyContext() override;

  private:
    HDC hDC;
    HGLRC hRC;
    UINT m_pixelFormat;
};

} // namespace Rake::Windows

#endif
