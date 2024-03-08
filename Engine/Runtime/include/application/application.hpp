#pragma once

#include "tools/logger.hpp"
#include "tools/profiler.hpp"
#include "core/timer.hpp"
#include "core/file_system.hpp"
#include "core/input_system.hpp"
#include "core/task_manager.hpp"
#include "core/console_system.hpp"
#include "engine/entity/scene.hpp"
#include "engine/graphics/renderer_system.hpp"
#include "engine/scripting/Python/PythonFFI_system.hpp"

namespace Rake::application {

using namespace std::chrono;

class Application : public NonCopyable, NonMovable {
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
    RK_API Application();
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
    virtual void OnImGuiRender() noexcept = 0;

   public:
    NODISCARD inline const State &GetState() const noexcept { return m_state; }
};

}  // namespace Rake::application
