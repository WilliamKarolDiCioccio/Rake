#pragma once

#include <vector>

#include "vulkan_common.hpp"

#include "vulkan_device.hpp"

namespace Rake::platform::Vulkan {

struct VulkanSwapchain {
    VkDevice device;
    VkPhysicalDevice physicalDevice;
    VkSurfaceKHR surface;
    VkSwapchainKHR swapchain;
    VkSwapchainKHR oldSwapchain;
    VkSurfaceFormatKHR format;
    VkExtent2D extent;
    std::vector<VkImage> images;
    std::vector<VkImageView> imageViews;

    VulkanSwapchain()
        : device(nullptr),
          physicalDevice(nullptr),
          surface(nullptr),
          swapchain(nullptr),
          oldSwapchain(nullptr),
          format({}),
          extent({}) {}
};

void CreateVulkanSwapchain(VulkanSwapchain& _swapchain, const VulkanDevice& _device, const VulkanSurface& _surface);

void DestroyVulkanSwapchain(VulkanSwapchain& _swapchain, const VulkanDevice& _device);

VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& _availableFormats);

VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& _availablePresentModes);

VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& _capabilities, uint32_t _width, uint32_t _height);

}  // namespace Rake::platform::Vulkan
