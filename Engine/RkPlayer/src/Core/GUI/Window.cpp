#include "src/RkPch.hpp"

#include "Common.def.h"

#if defined(DESKTOP_DEVICE) == RK_TRUE

#include "Core/GUI/Window.hpp"

#if defined(PLATFORM_WINDOWS)
#include "platform/Windows/Win32Window.hpp"
#elif defined(PLATFORM_LINUX)
#include "platform/Linux/GLFWWindow.hpp"
#elif defined(PLATFORM_MACOS)
#include "Platform/MacOS/CocoaWindow.hpp"
#endif

namespace Rake::GUI
{

Window *Window::CreateNativeWindow(long _width, long _height, long _minWidth, long _minHeight, const char *_title, WindowFlags _flags)
{
#if defined(PLATFORM_WINDOWS)
    return new Windows::Win32Window();
#elif defined(PLATFORM_LINUX)
    return new Linux::X11Window();
#elif defined(PLATFORM_MACOS)
    return new MacOS::CocoaWindow();
#endif
}

} // namespace Rake::GUI

#endif
