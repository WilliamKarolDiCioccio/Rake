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

#include "Types.h"

namespace Rake::Core
{

static inline void RaiseInterrupt(U32 _signum)
{
    exit(_signum);
}

#define RK_SIGINT  Core::RaiseInterrupt(SIGINT);
#define RK_SIGILL  Core::RaiseInterrupt(SIGILL)
#define RK_SIGFPE  Core::RaiseInterrupt(SIGFPE)
#define RK_SIGSEGV Core::RaiseInterrupt(SIGSEGV)
#define RK_SIGTERM Core::RaiseInterrupt(SIGTERM)
#define RK_SIGABRT Core::RaiseInterrupt(SIGABRT)

} // namespace Rake::Core
