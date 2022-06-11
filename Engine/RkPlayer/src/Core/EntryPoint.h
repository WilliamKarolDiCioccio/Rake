#pragma once

#include <RkBase/RkMain.h>

#include "Types.h"

#include "Core/Tools/Log.hpp"
#include "Core/Errors/RkException.hpp"
#include "Core/Application/AppFramework.hpp"

extern Rake::Core::AppFramework *RkCreateApplication();

RK_GUI_MAIN()
{
    Rake::Core::RkLogManager::Init();

    auto app = RkCreateApplication();

    try
    {
        app->Start();
        app->Update();
        app->Stop();
    }
    catch (const Rake::Core::RkException e)
    {
        printf(e.what(), '\n');
    }
    catch (const std::exception e)
    {
        printf(e.what()), '\n';
    }
    catch (...)
    {
        ERROR("Undefined program behavior");
    }

    delete app;

    Rake::Core::RkLogManager::Release();

    return EXIT_SUCCESS;
}
