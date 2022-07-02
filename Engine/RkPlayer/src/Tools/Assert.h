/*****************************************************************/ /**
 * \file   Assert.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   July 2022
 *********************************************************************/

#pragma once

#include "Core/Config.h"

#if defined(ASSERTIONS_ENABLED) == RK_TRUE
#include <RkSTL/Assert.h>
#else
#define RK_STATIC_ASSERT(cnd) (void)0
#define RK_ASSERT(cnd)        (void)0
#endif
