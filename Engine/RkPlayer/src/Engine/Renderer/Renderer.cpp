#include "src/RkPch.h"

#include "Renderer.hpp"

#include "Drivers/Vulkan/VulkanRenderer.hpp"

namespace Rake::Engine
{

B8 Renderer::m_isInitialized = false;

std::unique_ptr<Renderer> Renderer::CreateRenderer(GraphicsAPI _api)
{
    if (!m_isInitialized)
    {
        if (_api == API_VULKAN)
            return std::make_unique<Drivers::VulkanRenderer>();
        else
            RK_SIGABRT;
    }
    else
        return nullptr;
}

} // namespace Rake::Engine
