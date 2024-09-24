#pragma once

#include "vulkan_common.hpp"
#include "vulkan_instance.hpp"
#include "vulkan_surface.hpp"

namespace Rake::platform::Vulkan {

struct QueueFamilySupportDetails {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool IsComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;

    SwapChainSupportDetails() = default;

    bool IsComplete() { return !formats.empty() && !presentModes.empty(); }
};

struct VulkanDevice {
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    std::vector<const char*> requiredExtensions;
    std::vector<const char*> optionalExtensions;
    std::vector<const char*> availableExtensions;
    std::vector<const char*> requiredLayers;
    std::vector<const char*> availableLayers;

    VulkanDevice() : physicalDevice(nullptr), device(nullptr), graphicsQueue(nullptr), presentQueue(nullptr) {
        requiredExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
            VK_KHR_MULTIVIEW_EXTENSION_NAME,
        };

        optionalExtensions = {
            VK_EXT_FULL_SCREEN_EXCLUSIVE_EXTENSION_NAME,
        };

#ifdef RK_DEBUG
        requiredLayers = {
            "VK_LAYER_KHRONOS_validation",
        };
#endif
    }
};

void CreateVulkanDevice(VulkanDevice& _device, const VulkanInstance& _instance, const VulkanSurface& _surface);

void DestroyVulkanDevice(VulkanDevice& _device);

bool IsDeviceSuitable(const VkPhysicalDevice& _device, const VkSurfaceKHR& _surface);

uint16_t GetVulkanDeviceScore(const VkPhysicalDevice& _device);

VkPhysicalDevice PickVulkanPhysicalDevice(const VulkanInstance& _instance, const VkSurfaceKHR& _surface);

QueueFamilySupportDetails FindVulkanDeviceQueueFamiliesSupport(
    const VkPhysicalDevice& _device, const VkSurfaceKHR& _surface);

SwapChainSupportDetails FindVulkanDeviceSwapChainSupport(const VkPhysicalDevice& device, const VkSurfaceKHR& _surface);

void CheckVulkanDeviceExtensionsSupport(VulkanDevice& _device);

void CheckVulkanDeviceLayersSupport(VulkanDevice& _device);

inline std::string GetVulkanDeviceTypeString(VkPhysicalDeviceType _type) {
    switch (_type) {
        case VK_PHYSICAL_DEVICE_TYPE_OTHER:
            return "Other";
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            return "Integrated GPU";
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            return "Discrete GPU";
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
            return "Virtual GPU";
        case VK_PHYSICAL_DEVICE_TYPE_CPU:
            return "CPU";
        default:
            return "Unknown";
    }
}

}  // namespace Rake::platform::Vulkan
