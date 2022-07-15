/*****************************************************************/ /**
 * \file   Win32App.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Core/Base.hpp"

#if defined(PLATFORM_WINDOWS) == 1

#include <mutex>
#include <processenv.h>
#include <consoleapi.h>

namespace Rake::Platform
{

class Win32App
{
  protected:
    Win32App();
    virtual ~Win32App();

  protected:
    void PumpPlatformMessages() const;
    B8 AllocateConsole();
    B8 ReleaseConsole();

  private:
    B8 RedirectConsoleIO();
};

} // namespace Rake::Platform

#define PLATFORM_APP_FRAMEWORK Rake::Platform::Win32App

#endif
