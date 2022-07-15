/*****************************************************************/ /**
 * \file   DisableWarnings.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   July 2022
 *********************************************************************/

#include "Detection.h"

#if defined(COMPILER_MSVC) == 1
__pragma(warning(push, 0))
#elif defined(COMPILER_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#elif defined(COMPILER_GCC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignore "-w"
#endif
