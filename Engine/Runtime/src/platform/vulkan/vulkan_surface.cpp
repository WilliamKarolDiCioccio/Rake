#include "pch.hpp"

#include "platform/vulkan/vulkan_surface.hpp"

namespace Rake::platform::Vulkan {

#ifdef PLATFORM_WINDOWS
static VkResult CreateWin32Surface(
    VkInstance instance,
    const VkWin32SurfaceCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSurfaceKHR* pSurface) {
    auto func =
        reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(vkGetInstanceProcAddr(instance, "vkCreateWin32SurfaceKHR"));
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pSurface);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}
#endif

void CreateVulkanSurface(VulkanSurface& _surface, const VulkanInstance& _instance, void* _windowHandle) {
#ifdef PLATFORM_WINDOWS
    const VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
        .pNext = nullptr,
        .hinstance = GetModuleHandle(nullptr),
        .hwnd = (HWND)(_windowHandle),
    };

    if (CreateWin32Surface(_instance.instance, &surfaceCreateInfo, nullptr, &_surface.surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Win32 Vulkan surface!");
    }
#endif
}

void DestroyVulkanSurface(VulkanSurface& _surface, const VulkanInstance& _instance) {
    vkDestroySurfaceKHR(_instance.instance, _surface.surface, nullptr);
}

}  // namespace Rake::platform::Vulkan
