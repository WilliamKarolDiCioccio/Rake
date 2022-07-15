#include "src/RkPch.h"

#if defined(DESKTOP_DEVICE) == RK_TRUE

#include "Window.hpp"

#if defined(PLATFORM_WINDOWS) == 1
#include "Platform/Windows/Win32Window.hpp"
#endif

namespace Rake::GUI
{

std::unique_ptr<Window> Window::CreateWindow()
{
#if defined(PLATFORM_WINDOWS) == 1
    return std::make_unique<Platform::Win32Window>();
#else
#error Unsupported dekstop platform!
#endif
}

} // namespace Rake::GUI

#endif
