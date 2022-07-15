#pragma once

#if defined(DESKTOP_DEVICE) == 1

#include "Core/Base.hpp"
#include "Core/Config.h"

#include "Window.hpp"

namespace Rake::GUI
{

class WindowManager final
{
  private:
    WindowManager() = default;

  public:
    static B8 RegisterWindow();
    static void UnregisterWindow();
    static void UnregisterAllWindows();
};

} // namespace Rake::GUI

#endif
