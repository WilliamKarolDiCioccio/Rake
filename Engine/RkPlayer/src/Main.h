#pragma once

#include <csignal>
#include <iostream>

#include "Core/Base.hpp"
#include "Tools/Assert.h"
#include "Tools/Log.hpp"
#include "Core/Exception.hpp"
#include "Application/AppFramework.hpp"

void IntHandler(int _signalCode)
{
    exit(_signalCode);
}

void SegHandler(int _signalCode)
{
    exit(_signalCode);
}

extern std::unique_ptr<APP_FRAMEWORK> RkCreateApplication();

#define COMMON_BODY()                                                                                                                                                                                                           \
    {                                                                                                                                                                                                                           \
        ::signal(SIGINT, IntHandler);                                                                                                                                                                                           \
        ::signal(SIGSEGV, SegHandler);                                                                                                                                                                                          \
                                                                                                                                                                                                                                \
        try                                                                                                                                                                                                                     \
        {                                                                                                                                                                                                                       \
            auto g_app = RkCreateApplication();                                                                                                                                                                                 \
            auto g_logger = std::make_unique<Rake::Tools::ConsoleLogger>();                                                                                                                                                     \
                                                                                                                                                                                                                                \
            g_app->Start();                                                                                                                                                                                                     \
            g_app->Update();                                                                                                                                                                                                    \
            g_app->Stop();                                                                                                                                                                                                      \
        }                                                                                                                                                                                                                       \
        catch (const Rake::Core::Exception &e)                                                                                                                                                                                  \
        {                                                                                                                                                                                                                       \
            std::cerr << e.what() << std::endl;                                                                                                                                                                                 \
        }                                                                                                                                                                                                                       \
        catch (const std::exception &e)                                                                                                                                                                                         \
        {                                                                                                                                                                                                                       \
            std::cerr << e.what() << std::endl;                                                                                                                                                                                 \
        }                                                                                                                                                                                                                       \
        catch (...)                                                                                                                                                                                                             \
        {                                                                                                                                                                                                                       \
            std::cerr << "Undefined program behavior" << std::endl;                                                                                                                                                             \
        }                                                                                                                                                                                                                       \
    }

#if defined(PLATFORM_WINDOWS)

#include <windows.h>

#include "Platform/Windows/Win32Utils.hpp"

int WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{

    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;

    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{

    HANDLE mutex = OpenMutex(MUTEX_ALL_ACCESS, NULL, L"RakeInstance");

    if (mutex != NULL)
    {
        MessageBeep(MB_ICONERROR);
        MessageBox(NULL, L"Another instance of rake is running!", L"Error", MB_OK);
        RK_SIGTERM;
    }
    else
        mutex = CreateMutex(NULL, NULL, L"RakeInstance");

#ifdef RK_DEBUG
    Rake::Win32::AllocateConsole(L"RkDebugConsole");
#endif

    COMMON_BODY();

#ifdef RK_DEBUG
    Rake::Win32::ReleaseConsole();
#endif

    mutex = OpenMutex(MUTEX_ALL_ACCESS, NULL, L"RakeInstance");

    if (mutex != NULL)
        ::ReleaseMutex(mutex);

    return EXIT_SUCCESS;
}

#endif
