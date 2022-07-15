/*****************************************************************/ /**
 * \file   AppFramework.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Core/Base.hpp"

#if defined(PLATFORM_WINDOWS) == 1
#include "Platform/Windows/Win32App.hpp"
#endif

#include "Core/SyncTimer.hpp"
#include "GUI/Desktop/Window.hpp"
#include "GUI/Desktop/WindowManager.hpp"
#include "Engine/Renderer/Renderer.hpp"

namespace Rake::Application
{

using namespace std::chrono_literals;

enum class Mode : U32
{
    IsGameMode = 0,
    IsCheatMode = 1,
    IsEditorMode = 2,
};

typedef struct AppData
{
    Mode mode;
    const wchar_t *appName;
    const char *iconPath;
    const char *cursorPath;
} AppData;

class AppFramework : public PLATFORM_APP_FRAMEWORK
{
  private:
    static AppFramework *m_appInstance;

    struct AppState
    {
        B8 isRunning = true;
        B8 isPaused = false;
        B8 isBackground = false;
    };

    AppState m_appState;

  private:
    std::unique_ptr<Core::SyncTimer> m_timer;
    std::unique_ptr<GUI::Window> m_window;
    std::unique_ptr<Engine::Renderer> m_gEngine;

  public:
    RAKE_API AppFramework(AppData _appData);
    RAKE_API virtual ~AppFramework();

    RAKE_API void Update();
    RAKE_API void Start();
    RAKE_API void Pause(B8 _isPaused);
    RAKE_API void Stop();

    RAKE_API static AppFramework *GetInstance();

  private:
    B8 Init();
    void Release();

  protected:
    RAKE_API virtual void OnStart() = 0;
    RAKE_API virtual void OnResume() = 0;
    RAKE_API virtual void OnUpdate() = 0;
    RAKE_API virtual void OnPause() = 0;
    RAKE_API virtual void OnStop() = 0;
};

} // namespace Rake::Application

#define APP_FRAMEWORK Rake::Application::AppFramework

#define IS_GAME_MODE   Rake::Application::Mode::IsGameMode
#define IS_CHEAT_MODE  Rake::Application::Mode::IsCheatMode
#define IS_EDITOR_MODE Rake::Application::Mode::IsEditorMode
