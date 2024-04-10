#pragma once

#include "RKRuntime/core/internal/config.h"

#include <RKSTL/defines.hpp>

#ifdef PLAYER_EXPORT
#define RK_API DLL_EXPORT
#else
#define RK_API DLL_IMPORT
#endif
