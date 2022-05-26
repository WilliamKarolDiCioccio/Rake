#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <mutex>
#include <RkBase/RkMain.h>

#include "Common.def.h"

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

    Rake::Core::LogManager logManager;

    logManager.Init();

    ATTACH_CONSOLE_PROFILE;

    Rake::Core::AppInfo appInfo = {IS_CHEAT_MODE, L"🛏️Testbed🛏️"};

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

    logManager.Release();

#if defined(PLATFORM_WINDOWS)
    if (hMutex != NULL)
        ReleaseMutex(hMutex);
#endif

    return EXIT_SUCCESS;
}
