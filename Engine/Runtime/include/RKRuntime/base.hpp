#pragma once

#include "RKRuntime/core/internal/config.h"

#include <RKSTL/defines.hpp>

#ifdef PLAYER_EXPORT
// Used for exporting symbols in the player library
#define RK_API DLL_EXPORT
#else
// Used for importing symbols from the player library
#define RK_API DLL_IMPORT
#endif
