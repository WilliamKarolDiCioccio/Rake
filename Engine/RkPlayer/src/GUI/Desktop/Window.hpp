/*****************************************************************/ /**
 * \file   Window.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Core/Base.hpp"

#if defined(DESKTOP_DEVICE) == 1

#if defined CreateWindow
#undef CreateWindow
#elif defined ShowCuror
#undef ShowCursor
#elif defined SetCursor
#undef SetCursor
#elif defined SetCursorPos
#undef SetCursorPos
#endif

#include <vector>
#include <memory>

namespace Rake::GUI
{

class Window
{
  protected:
    struct SavedState
    {
        B8 isShowing = false;
        B8 isFullscreen = false;
        B8 isMaximized = false;
        B8 isVSync = true;
        B8 isCursorClipped = false;
    };

    SavedState m_savedState;

  public:
    void *m_handle = nullptr;

  public:
    virtual ~Window() = default;
    static std::unique_ptr<Window> CreateWindow();

  public:
    virtual void Refresh() = 0;

  public:
    virtual void Show(B8 _shouldShow) = 0;
    virtual void Maximize(B8 _maximize) = 0;
    virtual void Fullscreen(B8 _fullscreen) = 0;
    virtual void SetSize(long _newWidth, long _newHeight) = 0;
    virtual void SetPos(B32 _newX, B32 _newY) = 0;
    virtual void SetIcon(const char *_iconPath) = 0;
    virtual void SetTitle(const wchar_t *_title) = 0;
    virtual void ShowCursor(B8 _shouldShow) = 0;
    virtual void SetCursor(char *_spritePath) = 0;
    virtual void SetCursorPos(B32 _newX, B32 _newY) = 0;
    virtual void ConfineCursor(B8 _isClipped) = 0;

  public:
    virtual U32 GetWidth() const = 0;
    virtual U32 GetHeight() const = 0;
};

} // namespace Rake::GUI

#endif
