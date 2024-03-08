#pragma once

#include "vulkan_common.hpp"

#include "vulkan_instance.hpp"

namespace Rake::platform::Vulkan {

struct VulkanSurface {
    VkSurfaceKHR surface;

    VulkanSurface() : surface(nullptr) {}
};

void CreateVulkanSurface(VulkanSurface& _surface, const VulkanInstance& _instance, void* _windowHandle);

void DestroyVulkanSurface(VulkanSurface& _surface, const VulkanInstance& _instance);

}  // namespace Rake::platform::Vulkan
