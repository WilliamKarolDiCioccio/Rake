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

#include <vector>
#include <ShellScalingApi.h>

#include "GUI/Desktop/Window.hpp"

namespace Rake::Platform
{

class Win32Window final : public GUI::Window
{
  private:
    struct SavedProps
    {
        RECT rect;
        LONG style;
        LONG extendedStyle;
        HDC deviceContext;
        UINT scalingFactor;
    };

    SavedProps m_savedProps;

  public:
    Win32Window();
    ~Win32Window();

  public:
    void Refresh() override;

  public:
    void Show(B8 _shouldShow) override;
    void Maximize(B8 _maximize) override;
    void Fullscreen(B8 _fullscreen) override;
    void SetSize(long _newWidth, long _newHeight) override;
    void SetPos(B32 _newX, B32 _newY) override;
    void SetIcon(const char *_iconPath) override;
    void SetTitle(const wchar_t *_title) override;
    void ShowCursor(B8 _shouldShow) override;
    void SetCursor(char *_spritePath) override;
    void SetCursorPos(B32 _newX, B32 _newY) override;
    void ConfineCursor(B8 _isClipped) override;

  private:
    UINT SetupPixelFormat();
    UINT GetDPIScale();

  public:
    inline U32 GetWidth() const override
    {
        RECT rect;

        if (!::GetClientRect((HWND)m_handle, &rect))
            return NULL;

        return rect.right - rect.left;
    }

    inline U32 GetHeight() const override
    {
        RECT rect;

        if (!::GetClientRect((HWND)m_handle, &rect))
            return NULL;

        return rect.bottom - rect.top;
    }
};

} // namespace Rake::Platform

#endif
