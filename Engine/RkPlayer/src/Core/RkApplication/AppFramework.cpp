#include "RkPch.hpp"

#include "Core/RkApplication/AppFramework.hpp"

namespace Rake::Core
{

AppFramework *AppFramework::m_appInstance = nullptr;

AppFramework::AppFramework(const char *_appName, ApplicationMode _mode)
{
    if (AppFramework::m_appInstance == nullptr)
    {
        AppFramework::m_appInstance = this;

        m_appInstance = this;
        RK_ASSERT(m_appInstance);

        if (_mode >= ApplicationMode::IsGameMode)
        {
        }
        else if (_mode == ApplicationMode::IsCheatMode)
        {
        }
        else if (_mode == ApplicationMode::IsEditorMode)
        {
        }
        else
        {
            throw RkException("Invalid application command line arguments", __FILE__, __LINE__);
        }

        if (!this->Init())
        {
            throw std::runtime_error("Unable to acquire resources");
        }

        RK_BIND_ON_EVENT(Stop())
    }
    else
    {
        throw std::runtime_error("Attempt to create a second application");
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
    while (isRunning)
    {
        if (isPaused)
        {
            this->OnPause();
        }
        else
        {
            this->OnUpdate();

            m_timer->Tick(60);
#if defined(DESKTOP_DEVICE) == 1
            m_window->Refresh();
#elif defined(MOBILE_DEVICE) == 1
            m_surface->Refresh();
#endif
        }

        std::this_thread::sleep_for(16ms);
    }
}

void AppFramework::Start()
{
    this->OnStart();

#if defined(DESKTOP_DEVICE) == 1
    m_window->ShouldShow(true);
#endif

    isRunning = true;
}

void AppFramework::Pause()
{
    isPaused = true;
}

void AppFramework::Stop()
{
    this->OnStop();

#if defined(DESKTOP_DEVICE) == 1
    m_window->ShouldShow(false);
#endif

    isRunning = false;
}

AppFramework *AppFramework::RetriveInstance()
{
    if (AppFramework::m_appInstance != nullptr)
    {
        return AppFramework::m_appInstance;
    }
}

bool AppFramework::Init()
{
    m_timer = new SyncTimer(1.0f);
#if defined(DESKTOP_DEVICE) == 1
    m_window = GUI::Window::CreateNativeWindow(1280, 720, 480, 480, "Rake", IS_WINDOWED);
#elif defined(MOBILE_DEVICE) == 1
    m_surface = GUI::Surface::CreateNativeSurface();
#endif

    return true;
}

void AppFramework::Release()
{
    delete (m_timer);
#if defined(DESKTOP_DEVICE) == 1
    delete (m_window);
#elif defined(MOBILE_DEVICE) == 1
    delete (m_surface);
#endif

    RK_ASSERT(!m_timer);
#if defined(DESKTOP_DEVICE) == 1
    RK_ASSERT(!m_window);
#elif defined(MOBILE_DEVICE) == 1
    RK_ASSERT(!m_surface);
#endif
}

} // namespace Rake::Core
