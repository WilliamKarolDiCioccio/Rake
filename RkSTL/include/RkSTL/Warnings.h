/*****************************************************************/ /**
 * \file   Warnings.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   July 2022
 *********************************************************************/

#pragma once

#include "internal/Detection.h"

#if defined(COMPILER_MSVC) == 1
#define DISABLE_ALL_WARNINGS __pragma(warning(push, 0))
#define RESTORE_ALL_WARNINGS __pragma(warning(pop))
#else
#define DISABLE_ALL_WARNINGS (void)0;
#define RESTORE_ALL_WARNINGS (void)0;
#endif
