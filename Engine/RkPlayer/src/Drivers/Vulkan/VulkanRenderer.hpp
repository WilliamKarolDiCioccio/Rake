#pragma once

#include <vector>
#include <vulkan/vulkan.h>

#include "Engine/Renderer/Renderer.hpp"
#include "VulkanUtils.hpp"

namespace Rake::Drivers
{

class VulkanRenderer : public Engine::Renderer
{
  private:
    struct savedVkExtensionData
    {
        U32 extensionsCount;
    };

    VkInstance m_vkInstance;

  public:
    VulkanRenderer();

  protected:
    B8 InitAPI() override;
    void ReleaseAPI() override;

  private:
    void EnableValidationLayers();
};

} // namespace Rake::Drivers
