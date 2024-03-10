#include "pch.hpp"

#include "platform/vulkan/vulkan_swapchain.hpp"

namespace Rake::platform::Vulkan {

void CreateVulkanSwapchain(VulkanSwapchain& _swapchain, const VulkanDevice& _device, const VulkanSurface& _surface) {
    SwapChainSupportDetails swapChainSupport =
        FindVulkanDeviceSwapChainSupport(_device.physicalDevice, _surface.surface);

    VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities, 0, 0);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.pNext = nullptr;
    createInfo.flags = 0;
    createInfo.surface = _surface.surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    createInfo.presentMode = presentMode;

    QueueFamilySupportDetails queueSupportDetails =
        FindVulkanDeviceQueueFamiliesSupport(_device.physicalDevice, _surface.surface);

    uint32_t queueFamilyIndices[] = {
        queueSupportDetails.graphicsFamily.value(),
        queueSupportDetails.presentFamily.value()};

    if (queueSupportDetails.graphicsFamily != queueSupportDetails.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    }

    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = _swapchain.oldSwapchain;

    if (vkCreateSwapchainKHR(_device.device, &createInfo, nullptr, &_swapchain.swapchain) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan swapchain!");
    }
}

void DestroyVulkanSwapchain(VulkanSwapchain& _swapchain, const VulkanDevice& _device) {
    vkDestroySwapchainKHR(_device.device, _swapchain.swapchain, nullptr);
}

VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& _availableFormats) {
    auto it = std::find_if(_availableFormats.begin(), _availableFormats.end(), [](const VkSurfaceFormatKHR& _format) {
        return _format.format == VK_FORMAT_B8G8R8A8_SRGB && _format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    });

    if (it != _availableFormats.end()) {
        return *it;
    }

    return _availableFormats[0];
}

VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& _availablePresentModes) {
    if (std::find(_availablePresentModes.begin(), _availablePresentModes.end(), VK_PRESENT_MODE_MAILBOX_KHR) !=
        _availablePresentModes.end()) {
        return VK_PRESENT_MODE_MAILBOX_KHR;
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& _capabilities, uint32_t _width, uint32_t _height) {
    if (_capabilities.currentExtent.width != UINT32_MAX) {
        return _capabilities.currentExtent;
    } else {
        VkExtent2D actualExtent = {_width, _height};

        actualExtent.width = std::min(
            _capabilities.minImageExtent.width,
            std::min(_capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(
            _capabilities.minImageExtent.height,
            std::min(_capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }
}

}  // namespace Rake::platform::Vulkan
