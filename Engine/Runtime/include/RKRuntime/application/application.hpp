#pragma once

#include "RKRuntime/tools/logger.hpp"
#include "RKRuntime/tools/profiler.hpp"
#include "RKRuntime/core/timer.hpp"
#include "RKRuntime/core/file_system.hpp"
#include "RKRuntime/core/input_system.hpp"
#include "RKRuntime/core/task_manager.hpp"
#include "RKRuntime/core/console_system.hpp"
#include "RKRuntime/engine/entity/scene.hpp"
#include "RKRuntime/engine/graphics/renderer_system.hpp"
#include "RKRuntime/engine/scripting/Python/PythonFFI_system.hpp"

namespace Rake::application {

/**
 * @brief The Application class is the main class of the engine.
 * 
 * @details
 * The Application class is a singleton class that is responsible for managing the application's lifecycle.
 * It is responsible for initializing and shutting down the application, as well as updating the application's systems.
 * 
 * @note The Application class is automatically created in the main function of the application. The user should only inherit from the Application class to implement the virtual functions and provide a template speecialization for the RkCreateApplication() function.
 * @see RkCreateApplication
 */
class RK_API Application : public NonCopyable, NonMovable {
   private:
    static inline Application *m_instance = nullptr;

    struct State {
        bool isRunning;
        bool isPaused;
        bool isBackground;
        std::mutex mutex;

        State() : isRunning(false), isPaused(false), isBackground(false) {}
    };

    State m_state;

   protected:
    core::Timer m_timer;
    std::unique_ptr<core::CVarSystem> m_cVarSystem = nullptr;
    std::unique_ptr<core::WindowSystem> m_windowSystem = nullptr;
    std::unique_ptr<core::InputSystem> m_inputSystem = nullptr;
    std::unique_ptr<engine::entity::Scene> m_scene = nullptr;
    std::unique_ptr<engine::graphics::RendererSystem> m_rendererSystem = nullptr;
    std::unique_ptr<engine::scripting::PythonFFISystem> m_pythonFFISystem = nullptr;

   public:
    Application();
    virtual ~Application();

   public:
    /**
     * @brief Start the application. Sets the application state to running.
     *
     * @note The function is called by the main function of the application to start the application.
     * @see OnStart
     * @see State
	 */
    void Start() noexcept;

    /**
     * @brief Pause the application. Sets the application state to paused.
     * 
     * @see OnPause
     * @see State
	 */
    void Pause() noexcept;

    /**
     * @brief Resume the application. Sets the application state to not paused.
     * 
     * @see OnResume
     * @see State
     */
    void Resume() noexcept;

    /**
     * @brief Update the application. Calls the OnUpdate function of the application.
     * 
     * @note The function is called by the main function of the application to update the application.
	 * @see OnUpdate
     * @see State
     */
    void Update() noexcept;

    /**
     * @brief Stop the application. Sets the application state to not running.
     * 
     * @note The function is called by the main function of the application to stop the application.
     * @see OnStop
     * @see State
     */
    void Stop() noexcept;

   protected:
    /**
     * @brief The function is called when the application is started.
     * 
     * @note The implementation should override this function to implement the application's startup logic.
     * @see Start
	 */
    virtual void OnStart() noexcept = 0;

    /**
     * @brief The function is called when the application is resumed.
     * 
     * @note The implementation should override this function to implement the application's resume logic.
     * @see Resume
     */
    virtual void OnResume() noexcept = 0;

    /**
     * @brief The function is called when the application is updated.
     * 
     * @note The implementation should override this function to implement the application's update logic.
     * @see Update
	 */
    virtual void OnUpdate() noexcept = 0;

    /**
     * @brief The function is called when the application is paused.
     * 
     * @note The user should override this function to implement the application's pause logic.
     * @see Pause
     */
    virtual void OnPause() noexcept = 0;

    /**
     * @brief The function is called when the application is stopped.
     * 
     * @note The user should override this function to implement the application's shutdown logic.
     * @see Stop
     */
    virtual void OnStop() noexcept = 0;

    virtual void OnImGuiRender() noexcept = 0;

   public:
    /**
     * @brief Get the state of the application.
     * 
     * @return The state of the application.
     * @see State
	 */
    NODISCARD inline const State &GetState() const noexcept { return m_state; }
};

}  // namespace Rake::application
