#include "pch.hpp"

#include "platform/vulkan/vulkan_device.hpp"
#include "platform/vulkan/vulkan_surface.hpp"

namespace Rake::platform::Vulkan {

void CreateVulkanDevice(VulkanDevice& _device, const VulkanInstance& _instance, const VulkanSurface& _surface) {
    VkPhysicalDevice physicalDevice = PickVulkanPhysicalDevice(_instance, _surface.surface);

    CheckVulkanDeviceExtensionsSupport(_device);

    for (const auto& extension : _instance.availableExtensions) {
        RK_LOG_INFO(L"Enabled Vulkan device extension '{}'", libraries::ByteToWideString(extension));
    }

    CheckVulkanDeviceLayersSupport(_device);

    for (const auto& layer : _instance.availableLayers) {
        RK_LOG_INFO(L"Enabled Vulkan device layer '{}'", libraries::ByteToWideString(layer));
    }

    _device.physicalDevice = physicalDevice;

    QueueFamilySupportDetails indices = FindVulkanDeviceQueueFamiliesSupport(physicalDevice, _surface.surface);

    constexpr float queuePriorities = 1.0f;

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    float queuePriority = 1.0f;

    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    constexpr VkPhysicalDeviceFeatures deviceFeatures{
        .geometryShader = true,
        .sampleRateShading = true,
        .multiDrawIndirect = true,
        .fillModeNonSolid = true,
        .multiViewport = true,
        .samplerAnisotropy = true,
    };

    const VkDeviceCreateInfo deviceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size()),
        .pQueueCreateInfos = queueCreateInfos.data(),
        .enabledLayerCount = static_cast<uint32_t>(_device.availableLayers.size()),
        .ppEnabledLayerNames = _device.availableLayers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(_device.availableExtensions.size()),
        .ppEnabledExtensionNames = _device.availableExtensions.data(),
        .pEnabledFeatures = &deviceFeatures,
    };

    if (vkCreateDevice(_device.physicalDevice, &deviceCreateInfo, nullptr, &_device.device) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan device!");
    }

    volkLoadDevice(_device.device);

    vkGetDeviceQueue(_device.device, indices.graphicsFamily.value(), 0, &_device.graphicsQueue);
    vkGetDeviceQueue(_device.device, indices.presentFamily.value(), 0, &_device.presentQueue);
}

void DestroyVulkanDevice(VulkanDevice& _device) { vkDestroyDevice(_device.device, nullptr); }

bool IsDeviceSuitable(const VkPhysicalDevice& _physicalDevice, const VkSurfaceKHR& _surface) {
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(_physicalDevice, &deviceProperties);
    vkGetPhysicalDeviceFeatures(_physicalDevice, &deviceFeatures);

    QueueFamilySupportDetails queueFamiliySupport = FindVulkanDeviceQueueFamiliesSupport(_physicalDevice, _surface);
    SwapChainSupportDetails swapChainSupport = FindVulkanDeviceSwapChainSupport(_physicalDevice, _surface);

    return deviceFeatures.geometryShader && deviceFeatures.sampleRateShading && deviceFeatures.multiDrawIndirect &&
           deviceFeatures.fillModeNonSolid && deviceFeatures.multiViewport && deviceFeatures.samplerAnisotropy &&
           queueFamiliySupport.IsComplete() && swapChainSupport.IsComplete();
}

uint16_t GetVulkanDeviceScore(const VkPhysicalDevice& _physicalDevice) {
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(_physicalDevice, &deviceProperties);
    vkGetPhysicalDeviceFeatures(_physicalDevice, &deviceFeatures);

    uint16_t score = 0;

    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
        score += 1000;
    }

    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(_physicalDevice, &memoryProperties);

    uint32_t heapCount = memoryProperties.memoryHeapCount;
    uint64_t totalDeviceMemory = 0;

    for (uint32_t j = 0; j < heapCount; ++j) {
        if (memoryProperties.memoryHeaps[j].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) {
            totalDeviceMemory += memoryProperties.memoryHeaps[j].size;
        }
    }

    totalDeviceMemory /= 1024 * 1024;

    return score;
}

