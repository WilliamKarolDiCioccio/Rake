#pragma once

#include <windows.h>
#include <windowsx.h>

#include "Types.h"

namespace Rake::Platform
{

static inline void DispatchMessages()
{
    MSG msg;

    if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

} // namespace Rake::Platform
