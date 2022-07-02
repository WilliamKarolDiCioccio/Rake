/*****************************************************************/ /**
 * \file   WindowPAL.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#if defined(DESKTOP_DEVICE) == 1

#ifdef CreateWindow
#undef CreateWindow
#endif

namespace Rake::Application::GUI
{

typedef struct Monitor
{
    long width = 1920;
    long height = 1080;
    const wchar_t *name = L"DefaultMonitor";
    const wchar_t *ID = L"1";
} Monitor, monitor;

typedef struct Cursor
{
    long posX = 0;
    long posY = 0;
} Cursor, cursor;

class Window
{
  public:
    std::vector<Monitor> m_monitorList;
    Cursor m_cursor;

  public:
    long m_width = 1280;
    long m_height = 720;
    long m_minWidth = 0;
    long m_minHeight = 0;
    long m_posX = 0;
    long m_posY = 0;
    const wchar_t *m_title = L"Rake";

  protected:
    B8 m_isFullscreen = false;
    B8 m_isMaximized = false;
    B8 m_isVSync = true;

  public:
    void *m_handle = nullptr;
    void *m_context = nullptr;

  public:
    virtual ~Window() = default;
    static std::unique_ptr<Window> CreateWindow();

  public:
    virtual void Refresh() = 0;

  public:
    RAKE_API virtual void Maximize(const B8 _maximize) = 0;
    RAKE_API virtual void Fullscreen(const B8 _fullscreen) = 0;
    RAKE_API virtual void Show(const B8 _shouldShow) = 0;
    RAKE_API virtual void RkShowCursor(const B8 _shouldShow) = 0;
    RAKE_API virtual void SetTitle(const wchar_t *_title) = 0;
    RAKE_API virtual void SetIcon(const char *_iconPath) = 0;
    RAKE_API virtual void RkSetCursor(const char *_spritePath) = 0;
    RAKE_API virtual void SetSize(long _newWidth, long _setSize) = 0;
    RAKE_API virtual void SetPos(long _newX, long _newY) = 0;
    RAKE_API virtual void RkSetCursorPos(long _newX, long _newY) = 0;

  private:
    virtual void GetMonitorMetrics(std::vector<Application::GUI::Monitor> &_monitor) = 0;
};

} // namespace Rake::Application::GUI

#endif
