#pragma once

#define VK_NO_PROTOTYPES
#ifdef PLATFORM_WINDOWS
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#include <vulkan/vulkan.h>
#include <Volk/volk.h>
#include <vulkan/vk_enum_string_helper.h>
#ifdef PLATFORM_WINDOWS
#include "platform/win32/win32_common.hpp"
#include <vulkan/vulkan_win32.h>
#endif

namespace Rake::platform {

static inline void CheckVulkanResult(VkResult _result) {
    auto resultStr = libraries::ByteToWideString(std::string(string_VkResult(_result)));

    switch (_result) {
        case VK_SUCCESS:
            RK_LOG_DEBUG(L"Vulkan result: VK_SUCCESS");
            break;
        case VK_NOT_READY:
        case VK_TIMEOUT:
        case VK_EVENT_SET:
        case VK_EVENT_RESET:
        case VK_INCOMPLETE:
            RK_LOG_WARN(L"Vulkan result: {}", resultStr);
            break;
        case VK_ERROR_OUT_OF_HOST_MEMORY:
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
        case VK_ERROR_INITIALIZATION_FAILED:
        case VK_ERROR_DEVICE_LOST:
        case VK_ERROR_MEMORY_MAP_FAILED:
        case VK_ERROR_LAYER_NOT_PRESENT:
        case VK_ERROR_EXTENSION_NOT_PRESENT:
        case VK_ERROR_FEATURE_NOT_PRESENT:
        case VK_ERROR_INCOMPATIBLE_DRIVER:
        case VK_ERROR_TOO_MANY_OBJECTS:
        case VK_ERROR_FORMAT_NOT_SUPPORTED:
        case VK_ERROR_FRAGMENTED_POOL:
        case VK_ERROR_UNKNOWN:
        case VK_ERROR_OUT_OF_POOL_MEMORY:
        case VK_ERROR_INVALID_EXTERNAL_HANDLE:
        case VK_ERROR_FRAGMENTATION:
        case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        case VK_PIPELINE_COMPILE_REQUIRED:
        case VK_ERROR_SURFACE_LOST_KHR:
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        case VK_SUBOPTIMAL_KHR:
        case VK_ERROR_OUT_OF_DATE_KHR:
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        case VK_ERROR_VALIDATION_FAILED_EXT:
        case VK_ERROR_INVALID_SHADER_NV:
        case VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR:
        case VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR:
        case VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR:
        case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR:
        case VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR:
        case VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR:
        case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        case VK_ERROR_NOT_PERMITTED_KHR:
        case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        case VK_THREAD_IDLE_KHR:
        case VK_THREAD_DONE_KHR:
        case VK_OPERATION_DEFERRED_KHR:
        case VK_OPERATION_NOT_DEFERRED_KHR:
        case VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR:
        case VK_ERROR_COMPRESSION_EXHAUSTED_EXT:
        case VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT:
        case VK_RESULT_MAX_ENUM:
            RK_LOG_ERROR(L"Vulkan result: {}", resultStr);
            break;
        default:
            RK_LOG_FATAL(L"Unknown Vulkan result: {}", resultStr);
            break;
    }

    RK_ASSERT(_result == VK_SUCCESS);
}

}  // namespace Rake::platform
