#include "src/RkPch.h"

#if defined(PLATFORM_WINDOWS) == 1

#include <cstdio>

#include "Win32App.hpp"

namespace Rake::Platform
{

Win32App::Win32App()
{
    HANDLE mutex = OpenMutex(MUTEX_ALL_ACCESS, NULL, L"RakeInstance");

    if (mutex != NULL)
    {
        MessageBox(NULL, L"Another instance of rake is running!", L"Error", MB_OK);
        RK_SIGTERM;
    }
    else
        mutex = CreateMutex(NULL, NULL, L"RakeInstance");
}

Win32App::~Win32App()
{
    HANDLE mutex = OpenMutex(MUTEX_ALL_ACCESS, NULL, L"RakeInstance");

    if (mutex != NULL)
        ::ReleaseMutex(mutex);
}

void Win32App::PumpPlatformMessages() const
{
    MSG msg;

    if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
    {
        ::TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

B8 Win32App::AllocateConsole()
{
    this->ReleaseConsole();

    if (!::AllocConsole())
        return false;

    if (!this->RedirectConsoleIO())
        return false;

    return true;
}

B8 Win32App::RedirectConsoleIO()
{
    FILE *filePointer;

    if (::GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE)
        if (::freopen_s(&filePointer, "CONIN$", "r", stdin) != NULL)
            return false;
        else
            ::setvbuf(stdin, NULL, _IONBF, 0);

    if (::GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE)
        if (::freopen_s(&filePointer, "CONOUT$", "w", stdout) != NULL)
            return false;
        else
            ::setvbuf(stdout, NULL, _IONBF, 0);

    if (::GetStdHandle(STD_ERROR_HANDLE) != INVALID_HANDLE_VALUE)
        if (::freopen_s(&filePointer, "CONOUT$", "w", stderr) != NULL)
            return false;
        else
            ::setvbuf(stderr, NULL, _IONBF, 0);

    std::ios::sync_with_stdio(true);

    std::wcout.clear();
    std::cout.clear();
    std::wcerr.clear();
    std::cerr.clear();
    std::wcin.clear();
    std::cin.clear();

    return true;
}

B8 Win32App::ReleaseConsole()
{
    FILE *fp;

    if (freopen_s(&fp, "NUL:", "r", stdin) != 0)
        return false;
    else
        setvbuf(stdin, NULL, _IONBF, 0);

    if (freopen_s(&fp, "NUL:", "w", stdout) != 0)
        return false;
    else
        setvbuf(stdout, NULL, _IONBF, 0);

    if (freopen_s(&fp, "NUL:", "w", stderr) != 0)
        return false;
    else
        setvbuf(stderr, NULL, _IONBF, 0);

    if (!FreeConsole())
        return false;

    return true;
}

} // namespace Rake::Platform

#endif
