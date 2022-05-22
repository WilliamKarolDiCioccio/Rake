/*****************************************************************/ /**
 * \file   WindowPAL.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Common.def.h"
#include "Core/EngineConfig.def.h"

#if defined(DESKTOP_DEVICE) == RK_TRUE

#include "Core/Errors/RkException.hpp"

namespace Rake::GUI
{

using namespace Rake::Core;

enum class WindowFlags : U32
{
    IsFullscreen = 0x0001,
    IsWindowed = 0x0002,
    IsFocused = 0x0010,
    IsUnfocused = 0x0020
};

typedef struct WindowProps
{
    long width;
    long height;
    long minWidth;
    long minHeight;
    WindowFlags flags;
    const char *title;

    WindowProps(long _width = 1280, long _height = 720, long _minWidth = 0, long _minHeight = 0, const char *_title = "Rake", WindowFlags _flags = WindowFlags::IsWindowed)
        : width(_width), height(_height), minWidth(_minWidth), minHeight(_minHeight), title(_title), flags(_flags){};
} WindowProps, window_props;

class Window
{
  protected:
    WindowProps m_props;

  public:
    virtual ~Window() = default;
    static Window *CreateNativeWindow(long _width, long _height, long _minWidth, long _minHeight, const char *_title, WindowFlags _flags);

  public:
    virtual void Refresh() = 0;
    virtual void MinimizeWindow() = 0;
    virtual void MaximizeWindow() = 0;
    virtual void FullscreenWindow() = 0;
    virtual void ShouldShow(const B8 _shouldShow) = 0;
    virtual void SetIcon(const char *_iconPath) = 0;
    virtual void SetTitle(const char *_title) = 0;

  public:
    inline long GetWidth() const
    {
        return m_props.width;
    }

    inline long GetHeight() const
    {
        return m_props.width;
    }
};

} // namespace Rake::GUI

#define IS_FULLSCREEN Rake::GUI::WindowFlags::IsFullscreen
#define IS_WINDOWED   Rake::GUI::WindowFlags::IsWindowed
#define IS_FOCUSED    Rake::GUI::WindowFlags::IsFocused
#define IS_UNFOCUSED  Rake::GUI::WindowFlags::IsUnfocused

#endif
