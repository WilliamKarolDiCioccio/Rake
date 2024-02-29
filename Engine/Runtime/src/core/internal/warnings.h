#pragma once

#include "Detection.h"

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#ifdef COMPILER_MSVC
#define RK_DISABLE_WARNINGS __pragma(warning(push, 0))
#define RK_RESTORE_WARNINGS __pragma(warning(pop))
#else
#error "Unknown or not supported compiler toolchain!"
#endif
