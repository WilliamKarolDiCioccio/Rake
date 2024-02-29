#pragma once

#include "Config.h"

#if RK_ASSERTIONS_ENABLED

#include "Detection.h"

#ifdef COMPILER_MSVC
#include <intrin.h>
#define RK_DEBUG_BREAK __debugbreak()
#else
#error "Unknown or not supported compiler toolchain!"
#endif

#define RK_ASSERT(cnd)        cnd ? void() : RK_DEBUG_BREAK
#define RK_STATIC_ASSERT(cnd) static_assert(cnd, "Static assert failed: " #cnd)

#else

#define RK_STATIC(cnd)
#define RK_STATIC_ASSERT(cnd)

#endif
