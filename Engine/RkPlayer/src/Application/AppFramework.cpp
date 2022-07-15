#include "src/RkPch.h"

#include "AppFramework.hpp"

namespace Rake::Application
{

AppFramework *AppFramework::m_appInstance = nullptr;

AppFramework::AppFramework(const AppData _appData)
{
    if (!m_appInstance)
    {
        m_appInstance = this;

        if (_appData.mode == IS_GAME_MODE)
        {
        }
        else if (_appData.mode == IS_CHEAT_MODE)
        {
        }
        else if (_appData.mode == IS_EDITOR_MODE)
        {
        }
        else
        {
            RK_SIGABRT;
        }

        if (!this->Init())
        {
            RK_SIGABRT;
        }

        m_window->SetTitle(_appData.appName);
    }
    else
    {
        return;
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
            this->PumpPlatformMessages();

        this->PumpPlatformMessages();

        m_timer->Tick();
        m_window->Refresh();

        std::cout << "Width:" << m_window->GetWidth() << "Height:" << m_window->GetHeight() << '\r';

        this->OnUpdate();

        std::this_thread::sleep_for(16ms);
    }
}

void AppFramework::Start()
{
    m_window->Show(true);
    m_window->Maximize(true);
    m_window->Fullscreen(true);

    m_appState.isRunning = true;

    this->OnStart();
}

void AppFramework::Pause(B8 _isPaused)
{
    if (m_appState.isPaused != _isPaused)
    {
        m_appState.isPaused = _isPaused;

        if (_isPaused)
            this->OnPause();
    }
}

void AppFramework::Stop()
{
    m_window->Show(false);

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
#if defined(RK_DEBUG)
    this->AllocateConsole();
#endif

    m_timer = std::make_unique<Core::SyncTimer>();
    m_window = GUI::Window::CreateWindow();
    m_gEngine = Engine::Renderer::CreateRenderer(API_VULKAN);

    GUI::WindowManager::RegisterWindow();

    return true;
}

void AppFramework::Release()
{
#if defined(RK_DEBUG)
    this->ReleaseConsole();
#endif

    GUI::WindowManager::UnregisterAllWindows();
}

} // namespace Rake::Application
