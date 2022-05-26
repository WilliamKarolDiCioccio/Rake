/*****************************************************************/ /**
 * \file   Assert.inl.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   April 2022
 *********************************************************************/

#pragma once

#include "Common.def.h"
#include "Core/EngineConfig.def.h"

#if defined(ASSERTIONS_ENABLED) == 1

#if !defined(RK_DEBUG_BREAK)
#if defined(PLATFORM_WINDOWS)
#include <intrin.h>
#define RK_DEBUG_BREAK __debugbreak()
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_APPLE)
#include <unistd.h>
#include "Core/Error/RkSignal.hpp"
#define RK_DEBUG_BREAK exit(SIGTRAP)
#else
#define RK_DEBUG_BREAK "(unknown debugbreak)"
#endif
#endif

#if !defined(RK_CURRENT_FUNCTION)
#if defined(COMPILER_MSVC)
#define RK_CURRENT_FUNCTION __func__
#elif defined()
#define RK_CURRENT_FUNCTION __PRETTY_FUNCTION__
#endif
#else
#define RK_CURRENT_FUNCTION "(unknow function)"
#endif

#define RK_STATIC_ASSERT(cnd) static_assert(cnd, "Static assert failed: " #cnd)

namespace Rake::Core
{

template <typename T> void RkAssert(T _cnd)
{
    if (!_cnd)
    {
        RK_DEBUG_BREAK;
    }
}

} // namespace Rake::Core

#define RK_ASSERT(cnd) Rake::Core::RkAssert(cnd);

#else

#define RK_STATIC_ASSERT(cnd) (void)0
#define RK_ASSERT(cnd)        (void)0

#endif
