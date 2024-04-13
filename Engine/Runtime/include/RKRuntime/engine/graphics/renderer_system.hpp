#pragma once

#include "RKRuntime/core/window_system.hpp"
#include "RKRuntime/core/command_line_parser.hpp"

namespace Rake::engine::graphics {

/**
 * @brief The renderer backend flags
 */
enum class RendererBackend : uint8_t {
    vulkan = 0 << 0,
    directx = 1 << 0,
};

/**
 * @brief The rendering context interface
 * 
 * @details
 * The RenderingContext class is responsible for managing the context's state and data.
 * Each RenderingContext instance is associated with a specific window and is responsible for rendering the window's content.
 * 
 * @note This class is a singleton instantiated by the Application class method and should be accessed through the Get() method.
 * @see Application
 * @see RendererSystem
 */
class RenderingContext {
   public:
    virtual ~RenderingContext() = default;

   public:
    virtual void Render() noexcept = 0;
};

/**
 * @brief The RendererSystem class is an abstract class that represents a rendering system.
 * 
 * @details
 * The RendererSystem class is responsible for creating, managing, and destroying contexts. It keeps track of all contexts.
 * 
 * @note This class is a singleton instantiated by the Application class method and should be accessed through the Get() method.
 * @see RenderingContext
 */
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
    /**
	 * @brief Render the next frame.
	 * 
     * @note This method is called by the Application class.
     * @see Application
	 */
    void Render() noexcept;

   public:
    RK_API virtual const std::shared_ptr<RenderingContext>& CreateContext(
        const std::string& _name, const std::shared_ptr<core::Window>& _window) noexcept = 0;
    RK_API virtual void DestroyContext(const std::string& _name) noexcept = 0;

   public:
    /**
	 * @brief Command line arguments handler for the RendererSystem class.
	 * 
	 * @param _arg The command line argument.
	 * @return True if the argument was parsed successfully, false otherwise.
	 */
    RK_API static bool ParseOptionArguments(const std::string& _arg) noexcept;

    /**
     * @brief Get the stored configuration of the RendererSystem class.
	 * 
	 * @return The configuration as a const reference.
	 */
    NODISCARD static const Config& GetConfig() noexcept { return m_config; }

    /**
     * @brief Get the singleton instance of the RendererSystem class.
     * 
     * @return The RendererSystem instance.
     */
    RK_API NODISCARD static RendererSystem* Get() noexcept;

    /**
     * @brief Get the context by name.
     * 
     * @param _name The name of the context.
     * @return The context as a shared pointer.
	 */
    RK_API NODISCARD static const std::shared_ptr<RenderingContext> GetContextByName(const std::string& _name) noexcept;

    /**
	 * @brief Get the context registry.
	 * 
	 * @return The context registry as a const reference to an unordered map.
	 */
    RK_API NODISCARD static const std::unordered_map<std::string, std::shared_ptr<RenderingContext>>&
    GetContextRegistry() noexcept;

    /**
     * @brief Create the choosen rendering system.
     * 
     * @return The choosen rendering system as a unique pointer.
     * @note This method is called by the Application class.
     * @note You can choose the rendering system by setting the command line argument --renderer followed by the backend name (vulkan or directx). Choosing DirectX on non-Windows platforms will result in a runtime error.
     * @see Application
     */
    static std::unique_ptr<RendererSystem> CreateWithBackend() noexcept;
};

}  // namespace Rake::engine::graphics
