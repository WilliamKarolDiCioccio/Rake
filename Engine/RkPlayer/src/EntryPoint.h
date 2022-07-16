#pragma once

#include <iostream>
#include <RkSTL/Main.h>

#include "Core/Base.hpp"
#include "Tools/Assert.h"
#include "Tools/Log.hpp"
#include "Core/RkException.hpp"
#include "Application/AppFramework.hpp"

extern Rake::Application::AppFramework *RkCreateApplication();

#if defined(PLATFORM_WINDOWS) == 1
#include <shellapi.h>
#endif

void ParseCmdLineArgs(Rake::Application::AppData &_appData)
{
    int argc = __argc;
    wchar_t **argv = __wargv;

#if defined(PLATFORM_WINDOWS)
    argv = ::CommandLineToArgvW(GetCommandLine(), &argc);
#endif

    for (size_t i = 0; i < argc; i++)
    {
        // if (::wcscmp(argv[i], L"") == 0)
        // {
        // }
    }
}

RK_GUI_MAIN()
{
    try
    {
        auto app = RkCreateApplication();

        app->Start();
        app->Update();
        app->Stop();

        delete (app);
    }
    catch (const RkException &e)
    {
    }
    catch (const std::exception &e)
    {
    }
    catch (...)
    {
    }

    return EXIT_SUCCESS;
}
