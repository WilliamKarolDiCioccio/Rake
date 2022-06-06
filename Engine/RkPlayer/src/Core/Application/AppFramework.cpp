#include "src/RkPch.hpp"

#include "Core/Application/AppFramework.hpp"

#include <gl/glew.h>

namespace Rake::Core
{

AppFramework *AppFramework::m_appInstance = nullptr;

AppFramework::AppFramework(const AppInfo &_appInfo)
{
    if (AppFramework::m_appInstance == nullptr)
    {
        AppFramework::m_appInstance = this;

        if (!m_appInstance)
            throw Core::RkException("", __FILE__, __LINE__);

        if (_appInfo.mode >= Mode::IsGameMode)
        {
        }
        else if (_appInfo.mode == Mode::IsCheatMode)
        {
        }
        else if (_appInfo.mode == Mode::IsEditorMode)
        {
        }
        else if (_appInfo.mode == Mode::IsTerminalMode)
        {
        }
        else
        {
            throw RkException("", __FILE__, __LINE__);
        }

        if (!this->Init())
        {
            throw RkException("", __FILE__, __LINE__);
        }
        else
        {
            m_window->SetTitle(_appInfo.appName);
            m_window->SetIcon(_appInfo.iconPath);
            m_window->RkSetCursor(_appInfo.cursorPath);
        }
    }
    else
    {
        throw RkException("", __FILE__, __LINE__);
    }
}

AppFramework::~AppFramework()
{
    this->Release();

    delete (m_appInstance);
    RK_ASSERT(!m_appInstance);
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
            Platform::DispatchMessages();

            m_timer->Tick(60);
#if defined(DESKTOP_DEVICE) == 1
            m_window->Refresh();
#elif defined(MOBILE_DEVICE) == 1
            m_surface->Refresh();
#endif

            this->OnUpdate();
        }

        std::this_thread::sleep_for(16ms);
    }
}

void AppFramework::Start()
{
    this->OnStart();

#if defined(DESKTOP_DEVICE) == 1
    m_window->Show(true);
#endif

    m_isRunning = true;
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
    this->OnStop();

#if defined(DESKTOP_DEVICE) == 1
    m_window->Show(false);
#endif

    m_isRunning = false;
}

AppFramework *AppFramework::GetInstance()
{
    if (AppFramework::m_appInstance != nullptr)
        return AppFramework::m_appInstance;
    else
        return nullptr;
}

bool AppFramework::Init()
{
    m_timer = std::make_unique<SyncTimer>(1.0f);
#if defined(DESKTOP_DEVICE) == 1
    m_window = Window::CreateNativeWindow();
    m_window->MakeCurrentContext();
#elif defined(MOBILE_DEVICE) == 1
    m_surface = GUI::Surface::CreateNativeSurface();
#endif

    return true;
}

void AppFramework::Release()
{
    m_window->DestroyContext();
}

} // namespace Rake::Core
