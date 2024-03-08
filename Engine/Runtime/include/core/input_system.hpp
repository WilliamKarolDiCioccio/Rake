#pragma once

#include <glm/vec2.hpp>

#include "base.hpp"

#include "input_map.inl"

namespace Rake::core {

using Action = std::string;

struct Keyboard {
    struct InputState {
        bool keyDown[256];
    };

    bool connected = false;
    std::unordered_map<Action, KeyboardKeys> inputMap = {};
    InputState inputState = {};
    InputState lastInputState = {};
};

struct Mouse {
    struct InputState {
        glm::vec2 cursorPosition;
        float wheelDelta;
        bool buttons[5];
    };

    bool connected = false;
    float battery = 0.f;
    std::unordered_map<Action, MouseButtons> inputMap = {};
    int8_t flipAxis[2] = {1, 1};
    int8_t flipWheel = 1;
    InputState inputState = {};
    InputState lastInputState = {};
};

struct Controller {
    struct InputState {
        glm::vec2 sticks[2];
        float triggers[2];
        bool buttons[12];
    };

    bool connected = false;
    float battery = 0.f;
    std::unordered_map<Action, ControllerButtons> buttonsInputMap = {};
    std::unordered_map<Action, ControllerTriggers> triggersInputMap = {};
    std::unordered_map<Action, ControllerSticks> sticksInputMap = {};
    int8_t flipAxis[4] = {1, 1, 1, 1};
    InputState inputState = {};
    InputState lastInputState = {};
};

class InputSystem : public NonCopyable, NonMovable {
   private:
    static inline InputSystem *m_instance = nullptr;

   protected:
    static inline Keyboard m_keyboard = {};
    static inline Mouse m_mouse = {};
    static inline Controller m_controller = {};

   public:
    InputSystem();
    virtual ~InputSystem();

   public:
    virtual void Poll() noexcept = 0;

   public:
    RK_API void SetKeyboardInputMap(const std::unordered_map<Action, KeyboardKeys> &_inputMap) noexcept;
    RK_API void SetMouseInputMap(const std::unordered_map<Action, MouseButtons> &_inputMap) noexcept;
    RK_API void SetControllerButtonsInputMap(const std::unordered_map<Action, ControllerButtons> &_inputMap) noexcept;
    RK_API void SetControllerSticksInputMap(const std::unordered_map<Action, ControllerSticks> &_inputMap) noexcept;
    RK_API void SetControllerTriggersInputMap(const std::unordered_map<Action, ControllerTriggers> &_inputMap) noexcept;
    RK_API void FlipMouseWheel() noexcept;
    RK_API void FlipMouseAxis(MouseAxis _axis) noexcept;
    RK_API void FlipControllerAxis(ControllerAxis _axis) noexcept;
    RK_API static bool IsKeyboardKeyPressed(Action _action) noexcept;
    RK_API static bool IsKeyboardKeyFirstPressed(Action _action) noexcept;
    RK_API static bool IsKeyboardKeyFirstReleased(Action _action) noexcept;
    RK_API static bool IsMouseButtonPressed(Action _action) noexcept;
    RK_API static bool IsMouseButtonFirstPressed(Action _action) noexcept;
    RK_API static bool IsMouseButtonFirstReleased(Action _action) noexcept;
    RK_API static float GetMouseWheelDelta() noexcept;
    RK_API static glm::vec2 GetMouseCursorDelta() noexcept;
    RK_API static bool IsControllerButtonPressed(Action _action) noexcept;
    RK_API static bool IsControllerButtonFirstPressed(Action _action) noexcept;
    RK_API static bool IsControllerButtonFirstReleased(Action _action) noexcept;
    RK_API static float GetControllerTriggerValue(Action _action) noexcept;
    RK_API static glm::vec2 GetControllerSticksDelta(Action _action) noexcept;

   private:
    void LoadSettings() noexcept;
    void SaveSettings() noexcept;

   public:
    RK_API NODISCARD static  InputSystem *Get() noexcept;

    inline const std::unordered_map<Action, KeyboardKeys> &GetKeyboardInputMap() const noexcept {
        return m_keyboard.inputMap;
    }

    inline const std::unordered_map<Action, MouseButtons> &GetMouseInputMap() const noexcept {
        return m_mouse.inputMap;
    }

    inline const std::unordered_map<Action, ControllerButtons> &GetControllerButtonsInputMap() const noexcept {
        return m_controller.buttonsInputMap;
    }

    inline const std::unordered_map<Action, ControllerSticks> &GetControllerSticksInputMap() const noexcept {
        return m_controller.sticksInputMap;
    }

    inline const std::unordered_map<Action, ControllerTriggers> &GetControllerTriggersInputMap() const noexcept {
        return m_controller.triggersInputMap;
    }

    static std::unique_ptr<InputSystem> CreateNative() noexcept;
};

}  // namespace Rake::core
