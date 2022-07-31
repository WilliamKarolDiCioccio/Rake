#include "RkPch.h"

#if defined(DESKTOP_DEVICE)

#include "Window.hpp"

#if defined(PLATFORM_WINDOWS)
#include "Platform/Windows/Win32Window.hpp"
#endif

namespace Rake::GUI
{

std::unique_ptr<Window> WindowManager::CreateNativeView()
{
#if defined(PLATFORM_WINDOWS)
    return std::make_unique<Win32::Win32Window>();
#endif
}

} // namespace Rake::GUI

#endif
