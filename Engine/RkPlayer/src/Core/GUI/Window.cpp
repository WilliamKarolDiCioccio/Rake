#include "src/RkPch.hpp"

#include "Types.h"

#if defined(DESKTOP_DEVICE) == RK_TRUE

#include "Core/GUI/Window.hpp"

#if defined(PLATFORM_WINDOWS)
#include "platform/Windows/Win32Window.hpp"
#elif defined(PLATFORM_LINUX)
#include "platform/Linux/GLFWWindow.hpp"
#elif defined(PLATFORM_MACOS)
#include "Platform/MacOS/CocoaWindow.hpp"
#endif

namespace Rake::Core
{

std::unique_ptr<Window> Window::CreateNativeWindow()
{
#if defined(PLATFORM_WINDOWS)
    return std::make_unique<Windows::Win32Window>();
#elif defined(PLATFORM_LINUX)
    return std::make_unique<Linux::X11Window>();
#elif defined(PLATFORM_MACOS)
    return std::make_unique<Macos::CocoaWindow>();
#endif
}

} // namespace Rake::Core

#endif
