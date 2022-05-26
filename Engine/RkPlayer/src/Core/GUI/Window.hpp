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

namespace Rake::Core
{

class Window
{
  protected:
    enum class State : U32
    {
        IsFocused = 1,
        IsUnfocused = !IsFocused,
        IsMaximized = 3,
        IsMinimized = !IsMaximized | IsUnfocused,
        IsWindowed = 5,
        IsFullscreen = !IsWindowed | IsFocused,
    };

    typedef struct Icon
    {
        void *imagePath;
        void *imageHandle;
    } Icon, icon;

    typedef struct Monitor
    {
        long *width;
        long *height;
        B32 *monitorID;
    } Monitor, monitor;

  protected:
    State m_state;
    long m_width = 1280;
    long m_height = 720;
    long m_minWidth = 0;
    long m_minHeight = 0;
    long m_posX = 0;
    long m_posY = 0;
    const wchar_t *m_title = L"🤣Rake🤣";

  protected:
    void *m_handle = nullptr;
    void *m_context = nullptr;

  public:
    virtual ~Window() = default;
    static std::unique_ptr<Window> CreateNativeWindow();

  public:
    virtual void Refresh() = 0;

  public:
    RAKE_API virtual void Minimize() = 0;
    RAKE_API virtual void Maximize() = 0;
    RAKE_API virtual void Fullscreen() = 0;
    RAKE_API virtual void ShouldShow(const B8 _shouldShow) = 0;
    RAKE_API virtual void SetIcon(const char *_iconPath) = 0;
    RAKE_API virtual void SetTitle(const wchar_t *_title) = 0;
    RAKE_API virtual void SetSize(long _newWidth, long _setSize) = 0;
    RAKE_API virtual void SetPos(long _newX, long _newY) = 0;

    virtual void MakeCurrentContext() = 0;
    virtual void DestroyContext() = 0;

  public:
    RAKE_API inline long GetWidth() const
    {
        return this->m_width;
    }

    RAKE_API inline long GetHeight() const
    {
        return this->m_width;
    }

    RAKE_API inline long GetPosX()
    {
        return this->m_posX;
    }

    RAKE_API inline long GetPosY()
    {
        return this->m_posY;
    }
};

} // namespace Rake::Core

#endif
