/*****************************************************************/ /**
 * \file   RkSignal.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   April 2022
 *********************************************************************/

#pragma once

#include <signal.h>
#include <process.h>

#include "Common.h"

namespace Rake::Core
{

class RkSignalHandler final
{
  public:
    static inline void RaiseInterrupt(U32 _signum)
    {
        exit(_signum);
    }
};

#define RK_SIGINT  Core::RkSignalHandler::RaiseInterrupt(SIGINT);
#define RK_SIGILL  Core::RkSignalHandler::RaiseInterrupt(SIGILL)
#define RK_SIGFPE  Core::RkSignalHandler::RaiseInterrupt(SIGFPE)
#define RK_SIGSEGV Core::RkSignalHandler::RaiseInterrupt(SIGSEGV)
#define RK_SIGTERM Core::RkSignalHandler::RaiseInterrupt(SIGTERM)
#define RK_SIGABRT Core::RkSignalHandler::RaiseInterrupt(SIGABRT)

} // namespace Rake::Core
