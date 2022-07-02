/*****************************************************************/ /**
 * \file   Win32App.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#if defined(PLATFORM_WINDOWS) == 1

#include <mutex>
#include <processenv.h>
#include <consoleapi.h>

namespace Rake::Platform::Windows
{

class Win32App
{
  protected:
    Win32App();
    virtual ~Win32App();

  protected:
    void PumpPlatformMessages();

  private:
    B8 CheckMutex();
};

} // namespace Rake::Platform::Windows

#define PLATFORM_APP_FRAMEWORK Rake::Platform::Windows::Win32App

#endif
