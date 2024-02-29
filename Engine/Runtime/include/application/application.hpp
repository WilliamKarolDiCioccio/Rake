#pragma once

#include "tools/logger.hpp"
#include "core/timer.hpp"
#include "core/file_system.hpp"
#include "core/input_system.hpp"
#include "core/task_manager.hpp"
#include "core/console_system.hpp"
#include "engine/entity/scene.hpp"
#include "engine/graphics/renderer.hpp"
#include "engine/scripting/Python/PythonFFI.hpp"

namespace Rake::application {

using namespace std::chrono;

class Application : public NonCopyable, NonMovable {
   private:
    static inline Application *m_instance = nullptr;

    enum class Mode {
        none = 0,
        gameMode = 1,
        cheatMode = 2,
        editorMode = 3,
    };

    struct ApplicationConfig {
        bool disablePythonInterpreter;
        bool optionTerminatesPrematurely;
    };

    ApplicationConfig m_config = {};

    struct ApplicationState {
        std::atomic<bool> isRunning;
        std::atomic<bool> isPaused;
        std::atomic<bool> isBackground;
        std::mutex mutex;
    };

    ApplicationState m_state = {};

   protected:
    core::Timer m_timer;
    tools::Logger m_logger;

    std::unique_ptr<core::CVarSystem> m_cVarSystem = nullptr;
    std::unique_ptr<core::WindowSystem> m_windowSystem = nullptr;
    std::unique_ptr<core::InputSystem> m_inputSystem = nullptr;
    std::unique_ptr<engine::entity::Scene> m_scene = nullptr;
    std::unique_ptr<engine::graphics::Renderer> m_renderer = nullptr;
    std::unique_ptr<engine::scripting::PythonFFISystem> m_pythonFFISystem = nullptr;

   public:
    RK_API Application(int _argc, const char *_argv[]);
    RK_API virtual ~Application();

   public:
    RK_API void Start() noexcept;
    RK_API void Pause() noexcept;
    RK_API void Resume() noexcept;
    RK_API void Update() noexcept;
    RK_API void Stop() noexcept;

   protected:
    virtual void OnStart() noexcept = 0;
    virtual void OnResume() noexcept = 0;
    virtual void OnUpdate() noexcept = 0;
    virtual void OnPause() noexcept = 0;
    virtual void OnStop() noexcept = 0;
    virtual void OnImGuiRender(core::Window *window_handle) noexcept = 0;

   public:
    NODISCARD inline const ApplicationConfig &GetConfig() const noexcept { return m_config; }
    NODISCARD inline const ApplicationState &GetState() const noexcept { return m_state; }
};

}  // namespace Rake::application

#define RK_NONE_MODE   Rake::application::Application::Mode::none
#define RK_GAME_MODE   Rake::application::Application::Mode::gameMode
#define RK_CHEAT_MODE  Rake::application::Application::Mode::cheatMode
#define RK_EDITOR_MODE Rake::application::Application::Mode::editorMode
