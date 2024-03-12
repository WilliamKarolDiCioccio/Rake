#pragma once

#include "detection.h"

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#if defined(COMPILER_MSVC)
#define RK_DISABLE_WARNINGS __pragma(warning(push, 0))
#define RK_RESTORE_WARNINGS __pragma(warning(pop))
#elif defined(COMPILER_CLANG)
#define RK_DISABLE_WARNINGS _Pragma("clang diagnostic push") \
                            _Pragma("clang diagnostic ignored \"-Wall\"")
#define RK_RESTORE_WARNINGS _Pragma("clang diagnostic pop")
#elif defined(COMPILER_GCC)
#define RK_DISABLE_WARNINGS _Pragma("GCC diagnostic push") \
                            _Pragma("GCC diagnostic ignored \"-Wall\"")
#define RK_RESTORE_WARNINGS _Pragma("GCC diagnostic pop")
#else
#error "Unknown or not supported compiler toolchain!"
#endif
