#pragma once

#include "config.h"

#if RK_ASSERTIONS_ENABLED

#include "detection.h"

#if defined(COMPILER_MSVC)
#include <intrin.h>
#define RK_DEBUG_BREAK __debugbreak()
#elif defined(COMPILER_CLANG)
#define RK_DEBUG_BREAK __builtin_trap()
#elif defined(COMPILER_GCC)
#define DEBUG_BREAK __builtin_debugtrap()
#else
#error "Unknown or not supported compiler toolchain!"
#endif

#define RK_ASSERT(cnd)        cnd ? void() : RK_DEBUG_BREAK
#define RK_STATIC_ASSERT(cnd) static_assert(cnd, "Static assert failed: " #cnd)

#else

#define RK_STATIC(cnd)
#define RK_STATIC_ASSERT(cnd)

#endif
