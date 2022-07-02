#include "src/RkPch.h"

#include "AppFramework.hpp"

namespace Rake::Application
{

AppFramework *AppFramework::m_appInstance = nullptr;

AppFramework::AppFramework(const AppInfo _appInfo)
{
    if (!m_appInstance)
    {
        m_appInstance = this;

        if (!m_appInstance)
            throw Core::Error::RkException("", __FILE__, __LINE__);

        if (_appInfo.mode == IS_GAME_MODE)
        {
        }
        else if (_appInfo.mode == IS_CHEAT_MODE)
        {
        }
        else if (_appInfo.mode == IS_EDITOR_MODE)
        {
        }
        else if (_appInfo.mode == IS_TERMINAL_MODE)
        {
        }
        else
        {
            throw Core::Error::RkException("Unrecognized applicaton mode!", __FILE__, __LINE__);
        }

        if (!this->Init())
        {
            throw Core::Error::RkException("Cannot init members!", __FILE__, __LINE__);
        }
        else
        {
            m_timer->SetTimescale(1.0f);
            m_window->SetTitle(_appInfo.appName);
            m_window->SetIcon(_appInfo.iconPath);
            m_window->RkSetCursor(_appInfo.cursorPath);
        }
    }
    else
    {
        throw Core::Error::RkException("Application instance already created!", __FILE__, __LINE__);
    }
}

AppFramework::~AppFramework()
{
    this->Release();

    delete (m_appInstance);
}

void AppFramework::Update()
{
    while (m_isRunning)
    {
        if (m_isPaused)
        {
            this->OnPause();
        }
        else
        {
            this->PumpPlatformMessages();

            m_timer->Tick();
            m_window->Refresh();

            this->OnUpdate();
        }

        std::this_thread::sleep_for(m_sleep);
    }
}

void AppFramework::Start()
{
    m_window->Show(true);

    m_isRunning = true;

    this->OnStart();
}

void AppFramework::Pause()
{
    if (m_isPaused != true)
        m_isPaused = true;
    else
        m_isPaused = false;
}

void AppFramework::Stop()
{
    m_window->Show(false);

    m_isRunning = false;

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
    m_timer = std::make_unique<Core::Timer::SyncTimer>();
    m_window = GUI::Window::CreateWindow();
    m_gEngine = Engine::Graphics::Renderer::CreateRenderer();

    return true;
}

void AppFramework::Release()
{
}

} // namespace Rake::Application
