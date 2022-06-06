#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <mutex>
#include <RkBase/RkMain.h>

#include "Types.h"

#include "Core/Tools/Log.inl.hpp"
#include "Core/Tools/Console.inl.hpp"
#include "Core/Errors/RkException.hpp"
#include "Core/Application/AppFramework.hpp"

extern Rake::Core::AppFramework *RkCreateApplication(const Rake::Core::AppInfo _info);

RK_GUI_MAIN()
{
#if defined(PLATFORM_WINDOWS)
    HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, NULL, L"RakeInstance");

    if (hMutex == NULL)
        hMutex = CreateMutex(NULL, NULL, L"RakeInstance");
    else
        return EXIT_FAILURE;
#endif

    std::vector<spdlog::sink_ptr> m_sinks;

    Rake::Core::LogManager::Init(m_sinks);

    ATTACH_CONSOLE_PROFILE;

    Rake::Core::AppInfo appInfo = {IS_CHEAT_MODE, L"Testbed", NULL, NULL};

    try
    {
        auto app = RkCreateApplication(appInfo);

        app->Start();
        app->Update();
        app->Stop();

        delete app;
    }
    catch (const Rake::Core::RkException &e)
    {
    }
    catch (const std::exception &e)
    {
    }
    catch (...)
    {
    }

    DETACH_CONSOLE_PROFILE;

    Rake::Core::LogManager::Release();

#if defined(PLATFORM_WINDOWS)
    if (hMutex != NULL)
        ReleaseMutex(hMutex);
#endif

    return EXIT_SUCCESS;
}
