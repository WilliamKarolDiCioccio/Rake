#pragma once

#if defined(DESKTOP_DEVICE) == 1

#include "Core/Base.hpp"

namespace Rake::GUI
{

struct Monitor
{
};

class MonitorManager
{
  public:
    MonitorManager() = default;

  public:
    virtual void *EnumerateMonitors() = 0;
};

} // namespace Rake::GUI

#endif
