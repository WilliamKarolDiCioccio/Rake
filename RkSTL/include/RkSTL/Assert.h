/*****************************************************************/ /**
 * \file   Assert.inl.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   April 2022
 *********************************************************************/

#pragma once

#include "internal/Detection.h"

#if !defined(RK_DEBUG_BREAK)
#if defined(PLATFORM_WINDOWS)
#include <intrin.h>
#define RK_DEBUG_BREAK __debugbreak()
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_APPLE)
#include <unistd.h>
#include <signal.h>
#define RK_DEBUG_BREAK exit(SIGTRAP)
#else
#define RK_DEBUG_BREAK "(unknown debugbreak)"
#endif
#endif

#if !defined(RK_CURRENT_FUNCTION)
#if defined(COMPILER_MSVC)
#define RK_CURRENT_FUNCTION __func__
#elif defined(COMPILER_CLANG) || defined(COMPILER_GCC)
#define RK_CURRENT_FUNCTION __PRETTY_FUNCTION__
#endif
#else
#define RK_CURRENT_FUNCTION "(unknow function)"
#endif

#define RK_STATIC_ASSERT(cnd) static_assert(cnd, "Static assert failed: " #cnd)

#define RK_ASSERT(cnd)                                                                                                                                                                                                          \
    if (!cnd)                                                                                                                                                                                                                   \
    {                                                                                                                                                                                                                           \
        RK_DEBUG_BREAK;                                                                                                                                                                                                         \
    }
