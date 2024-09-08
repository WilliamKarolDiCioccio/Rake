#include "pch.hpp"

#define VMA_IMPLEMENTATION
#include <vma/vk_mem_alloc.h>

#include "platform/vulkan/vulkan_allocator.hpp"

namespace Rake::platform::Vulkan {

void CreateVulkanAllocator(
    VmaAllocator& _allocator,
    const VkInstance& _instance,
    const VkPhysicalDevice& _physicalDevice,
    const VkDevice& _device) {
    VmaAllocatorCreateInfo allocatorInfo = {};
    allocatorInfo.instance = _instance;
    allocatorInfo.physicalDevice = _physicalDevice;
    allocatorInfo.device = _device;

    if (vmaCreateAllocator(&allocatorInfo, &_allocator) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan allocator");
    }
}

void DestroyVulkanAllocator(VmaAllocator& _allocator) { vmaDestroyAllocator(_allocator); }

}  // namespace Rake::platform::Vulkan
