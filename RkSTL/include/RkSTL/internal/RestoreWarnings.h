/*****************************************************************/ /**
 * \file   RestoreWarnings.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   July 2022
 *********************************************************************/

#include "Detection.h"

#if defined(COMPILER_MSVC) == 1
__pragma(warning(pop))
#elif defined(COMPILER_CLANG)
#pragma clang diagnostic pop
#elif defined(COMPILER_GCC)
#pragma GCC diagnostic pop
#endif