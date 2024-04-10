#pragma once

#include "RKRuntime/engine/graphics/renderer_system.hpp"

#include "vulkan_instance.hpp"
#include "vulkan_surface.hpp"
#include "vulkan_device.hpp"
#include "vulkan_swapchain.hpp"

namespace Rake::platform::Vulkan {

class VulkanRenderingContext final : public engine::graphics::RenderingContext {
   private:
    std::shared_ptr<core::Window> m_window;
    VulkanInstance m_instance;
    VulkanDevice m_device;
    VulkanSurface m_surface;
    VulkanSwapchain m_swapchain;

   public:
    VulkanRenderingContext(const std::shared_ptr<core::Window>& _window, const VulkanInstance& _instance);
    ~VulkanRenderingContext() override;

   public:
    void Render() noexcept override;
};

class VulkanRendererSystem final : public engine::graphics::RendererSystem {
   private:
    VulkanInstance m_instance;

   public:
    VulkanRendererSystem();
    ~VulkanRendererSystem() override;

   public:
    std::shared_ptr<engine::graphics::RenderingContext>& CreateContext(
        const std::string& _name, const std::shared_ptr<core::Window>& _window) noexcept override;
    void DestroyContext(const std::string& _name) noexcept override;
};

}  // namespace Rake::platform::Vulkan
