/*****************************************************************/ /**
 * \file   AppFramework.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include <map>

#include "Core/Base.hpp"

#include "Core/SyncTimer.hpp"
#include "GUI/Desktop/Window.hpp"
#include "Engine/Renderer/Renderer.hpp"

namespace Rake::Application
{

enum class Mode : U32
{
    IsGameMode = 0,
    IsCheatMode = 1,
    IsEditorMode = 2,
};

struct AppData
{
    Mode mode;
    const wchar_t *appName;
    const char *iconPath;
    const char *cursorPath;
};

class AppFramework
{
  private:
    static inline AppFramework *m_appInstance = nullptr;
    AppData m_appData;

    struct AppState
    {
        B8 isRunning = true;
        B8 isPaused = false;
        B8 isBackground = false;
    };

    AppState m_appState;

  private:
    std::unique_ptr<Core::SyncTimer> m_timer;
    std::unique_ptr<GUI::Window> m_mainWindow;
    std::unique_ptr<Engine::Renderer> m_gEngine;

  public:
    RAKE_API AppFramework(const AppData &_appData);
    RAKE_API virtual ~AppFramework();
    RAKE_API static AppFramework *GetInstance();

  public:
    RAKE_API void Update();
    RAKE_API void Start();
    RAKE_API void Pause();
    RAKE_API void Resume();
    RAKE_API void Stop();

  private:
    B8 Init();
    void Release();
    void CreateSplash();
    void DestroySplash();

  protected:
    RAKE_API virtual void OnStart() = 0;
    RAKE_API virtual void OnResume() = 0;
    RAKE_API virtual void OnUpdate() = 0;
    RAKE_API virtual void OnPause() = 0;
    RAKE_API virtual void OnStop() = 0;
};

} // namespace Rake::Application

#define APP_FRAMEWORK Rake::Application::AppFramework

#define GAME_MODE   Rake::Application::Mode::IsGameMode
#define CHEAT_MODE  Rake::Application::Mode::IsCheatMode
#define EDITOR_MODE Rake::Application::Mode::IsEditorMode
