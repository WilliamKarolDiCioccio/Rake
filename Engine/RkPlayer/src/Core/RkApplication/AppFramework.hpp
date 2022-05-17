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

class AppFramework
{
  private:
    static AppFramework *m_appInstance;
    B8 isRunning = true;
    B8 isPaused = false;
    B8 isBackground = false;

  public:
    __RAKE_API AppFramework(const char *_appName, ApplicationMode _mode);
    __RAKE_API virtual ~AppFramework();

    __RAKE_API void Update();
    __RAKE_API void Start();
    __RAKE_API void Pause();
    __RAKE_API void Stop();

    __RAKE_API static AppFramework *RetriveInstance();

  private:
    __RAKE_API bool Init();
    __RAKE_API void Release();

  protected:
    __RAKE_API virtual void OnStart() = 0;
    __RAKE_API virtual void OnResume() = 0;
    __RAKE_API virtual void OnUpdate() = 0;
    __RAKE_API virtual void OnPause() = 0;
    __RAKE_API virtual void OnStop() = 0;

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
