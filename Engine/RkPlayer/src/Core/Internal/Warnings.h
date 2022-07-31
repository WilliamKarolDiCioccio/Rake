/*****************************************************************/ /**
 * \file   Warnings.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   July 2022
 *********************************************************************/

#pragma once

#include "Core/Internal/Detection.h"

#if defined(COMPILER_MSVC) == 1
#define DISABLE_WARNINGS __pragma(warning(push, 0))
#define RESTORE_WARNINGS __pragma(warning(pop))
#elif defined(COMPILER_CLANG)
#define DISABLE_WARNINGS #pragma clang diagnostic push #pragma clang diagnostic ignored "-Weverything"
#define RESTORE_WARNINGS #pragma clang diagnostic pop
#elif defined(COMPILER_GCC)
#define DISABLE_WARNINGS #pragma GCC diagnostic push #pragma GCC diagnostic ignore "-w"
#define RESTORE_WARNINGS #pragma GCC diagnostic pop
#endif
