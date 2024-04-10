#pragma once

#include "vulkan_common.hpp"

namespace Rake::platform::Vulkan {

struct VulkanInstance {
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    std::vector<const char*> requiredExtensions;
    std::vector<const char*> optionalExtensions;
    std::vector<const char*> availableExtensions;
    std::vector<const char*> requiredLayers;
    std::vector<const char*> availableLayers;

    VulkanInstance() : instance(nullptr), debugMessenger(nullptr) {
        requiredExtensions = {
            VK_KHR_SURFACE_EXTENSION_NAME,
        };

#ifdef PLATFORM_WINDOWS
        requiredExtensions.emplace_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#endif

#ifdef RK_DEBUG
        requiredExtensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        requiredExtensions.emplace_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

        requiredLayers = {
            "VK_LAYER_KHRONOS_validation",
        };
#endif
    }
};

void CreateVulkanInstance(VulkanInstance& _instance);

void DestroyVulkanInstance(VulkanInstance& _instance);

void CreateVulkanDebugMessenger(VulkanInstance& _instance);

void DestroyVulkanDebugMessenger(VulkanInstance& _instance);

void CheckVulkanInstanceExtensionsSupport(VulkanInstance& _instance);

void CheckVulkanInstanceLayersSupport(VulkanInstance& _instance);

}  // namespace Rake::platform::Vulkan
