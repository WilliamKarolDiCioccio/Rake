#include "pch.hpp"

#include "platform/vulkan/vulkan_swapchain.hpp"

namespace Rake::platform::Vulkan {

void CreateVulkanSwapchain(
    VulkanSwapchain& _swapchain,
    const VulkanDevice& _device,
    const VulkanSurface& _surface,
    const glm::uvec2& _renderTargetSize) {
    _swapchain.device = _device.device;

    SwapChainSupportDetails swapChainSupport =
        FindVulkanDeviceSwapChainSupport(_device.physicalDevice, _surface.surface);

    _swapchain.format = ChooseSwapSurfaceFormat(swapChainSupport.formats);
    _swapchain.presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
    _swapchain.extent = ChooseSwapExtent(swapChainSupport.capabilities, _renderTargetSize);

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
    createInfo.imageFormat = _swapchain.format.format;
    createInfo.imageColorSpace = _swapchain.format.colorSpace;
    createInfo.imageExtent = _swapchain.extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    createInfo.presentMode = _swapchain.presentMode;

    QueueFamilySupportDetails queueSupportDetails =
        FindVulkanDeviceQueueFamiliesSupport(_device.physicalDevice, _surface.surface);

    uint32_t queueFamilyIndices[] = {
        queueSupportDetails.graphicsFamily.value(),
        queueSupportDetails.presentFamily.value(),
    };

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
    createInfo.oldSwapchain = nullptr;

    if (vkCreateSwapchainKHR(_swapchain.device, &createInfo, nullptr, &_swapchain.swapchain) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan swapchain!");
    }

    vkGetSwapchainImagesKHR(_swapchain.device, _swapchain.swapchain, &imageCount, nullptr);
    _swapchain.images.resize(imageCount);
    vkGetSwapchainImagesKHR(_swapchain.device, _swapchain.swapchain, &imageCount, _swapchain.images.data());

    CreateImageViews(_swapchain);
}

void DestroyVulkanSwapchain(VulkanSwapchain& _swapchain) {
    DestroyImageViews(_swapchain);
    vkDestroySwapchainKHR(_swapchain.device, _swapchain.swapchain, nullptr);
}

void CreateImageViews(VulkanSwapchain& _swapchain) {
    _swapchain.imageViews.resize(_swapchain.images.size());

    for (size_t i = 0; i < _swapchain.images.size(); i++) {
        VkImageViewCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.pNext = nullptr;
        createInfo.flags = 0;
        createInfo.image = _swapchain.images[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = _swapchain.format.format;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        if (vkCreateImageView(_swapchain.device, &createInfo, nullptr, &_swapchain.imageViews[i]) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create Vulkan image views!");
        }
    }
}

void DestroyImageViews(VulkanSwapchain& _swapchain) {
    for (size_t i = 0; i < _swapchain.imageViews.size(); i++) {
        vkDestroyImageView(_swapchain.device, _swapchain.imageViews[i], nullptr);
    }
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

VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& _capabilities, const glm::uvec2& _renderTargetSize) {
    if (_capabilities.currentExtent.width != UINT32_MAX) {
        return _capabilities.currentExtent;
    } else {
        VkExtent2D actualExtent = {_renderTargetSize.x, _renderTargetSize.y};

        actualExtent.width =
            std::clamp(actualExtent.width, _capabilities.minImageExtent.width, _capabilities.maxImageExtent.width);
        actualExtent.height =
            std::clamp(actualExtent.height, _capabilities.minImageExtent.height, _capabilities.maxImageExtent.height);

        return actualExtent;
    }
}

}  // namespace Rake::platform::Vulkan