VkPhysicalDevice PickVulkanPhysicalDevice(const VulkanInstance& _instance, const VkSurfaceKHR& _surface) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(_instance.instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("Failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(_instance.instance, &deviceCount, devices.data());

    uint32_t highestScore = 0;
    VkPhysicalDevice physicalDevice = nullptr;

    for (const auto& device : devices) {
        if (IsDeviceSuitable(device, _surface)) {
            VkPhysicalDeviceProperties deviceProperties;
            vkGetPhysicalDeviceProperties(device, &deviceProperties);

            RK_LOG_DEBUG(
                L"Found suitable Vulkan GPU! name:'{}'",
                libraries::ByteToWideString(deviceProperties.deviceName));

            if (GetVulkanDeviceScore(device) >= highestScore) {
                physicalDevice = device;
            }
        }
    }

    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

    RK_LOG_INFO(
        L"Selected Vulkan GPU! name:'{}' type:'{}' driver:'{}'",
        libraries::ByteToWideString(deviceProperties.deviceName),
        libraries::ByteToWideString(GetVulkanDeviceTypeString(deviceProperties.deviceType)),
        deviceProperties.driverVersion);

    if (physicalDevice == nullptr) {
        throw std::runtime_error("Failed to find a suitable GPU!");
    }

    return physicalDevice;
}

QueueFamilySupportDetails FindVulkanDeviceQueueFamiliesSupport(
    const VkPhysicalDevice& _device, const VkSurfaceKHR& _surface) {
    QueueFamilySupportDetails indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(_device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(_device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(_device, i, _surface, &presentSupport);

        if (presentSupport) {
            indices.presentFamily = i;
        }

        if (indices.IsComplete()) {
            break;
        }

        i++;
    }

    return indices;
}

SwapChainSupportDetails FindVulkanDeviceSwapChainSupport(const VkPhysicalDevice& device, const VkSurfaceKHR& _surface) {
    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, _surface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, _surface, &formatCount, nullptr);

    if (formatCount != 0) {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, _surface, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, _surface, &presentModeCount, nullptr);

    if (presentModeCount != 0) {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, _surface, &presentModeCount, details.presentModes.data());
    }

    return details;
}

void CheckVulkanDeviceExtensionsSupport(VulkanDevice& _device) {
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    for (const auto& requiredExtension : _device.requiredExtensions) {
        bool found = std::find_if(extensions.begin(), extensions.end(), [&](const VkExtensionProperties& extension) {
                         return strncmp(requiredExtension, extension.extensionName, VK_MAX_EXTENSION_NAME_SIZE);
                     }) != extensions.end();

        if (found) {
            _device.availableExtensions.push_back(requiredExtension);
        } else {
            throw RkException("Required Vulkan device extension {} is not supported!", requiredExtension);
        }
    }

    for (const auto& optionalExtension : _device.optionalExtensions) {
        bool found = std::find_if(extensions.begin(), extensions.end(), [&](const VkExtensionProperties& extension) {
                         return strncmp(optionalExtension, extension.extensionName, VK_MAX_EXTENSION_NAME_SIZE);
                     }) != extensions.end();

        if (found) {
            _device.availableExtensions.push_back(optionalExtension);
        } else {
            RK_LOG_WARN(
                L"Optional Vulkan device extension '{}' is not supported!",
                libraries::ByteToWideString(optionalExtension));
        }
    }
}

void CheckVulkanDeviceLayersSupport(VulkanDevice& _device) {
    uint32_t layerCount = 0;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> layers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

    for (const auto& requiredLayer : _device.requiredLayers) {
        bool found = std::find_if(layers.begin(), layers.end(), [&](const VkLayerProperties& layer) {
                         return strncmp(requiredLayer, layer.layerName, VK_MAX_EXTENSION_NAME_SIZE) == 0;
                     }) != layers.end();

        if (found) {
            _device.availableLayers.push_back(requiredLayer);
        } else {
            throw RkException("Required Vulkan device layer {} is not supported!", requiredLayer);
        }
    }
}

}  // namespace Rake::platform::Vulkan
