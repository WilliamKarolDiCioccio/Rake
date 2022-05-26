#pragma once

#include "Common.def.h"

#if defined(RK_DEBUG) && defined(DESKTOP_DEVICE)

namespace Rake::Core
{

#if defined(PLATFORM_WINDOWS)
#include <consoleapi.h>
#endif

#include "Core/Tools/Assert.inl.hpp"

static class RkConsoleManager final
{
  public:
    static inline void CreateConsole()
    {
        B8 created = false;
        B8 attached = false;

        if (!created)
            created = AllocConsole();
        if (!attached)
            attached = AttachConsole(ATTACH_PARENT_PROCESS);

        CreateConsoleScreenBuffer(GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
        SetConsoleTitle(L"RkDebugConsole");
    }

    static inline void DestroyConsole()
    {
        FreeConsole();
    }
};

} // namespace Rake::Core

#define ATTACH_CONSOLE_PROFILE Rake::Core::RkConsoleManager::CreateConsole();
#define DETACH_CONSOLE_PROFILE Rake::Core::RkConsoleManager::DestroyConsole();

#else

#define ATTACH_CONSOLE_PROFILE
#define DETACH_CONSOLE_PROFILE

#endif
