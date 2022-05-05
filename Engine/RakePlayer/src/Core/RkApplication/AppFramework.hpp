/*****************************************************************/ /**
 * \file   AppFramework.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Common.h"

#include "Core/Error/RkException.hpp"
#include "Core/Event/RkEvent.inl.hpp"
#include "Core/Event/EventBus.inl.hpp"
#include "Core/Time/SyncTimer.hpp"
#if defined(DESKTOP_DEVICE) == 1
#include "GUI/Desktop/Window.hpp"
#elif defined(MOBILE_DEVICE) == 1
#include "GUI/Mobile/Surface.hpp"
#endif

namespace Rake::Core
{

enum class ApplicationMode : U32
{
    IsGameMode = 0,
    IsCheatMode = 1,
    IsEditorMode = 2
};

using AppCmdArgs = struct ApplicationCmdArgs
{
    const char *appName;
    ApplicationMode mode;
};

using AppState = struct ApplicationState
{
    B8 isRunning = true;
    B8 isPaused = false;
    B8 isBackground = false;
};

class AppFramework
{
  public:
    __RAKE_PLAYER_API AppFramework(const char *_appName, ApplicationMode _mode);
    __RAKE_PLAYER_API virtual ~AppFramework();

    __RAKE_PLAYER_API void Start();
    __RAKE_PLAYER_API void Update();
    __RAKE_PLAYER_API void Stop();

  private:
    __RAKE_PLAYER_API bool Init();
    __RAKE_PLAYER_API bool Release();

  protected:
    __RAKE_PLAYER_API virtual void OnStart() = 0;
    __RAKE_PLAYER_API virtual void OnResume() = 0;
    __RAKE_PLAYER_API virtual void OnUpdate() = 0;
    __RAKE_PLAYER_API virtual void OnPause() = 0;
    __RAKE_PLAYER_API virtual void OnStop() = 0;

  private:
    static inline bool m_exists = false;
    AppFramework *m_appInstance = nullptr;
    ApplicationState m_state;

  private:
    SyncTimer *m_syncTimer;
#if defined(DESKTOP_DEVICE) == 1
    GUI::Window *m_window;
#elif defined(MOBILE_DEVICE) == 1
    GUI::Surface *m_surface;
#endif
};

} // namespace Rake::Core

#define IS_GAME_MODE   Rake::Core::ApplicationMode::IsGameMode
#define IS_CHEAT_MODE  Rake::Core::ApplicationMode::IsCheatMode
#define IS_EDITOR_MODE Rake::Core::ApplicationMode::IsEditorMode
