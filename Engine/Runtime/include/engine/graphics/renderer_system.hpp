#pragma once

#include "core/window_system.hpp"
#include "core/command_line_parser.hpp"

namespace Rake::engine::graphics {

enum class RendererBackend : uint8_t {
    vulkan = 0 << 0,
    directx = 1 << 0,
};

class RenderingContext {
   public:
    virtual ~RenderingContext() = default;

   public:
    virtual void Render() noexcept = 0;
};

class RendererSystem {
   private:
    static inline RendererSystem* m_instance = nullptr;

   protected:
    struct Config {
        engine::graphics::RendererBackend backend;

        Config() : backend(engine::graphics::RendererBackend::vulkan) {}
    };

    static Config m_config;

    std::unordered_map<std::string, std::shared_ptr<RenderingContext>> m_contextRegistry;

   public:
    RendererSystem();
    virtual ~RendererSystem();

   public:
    void Render() noexcept;

   public:
    RK_API virtual const std::shared_ptr<RenderingContext>& CreateContext(
        const std::string& _name, const std::shared_ptr<core::Window>& _window) noexcept = 0;
    RK_API virtual void DestroyContext(const std::string& _name) noexcept = 0;

   public:
    RK_API static bool ParseOptionArguments(const char* _arg) noexcept;

    NODISCARD static const Config& GetConfig() noexcept { return m_config; }

    RK_API NODISCARD static RendererSystem* Get() noexcept;

    RK_API NODISCARD static const std::shared_ptr<RenderingContext> GetContextByName(const std::string& _name) noexcept;

    RK_API NODISCARD static const std::unordered_map<std::string, std::shared_ptr<RenderingContext>>&
    GetContextRegistry() noexcept;

    static std::unique_ptr<RendererSystem> CreateWithBackend() noexcept;
};

}  // namespace Rake::engine::graphics
