#include "src/RkPch.hpp"

#include "Core/Application/AppFramework.hpp"

namespace Rake::Core
{

AppFramework *AppFramework::m_appInstance = nullptr;

AppFramework::AppFramework(const AppInfo &_startupInfo)
{
    if (AppFramework::m_appInstance == nullptr)
    {
        AppFramework::m_appInstance = this;

        m_appInstance = this;
        RK_ASSERT(m_appInstance);

        if (_startupInfo.mode >= Mode::IsGameMode)
        {
        }
        else if (_startupInfo.mode == Mode::IsCheatMode)
        {
        }
        else if (_startupInfo.mode == Mode::IsEditorMode)
        {
        }
        else if (_startupInfo.mode == Mode::IsTerminalMode)
        {
        }

        if (!this->Init())
            throw RkException("Unable to acquire resources", __FILE__, __LINE__, APPLICATION_LAYER, RESOURCE_ACQUIREMENT_TYPE);
    }
    else
        throw RkException("Attempt to create a second application", __FILE__, __LINE__, APPLICATION_LAYER, TYPE_NONE);
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
    m_window->ShouldShow(false);
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
