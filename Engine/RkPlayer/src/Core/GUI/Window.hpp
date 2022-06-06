/*****************************************************************/ /**
 * \file   WindowPAL.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Types.h"
#include "Core/Rake.h"

#include "Core/EngineConfig.def.h"

#if defined(DESKTOP_DEVICE) == RK_TRUE

#include "Core/Errors/RkException.hpp"

namespace Rake::Core
{

typedef struct MonitorInfo
{
    long width;
    long height;
    U32 *ID;
} MonitorInfo, monitor_info;

typedef struct WindowInfo
{
    long width = 1280;
    long height = 720;
    long minWidth = 0;
    long minHeight = 0;
    long posX = 0;
    long posY = 0;
    const wchar_t *title = L"Rake";
} WindowInfo, window_info;

typedef struct ContextInfo
{
    char *API;
} ContextInfo, context_info;

class Window
{
  public:
    MonitorInfo m_monIn;
    WindowInfo m_winIn;
    ContextInfo m_conIn;

  protected:
    B8 m_isFullscreen = false;
    B8 m_isMaximized = false;
    B8 m_isFocused = true;

  protected:
    void *m_handle = nullptr;
    void *m_context = nullptr;

  public:
    virtual ~Window() = default;
    static std::unique_ptr<Window> CreateNativeWindow();

  public:
    virtual void Refresh() = 0;

  public:
    RAKE_API virtual void Maximize(const B8 _maximize) = 0;
    RAKE_API virtual void Fullscreen(const B8 _fullscreen) = 0;
    RAKE_API virtual void Show(const B8 _shouldShow) = 0;
    RAKE_API virtual void SetTitle(const wchar_t *_title) = 0;
    RAKE_API virtual void SetIcon(const char *_iconPath) = 0;
    RAKE_API virtual void RkSetCursor(const char *_spritePath) = 0;
    RAKE_API virtual void SetSize(long _newWidth, long _setSize) = 0;
    RAKE_API virtual void SetPos(long _newX, long _newY) = 0;

  public:
    virtual void MakeCurrentContext() = 0;
    virtual void DestroyContext() = 0;
};

} // namespace Rake::Core

#endif
