#pragma once

#include "Common.h"

#if defined(RK_DEBUG) && defined(DESKTOP_DEVICE)

namespace Rake::Core
{

#if defined(PLATFORM_WINDOWS)
#include <consoleapi.h>
#endif

#include "Core/Tools/Assert.inl.h"

static class RkConsoleManager final
{
  public:
    static inline void CreateConsole()
    {
        B8 created = false;
        B8 attached = false;

#if defined(PLATFORM_WINDOWS)
        if (!created)
            created = AllocConsole();
        if (!attached)
            attached = AttachConsole(ATTACH_PARENT_PROCESS);
#endif
    }

    static inline void DestroyConsole()
    {
#if defined(PLATFORM_WINDOWS)
        FreeConsole();
#endif
    }
};

} // namespace Rake::Core

#define ATTACH_CONSOLE_PROFILE Rake::Core::RkConsoleManager::CreateConsole();
#define DETACH_CONSOLE_PROFILE Rake::Core::RkConsoleManager::DestroyConsole();

#else

#define ATTACH_CONSOLE_PROFILE
#define DETACH_CONSOLE_PROFILE

#endif
