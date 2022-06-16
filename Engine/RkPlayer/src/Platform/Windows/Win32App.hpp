#pragma once

#if defined(PLATFORM_WINDOWS)

#include <mutex>
#include <processenv.h>
#include <consoleapi.h>

#include "Types.h"

namespace Rake::Windows
{

class Win32App
{
  public:
    HANDLE hMutex;
    DWORD processId;

  protected:
    Win32App();
    ~Win32App();

  protected:
    void PumpPlatformMessages();
};

} // namespace Rake::Windows

#define PLATFORM_APP_FRAMEWORK Rake::Windows::Win32App

#endif
