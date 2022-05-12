#include "RkPch.hpp"

#include "Core/RkApplication/AppFramework.hpp"

namespace Rake::Core
{

AppFramework::AppFramework(const char *_appName, ApplicationMode _mode)
{
    if (!AppFramework::m_exists)
    {
        AppFramework::m_exists = true;

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
            RK_SIGABRT;
        }

        if (!this->Init())
        {
            throw std::runtime_error("Unable to acquire resources");
            RK_SIGABRT;
        }
    }
    else
    {
        throw std::runtime_error("Attempt to create a second application");
        RK_SIGABRT;
    }
}

AppFramework::~AppFramework()
{
    this->Release();

    delete (m_appInstance);
    RK_ASSERT(!m_appInstance);
}

void AppFramework::Start()
{
    this->OnStart();

#if defined(DESKTOP_DEVICE) == 1
    m_window->ShouldShow(true);
#endif

    m_state.isRunning = true;
}

void AppFramework::Update()
{
    while (m_state.isRunning)
    {
        if (m_state.isPaused)
        {
            this->OnPause();
        }
        else
        {
            this->OnUpdate();

            std::cout << "vavevfauiefi";

            m_syncTimer->Tick();

#if defined(DESKTOP_DEVICE) == 1
            m_window->Refresh();
#elif defined(MOBILE_DEVICE) == 1
            m_surface->Refresh();
#endif
        }

        std::this_thread::sleep_for(16ms);
    }
}

void AppFramework::Stop()
{
    this->OnStop();

#if defined(DESKTOP_DEVICE) == 1
    m_window->ShouldShow(false);
#endif

    m_state.isRunning = false;
}

bool AppFramework::Init()
{
    m_syncTimer = new SyncTimer();
#if defined(DESKTOP_DEVICE) == 1
    m_window = GUI::Window::CreateNativeWindow(1280, 720, 480, 480, "Rake", IS_WINDOWED);
    m_window->MakeCurrent();
#elif defined(MOBILE_DEVICE) == 1
    m_surface = GUI::Surface::CreateNativeSurface();
    m_surface->MakeCurrent();
#endif

    return true;
}

bool AppFramework::Release()
{
    delete (m_syncTimer);
    RK_ASSERT(m_syncTimer);
    delete (m_window);
    RK_ASSERT(m_window);

    return true;
}

} // namespace Rake::Core
