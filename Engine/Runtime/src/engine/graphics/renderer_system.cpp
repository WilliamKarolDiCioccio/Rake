#include "pch.hpp"

#include "engine/graphics/renderer_system.hpp"

#include "platform/vulkan/vulkan_renderer_system.hpp"

namespace Rake::engine::graphics {

RendererSystem::Config RendererSystem::m_config;

RendererSystem::RendererSystem() {
    if (m_instance != nullptr) throw std::runtime_error("RendererSystem already created!");

    m_instance = this;

    m_contextRegistry.reserve(8);
}

RendererSystem::~RendererSystem() {
    m_instance = nullptr;
    delete (m_instance);
}

bool RendererSystem::ParseOptionArguments(const char *_arg) noexcept {
    if (strncmp(_arg, "vulkan", 6) == NULL) {
        m_config.backend = engine::graphics::RendererBackend::vulkan;
    } else if (strncmp(_arg, "directx", 7) == NULL) {
        m_config.backend = engine::graphics::RendererBackend::directx;
    } else {
        return false;
    }

    return true;
}

void RendererSystem::Render() noexcept {
    for (auto &[name, context] : m_contextRegistry) {
        context->Render();
    }
}

RendererSystem *RendererSystem::Get() noexcept { return m_instance; }

std::unique_ptr<RendererSystem> RendererSystem::CreateWithBackend() noexcept {
    switch (m_config.backend) {
        case Rake::engine::graphics::RendererBackend::vulkan:
            return std::make_unique<platform::Vulkan::VulkanRendererSystem>();
    }
}

const std::shared_ptr<RenderingContext> RendererSystem::GetContextByName(const std::string &_name) noexcept {
    auto it = m_instance->m_contextRegistry.find(_name);

    if (it != m_instance->m_contextRegistry.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

const std::unordered_map<std::string, std::shared_ptr<RenderingContext>> &
RendererSystem::GetContextRegistry() noexcept {
    return m_instance->m_contextRegistry;
}

}  // namespace Rake::engine::graphics
