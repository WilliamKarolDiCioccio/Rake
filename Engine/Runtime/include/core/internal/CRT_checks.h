#pragma once

#include "config.h"

#if RK_CRT_CHECKS_ENABLED

#include <crtdbg.h>

#include "Assert.h"

#if defined(COMPILER_MSVC)
#define RK_MEMORY_INTEGRITY_NOTIFY _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)

#define RK_MEMORY_INTEGRITY_CHECK   \
    if (!(bool)_CrtCheckMemory()) { \
        RK_DEBUG_BREAK;             \
                                    \
        abort();                    \
    }

#define RK_DUMP_MEMORY_LEAKS _CrtDumpMemoryLeaks();
#elif defined(COMPILER_CLANG) || defined(COMPILER_GCC)
#define RK_MEMORY_INTEGRITY_NOTIFY
#define RK_MEMORY_INTEGRITY_CHECK
#define RK_DUMP_MEMORY_LEAKS
#else
#error "Unknown or not supported compiler toolchain!"
#endif

#else

#define RK_MEMORY_INTEGRITY_NOTIFY
#define RK_MEMORY_INTEGRITY_CHECK
#define RK_DUMP_MEMORY_LEAKS

#endif
