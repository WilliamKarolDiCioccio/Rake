#include "RkPch.h"

#include "AppFramework.hpp"

using namespace std::chrono_literals;

namespace Rake::Application
{

AppFramework::AppFramework(const AppData &_appData) : m_appData(_appData)
{
    if (!m_appInstance)
    {
        m_appInstance = this;

        if (_appData.mode == GAME_MODE)
        {
        }
        else if (_appData.mode == CHEAT_MODE)
        {
        }
        else if (_appData.mode == EDITOR_MODE)
        {
        }
        else
        {
        }

        if (!this->Init())
        {
        }

        m_mainWindow->SetTitle(_appData.appName);
    }
}

AppFramework::~AppFramework()
{
    this->Release();

    delete (m_appInstance);
}

void AppFramework::Update()
{
    while (m_appState.isRunning)
    {
        while (m_appState.isPaused)
            ;

        m_timer->Tick();
        m_mainWindow->Refresh();
        std::cout << m_mainWindow->GetWidth() << '\n';

        this->OnUpdate();

        std::this_thread::sleep_for(16ms);
    }
}

void AppFramework::Start()
{
    m_mainWindow->Fullscreen(true);
    m_mainWindow->ConfineCursor(true);
    m_mainWindow->Highlight();

    m_appState.isRunning = true;

    this->OnStart();
}

void AppFramework::Pause()
{
    if (m_appState.isPaused != true)
    {
        m_appState.isPaused = true;
        this->OnPause();
    }
}

void AppFramework::Resume()
{
    if (m_appState.isPaused != false)
    {
        m_appState.isPaused = false;
        this->OnResume();
    }
}

void AppFramework::Stop()
{
    m_mainWindow->Show(false);

    m_appState.isRunning = false;

    this->OnStop();
}

AppFramework *AppFramework::GetInstance()
{
    if (AppFramework::m_appInstance != nullptr)
        return AppFramework::m_appInstance;
    else
        return nullptr;
}

B8 AppFramework::Init()
{
    m_timer = std::make_unique<Core::SyncTimer>();
    m_mainWindow = GUI::WindowManager::CreateNativeView();
    m_gEngine = Engine::Renderer::CreateRenderer(API_VULKAN);

    return true;
}

void AppFramework::Release()
{
}

void AppFramework::CreateSplash()
{
}

void AppFramework::DestroySplash()
{
}

} // namespace Rake::Application
