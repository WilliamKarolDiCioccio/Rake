#include "src/RkPch.h"

#include "VulkanRenderer.hpp"

namespace Rake::Drivers
{

VulkanRenderer::VulkanRenderer()
{
    this->InitAPI();
}

B8 VulkanRenderer::InitAPI()
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    if (vkCreateInstance(&createInfo, nullptr, &m_vkInstance) != VK_SUCCESS)
    {
    }

    return true;
}

void VulkanRenderer::ReleaseAPI()
{
    vkDestroyInstance(m_vkInstance, nullptr);
}

void VulkanRenderer::EnableValidationLayers()
{
}

} // namespace Rake::Drivers
