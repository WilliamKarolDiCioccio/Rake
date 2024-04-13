#pragma once

#include <glm/vec2.hpp>

#include "RKRuntime/base.hpp"

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

/**
 * @brief The InputSystem class is a singleton class that manages the input devices.
 * 
 * @details
 * The InputSystem class is responsible for polling the input devices and managing the input mappings.
 * 
 * @note This class is a singleton instantiated by the Application class method and should be accessed through the Get() method.
 * @see Application
 */
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
    /**
	 * @brief Poll the input system to get.
	 * 
	 * @note This method is called by the Application class.
	 * @see Application
	 */
    virtual void Poll() noexcept = 0;

   public:
    /**
     * @brief Set the keyboard input map.
     * 
     * @param _inputMap The new keyboard input map.
     */
    RK_API void SetKeyboardInputMap(const std::unordered_map<Action, KeyboardKeys> &_inputMap) noexcept;

    /**
     * @brief Set the mouse input map.
     *  
     * @param _inputMap The new mouse input map.
     * @see MouseButtons
     * @see Action
	 */
    RK_API void SetMouseInputMap(const std::unordered_map<Action, MouseButtons> &_inputMap) noexcept;

    /**
     * @brief Set the controller buttons input map.
     * 
     * @param _inputMap The new controller buttons input map.
     * @see ControllerButtons
     * @see Action
     */
    RK_API void SetControllerButtonsInputMap(const std::unordered_map<Action, ControllerButtons> &_inputMap) noexcept;

    /**
	 * @brief Set the controller sticks input map.
	 * 
	 * @param _inputMap The new controller sticks input map.
	 * @see ControllerSticks
	 * @see Action
     */
    RK_API void SetControllerSticksInputMap(const std::unordered_map<Action, ControllerSticks> &_inputMap) noexcept;

    /**
     * @brief Set the controller triggers input map.
     * 
     * @param _inputMap The new controller triggers input map.
     * @see ControllerTriggers
     * @see Action
     */
    RK_API void SetControllerTriggersInputMap(const std::unordered_map<Action, ControllerTriggers> &_inputMap) noexcept;

    /**
	 * @brief Flip the mouse wheel scroll axis.
	 * 
     * @note You can use this method to invert the mouse wheel scroll direction at runtime not affecting the input map.
	 */
    RK_API void FlipMouseWheel() noexcept;

    /**
    * @brief Flip the mouse axis.
    * 
    * @param _axis The mouse axis to flip.
    * 
    * @note You can use this method to invert the mouse axis at runtime not affecting the input map.
    * @see MouseAxis
	*/
    RK_API void FlipMouseAxis(MouseAxis _axis) noexcept;

    /**
    * @brief Flip the controller axis.
    * 
    * @param _axis The controller axis to flip.
    * 
    * @note You can use this method to invert the controller axis at runtime not affecting the input map.
    * @see ControllerAxis
    */
    RK_API void FlipControllerAxis(ControllerAxis _axis) noexcept;

    /**
	 * @brief Check if a keyboard key is pressed.
	 * 
	 * @param _action The action to check for by label.
	 * @return True if the key is pressed, false otherwise.
	 */
    RK_API static bool IsKeyboardKeyPressed(Action _action) noexcept;

    /**
     * @brief Check if a keyboard key is first pressed.
     * 
     * @param _action The action to check for by label.
     * @return True if the key is first pressed, false otherwise.
	 */
    RK_API static bool IsKeyboardKeyFirstPressed(Action _action) noexcept;

    /**
     * @brief Check if a keyboard key is first released.
     * 
     * @param _action The action to check for by label.
     * @return True if the key is first released, false otherwise.
     */
    RK_API static bool IsKeyboardKeyFirstReleased(Action _action) noexcept;

    /**
	 * @brief Check if a mouse button is pressed.
	 * 
	 * @param _action The action to check for by label.
	 * @return True if the button is pressed, false otherwise.
     */
    RK_API static bool IsMouseButtonPressed(Action _action) noexcept;

    /**
	 * @brief Check if a mouse button is first pressed.
	 * 
	 * @param _action The action to check for by label.
	 * @return True if the button is first pressed, false otherwise.
     */
    RK_API static bool IsMouseButtonFirstPressed(Action _action) noexcept;

    /**
    * @brief Check if a mouse button is first released.
    * 
    * @param _action The action to check for by label.
    * @return True if the button is first released, false otherwise.
	*/
    RK_API static bool IsMouseButtonFirstReleased(Action _action) noexcept;

    /**
     * @brief Get the mouse cursor position.
     * 
     * @return The mouse cursor position.
     */
    RK_API static float GetMouseWheelDelta() noexcept;

    /**
	 * @brief Get the mouse cursor position as a 2D vector.
	 * 
	 * @return The mouse cursor position.
     * @note The position is relative to the window.
	 */
    RK_API static glm::vec2 GetMouseCursorDelta() noexcept;

    /**
	 * @brief Check if a controller button is pressed.
	 * 
	 * @param _action The action to check for by label.
	 * @return True if the button is pressed, false otherwise.
     */
    RK_API static bool IsControllerButtonPressed(Action _action) noexcept;

    /**
     * @brief Check if a controller button is first pressed.
     * 
     * @param _action The action to check for by label.
     * @return True if the button is first pressed, false otherwise.
     */
    RK_API static bool IsControllerButtonFirstPressed(Action _action) noexcept;

    /**
	 * @brief Check if a controller button is first released.
	 * 
	 * @param _action The action to check for by label.
	 * @return True if the button is first released, false otherwise.
     */
    RK_API static bool IsControllerButtonFirstReleased(Action _action) noexcept;

    /**
	 * @brief Get the controller trigger value as a float ranging from 0 to 1 representing the trigger pressure.
	 * 
	 * @return The controller trigger pressure value.
	 */
    RK_API static float GetControllerTriggerValue(Action _action) noexcept;

    /**
	 * @brief Get the controller cursor stricks movement as a 2D vector.
	 * 
	 * @return The controller cursor movement.
	 */
    RK_API static glm::vec2 GetControllerSticksDelta(Action _action) noexcept;

   private:
    /**
     * @brief Load the window state from InputMappings.json file.
     * 
     * @see SaveInputMappings
     */
    void LoadInputMappings() noexcept;

    /**
     * @brief Save the window state to InputMappings.json file.
     * 
     * @see LoadInputMappings
	 */
    void SaveInputMappings() noexcept;

   public:
    /**
     * @brief Get the singleton instance of the InputSystem class.
     * 
     * @return The InputSystem instance.
     */
    RK_API NODISCARD static InputSystem *Get() noexcept;

    /**
	 * @brief Get the keyboard keys input map.
	 * 
	 * @return The keyboard keys input map.
     */
    inline const std::unordered_map<Action, KeyboardKeys> &GetKeyboardInputMap() const noexcept {
        return m_keyboard.inputMap;
    }

    /**
     * @brief Get the mouse buttons input map.
     * 
     * @return The mouse buttons input map.
	 */
    inline const std::unordered_map<Action, MouseButtons> &GetMouseInputMap() const noexcept {
        return m_mouse.inputMap;
    }

    /**
	 * @brief Get the controller buttons input map.
	 * 
	 * @return The controller buttons input map.
     */
    inline const std::unordered_map<Action, ControllerButtons> &GetControllerButtonsInputMap() const noexcept {
        return m_controller.buttonsInputMap;
    }

    /**
	 * @brief Get the controller sticks input map.
	 * 
	 * @return The controller sticks input map.
     */
    inline const std::unordered_map<Action, ControllerSticks> &GetControllerSticksInputMap() const noexcept {
        return m_controller.sticksInputMap;
    }

    /**
     * @brief Get the controller triggers input map.
     * 
     * @return The controller triggers input map.
	 */
    inline const std::unordered_map<Action, ControllerTriggers> &GetControllerTriggersInputMap() const noexcept {
        return m_controller.triggersInputMap;
    }

    /**
     * @brief Create a native input system.
     * 
     * @return The native window system as a unique pointer.
     * @note This method is called by the Application class.
     * @see Application
     */
    static std::unique_ptr<InputSystem> CreateNative() noexcept;
};

}  // namespace Rake::core
