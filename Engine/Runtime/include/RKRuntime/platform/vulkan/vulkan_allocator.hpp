#pragma once

#include <vma/vk_mem_alloc.h>

#include "vulkan_common.hpp"

namespace Rake::platform::Vulkan {

void CreateVulkanAllocator(
    VmaAllocator& _allocator,
    const VkInstance& _instance,
    const VkPhysicalDevice& _physicalDevice,
    const VkDevice& _device);

void DestroyVulkanAllocator(VmaAllocator& allocator);

}  // namespace Rake::platform::Vulkan
