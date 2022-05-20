/*****************************************************************/ /**
 * \file   AppFramework.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Common.def.h"

#include "Core/Error/RkException.hpp"

#include "Core/Event/RkEvent.inl.hpp"
#include "Core/Event/EventBus.inl.hpp"
#include "Core/Time/SyncTimer.hpp"

#ifdef DESKTOP_DEVICE
#include "GUI/Desktop/Window.hpp"
#else
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

class AppFramework
{
  private:
    static AppFramework *m_appInstance;
    B8 isRunning = true;
    B8 isPaused = false;
    B8 isBackground = false;

  public:
    RAKE_API AppFramework(const char *_appName, ApplicationMode _mode);
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

  private:
    SyncTimer *m_timer;
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
