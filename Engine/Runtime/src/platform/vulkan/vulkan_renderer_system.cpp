#include "pch.hpp"

#include "platform/vulkan/vulkan_renderer_system.hpp"

namespace Rake::platform::Vulkan {

VulkanRenderingContext::VulkanRenderingContext(
    const std::shared_ptr<core::Window>& _window, const VulkanInstance& _instance)
    : m_window(_window), m_instance(_instance) {
    const auto& windowHandle = _window->GetNativeHandle();
    const auto& renderTargetSize = _window->GetRenderTargetSize();

    Rake::tools::Profiler::BeginProfile(L"Initialization - Vulkan Context", Rake::tools::ProfileCategory::function);

    CreateVulkanSurface(m_surface, m_instance, windowHandle);
    CreateVulkanDevice(m_device, m_instance, m_surface);
    CreateVulkanSwapchain(m_swapchain, m_device, m_surface, renderTargetSize);

    Rake::tools::Profiler::EndProfile();
}

VulkanRenderingContext::~VulkanRenderingContext() {
    DestroyVulkanSwapchain(m_swapchain);
    DestroyVulkanDevice(m_device);
    DestroyVulkanSurface(m_surface, m_instance);
}

void VulkanRenderingContext::Render() noexcept {}

VulkanRendererSystem::VulkanRendererSystem() {
    Rake::tools::Profiler::BeginProfile(L"Initialization - Vulkan System", Rake::tools::ProfileCategory::function);

    CreateVulkanInstance(m_instance);

    Rake::tools::Profiler::EndProfile();
}

VulkanRendererSystem::~VulkanRendererSystem() {
    m_contextRegistry.clear();

    DestroyVulkanInstance(m_instance);
}

std::shared_ptr<engine::graphics::RenderingContext>& VulkanRendererSystem::CreateContext(
    const std::string& _name, const std::shared_ptr<core::Window>& _window) noexcept {
    auto context = std::make_unique<VulkanRenderingContext>(_window, m_instance);

    m_contextRegistry[_name] = std::move(context);

    return m_contextRegistry[_name];
}

void VulkanRendererSystem::DestroyContext(const std::string& _name) noexcept { m_contextRegistry.erase(_name); }

}  // namespace Rake::platform::Vulkan
