/*****************************************************************/ /**
 * \file   AppFramework.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Common.def.h"

#include "Core/Errors/RkException.hpp"

#include "Core/Timers/SyncTimer.hpp"

#if defined(DESKTOP_DEVICE)
#include "Core/GUI/Window.hpp"
#else
#include "GUI/Mobile/Surface.hpp"
#endif

namespace Rake::Core
{

enum class Mode : U32
{
    IsGameMode = 0,
    IsCheatMode = 1,
    IsEditorMode = 2,
    IsTerminalMode = 3
};

typedef struct AppInfo
{
    Mode mode;
    const wchar_t *appName;
} AppInfo, app_info;

class AppFramework
{
  private:
    static AppFramework *m_appInstance;
    B8 m_isRunning = true;
    B8 m_isPaused = false;
    B8 m_isBackground = false;

    std::unique_ptr<SyncTimer> m_timer;
#if defined(DESKTOP_DEVICE) == 1
    std::unique_ptr<Window> m_window;
#elif defined(MOBILE_DEVICE) == 1
    GUI::Surface *m_surface;
#endif

  public:
    RAKE_API AppFramework(const AppInfo &_startupInfo);
    RAKE_API virtual ~AppFramework();

    RAKE_API void Update();
    RAKE_API void Start();
    RAKE_API void Pause();
    RAKE_API void Stop();

    RAKE_API static AppFramework *GetInstance();

  private:
    RAKE_API bool Init();
    RAKE_API void Release();

  protected:
    RAKE_API virtual void OnStart() = 0;
    RAKE_API virtual void OnResume() = 0;
    RAKE_API virtual void OnUpdate() = 0;
    RAKE_API virtual void OnPause() = 0;
    RAKE_API virtual void OnStop() = 0;
};

#define IS_GAME_MODE     Rake::Core::Mode::IsGameMode
#define IS_CHEAT_MODE    Rake::Core::Mode::IsCheatMode
#define IS_EDITOR_MODE   Rake::Core::Mode::IsEditorMode
#define IS_TERMINAL_MODE Rake::Core::Mode::IsTerminalMode

} // namespace Rake::Core
