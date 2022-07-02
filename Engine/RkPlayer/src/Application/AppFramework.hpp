/*****************************************************************/ /**
 * \file   AppFramework.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#if defined(PLATFORM_WINDOWS) == 1
#include "Platform/Windows/Win32App.hpp"
#endif

#include "Core/Timer/SyncTimer.hpp"
#include "GUI/Window.hpp"
#include "Engine/Renderer/Renderer.hpp"

namespace Rake::Application
{

using namespace std::chrono_literals;

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
    const char *iconPath;
    const char *cursorPath;
} AppInfo, app_info;

class AppFramework : public PLATFORM_APP_FRAMEWORK
{
  private:
    static AppFramework *m_appInstance;
    B8 m_isRunning = true;
    B8 m_isPaused = false;
    B8 m_isBackground = false;
    const std::chrono::milliseconds m_sleep = 16ms;

  protected:
    std::unique_ptr<Core::Timer::SyncTimer> m_timer;
    std::unique_ptr<GUI::Window> m_window;
    std::unique_ptr<Engine::Graphics::Renderer> m_gEngine;

  public:
    RAKE_API AppFramework(const AppInfo _appInfo);
    RAKE_API virtual ~AppFramework();

    RAKE_API void Update();
    RAKE_API void Start();
    RAKE_API void Pause();
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

#define IS_GAME_MODE     Rake::Application::Mode::IsGameMode
#define IS_CHEAT_MODE    Rake::Application::Mode::IsCheatMode
#define IS_EDITOR_MODE   Rake::Application::Mode::IsEditorMode
#define IS_TERMINAL_MODE Rake::Application::Mode::IsTerminalMode
