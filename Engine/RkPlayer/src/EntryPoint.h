#pragma once

#include <iostream>
#include <RkSTL/Main.h>

#include "Core/Base.hpp"
#include "Tools/Assert.h"
#include "Tools/Log.hpp"
#include "Core/Error/RkException.hpp"
#include "Application/AppFramework.hpp"

extern Rake::Application::AppFramework *RkCreateApplication();

RK_GUI_MAIN()
{
    Rake::Tools::RkLogManager::Init();

    auto app = RkCreateApplication();

    try
    {
        app->Start();
        app->Update();
        app->Stop();
    }
    catch (const Rake::Core::Error::RkException e)
    {
        std::wcout << e.what() << std::endl;
    }
    catch (const std::exception e)
    {
        std::wcout << e.what() << std::endl;
    }
    catch (...)
    {
        ERROR("Undefined program behavior");
    }

    delete app;

    Rake::Tools::RkLogManager::Release();

    return EXIT_SUCCESS;
}
