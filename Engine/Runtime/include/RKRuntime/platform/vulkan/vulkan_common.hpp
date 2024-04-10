#pragma once

#define VK_NO_PROTOTYPES
#ifdef PLATFORM_WINDOWS
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#include <vulkan/vulkan.h>
#include <Volk/volk.h>
#ifdef PLATFORM_WINDOWS
#include "platform/win32/win32_common.hpp"
#include <vulkan/vulkan_win32.h>
#endif

namespace Rake::platform {}  // namespace Rake::platform
