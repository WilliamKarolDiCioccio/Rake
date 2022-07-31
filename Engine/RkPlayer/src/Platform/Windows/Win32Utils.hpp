#pragma once

#include "Core/Internal/Detection.h"

#if defined(PLATFORM_WINDOWS)

#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <stdio.h>
#include <iostream>

#include "Core/Base.hpp"

namespace Rake::Win32
{

static inline B8 ReleaseConsole()
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

static inline B8 RedirectConsoleIO()
{
    FILE *fp;

    if (::GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE)
        if (::freopen_s(&fp, "CONIN$", "r", stdin) != NULL)
            return false;
        else
            ::setvbuf(stdin, NULL, _IONBF, 0);

    if (::GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE)
        if (::freopen_s(&fp, "CONOUT$", "w", stdout) != NULL)
            return false;
        else
            ::setvbuf(stdout, NULL, _IONBF, 0);

    if (::GetStdHandle(STD_ERROR_HANDLE) != INVALID_HANDLE_VALUE)
        if (::freopen_s(&fp, "CONOUT$", "w", stderr) != NULL)
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

static inline B8 AllocateConsole(const wchar_t *_title)
{
    ReleaseConsole();

    if (!::AllocConsole())
        return false;

    if (!RedirectConsoleIO())
        return false;

    SetConsoleTitle(_title);

    return true;
}

} // namespace Rake::Win32

#endif
