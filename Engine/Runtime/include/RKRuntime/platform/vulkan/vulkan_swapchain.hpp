#pragma once

#include <vector>

#include <glm/vec2.hpp>

#include "vulkan_common.hpp"

#include "vulkan_device.hpp"

#include "core/window_system.hpp"

namespace Rake::platform::Vulkan {

struct VulkanSwapchain {
    VkDevice device;
    VkSwapchainKHR swapchain;
    VkSurfaceFormatKHR format;
    VkPresentModeKHR presentMode;
    VkExtent2D extent;
    std::vector<VkImage> images;
    std::vector<VkImageView> imageViews;
    bool canRequireExclusiveFullscreen;

    VulkanSwapchain()
        : device(nullptr),
          swapchain(nullptr),
          format({}),
          presentMode(),
          extent({}),
          canRequireExclusiveFullscreen(false) {}
};

void CreateVulkanSwapchain(
    VulkanSwapchain& _swapchain,
    const VulkanDevice& _device,
    const VulkanSurface& _surface,
    const std::shared_ptr<core::Window>& _window);

void CreateImageViews(VulkanSwapchain& _swapchain);

void DestroyImageViews(VulkanSwapchain& _swapchain);

void DestroyVulkanSwapchain(VulkanSwapchain& _swapchain);

VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& _availableFormats);

VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& _availablePresentModes);

VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& _capabilities, const glm::uvec2& _rendertargetSize);

VkResult AcquireExclusiveFullscreenMode(VulkanSwapchain& _swapchain);

VkResult ReleaseExclusiveFullscreenMode(VulkanSwapchain& _swapchain);

}  // namespace Rake::platform::Vulkan
