#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <RkBase/RkMain.h>

#include "Common.h"

#include "Core/Tools/Log.inl.hpp"
#include "Core/Tools/Console.inl.hpp"
#include "Core/Error/RkException.hpp"
#include "Core/RkApplication/AppFramework.hpp"

extern Rake::Core::AppFramework *RkCreateApplication(const char *_appName, Rake::Core::ApplicationMode _mode);

RK_GUI_MAIN()
{
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(DEFAULT_LOG_FILE_NAME, MEBIBYTES(1), LOG_FILES_PER_SESSION, false));
    auto logger = Rake::Core::RkLogManager::Init(sinks);

    // ATTACH_CONSOLE_PROFILE;

    try
    {
        auto app = RkCreateApplication("Testbed", IS_CHEAT_MODE);

        app->Start();
        app->Update();
        app->Stop();

        delete (app);
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

    // DETACH_CONSOLE_PROFILE;

    Rake::Core::RkLogManager::Release();

    return EXIT_SUCCESS;
}
