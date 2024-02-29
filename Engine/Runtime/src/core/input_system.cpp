#include "pch.hpp"

#include "core/input_system.hpp"

#include "core/file_system.hpp"
#ifdef PLATFORM_WINDOWS
#include "platform/win32/win32_input_system.hpp"
#endif

namespace Rake::core {

InputSystem::InputSystem() {
    if (m_instance != nullptr) throw std::runtime_error("Input system already created!");

    m_instance = this;

    LoadSettings();
}

InputSystem::~InputSystem() {
    SaveSettings();

    m_instance = nullptr;
    delete (m_instance);
}

void InputSystem::SetKeyboardInputMap(const std::unordered_map<Action, KeyboardKeys> &_inputMap) noexcept {
    m_keyboard.inputMap = _inputMap;
}

void InputSystem::SetMouseInputMap(const std::unordered_map<Action, MouseButtons> &_inputMap) noexcept {
    m_mouse.inputMap = _inputMap;
}

void InputSystem::SetControllerButtonsInputMap(
    const std::unordered_map<Action, ControllerButtons> &_inputMap) noexcept {
    m_controller.buttonsInputMap = _inputMap;
}

void InputSystem::SetControllerSticksInputMap(const std::unordered_map<Action, ControllerSticks> &_inputMap) noexcept {
    m_controller.sticksInputMap = _inputMap;
}

void InputSystem::SetControllerTriggersInputMap(
    const std::unordered_map<Action, ControllerTriggers> &_inputMap) noexcept {
    m_controller.triggersInputMap = _inputMap;
}

void InputSystem::FlipMouseWheel() noexcept { m_mouse.flipWheel *= -1; }

void InputSystem::FlipMouseAxis(MouseAxis _axis) noexcept { m_mouse.flipAxis[(uint8_t)_axis] *= -1; }

void InputSystem::FlipControllerAxis(ControllerAxis _axis) noexcept { m_controller.flipAxis[(uint8_t)_axis] *= -1; }

bool InputSystem::IsKeyboardKeyPressed(Action _action) noexcept {
    return m_keyboard.inputState.keyDown[(uint8_t)m_keyboard.inputMap[_action]];
}

bool InputSystem::IsKeyboardKeyFirstPressed(Action _action) noexcept {
    const uint8_t &key = (uint8_t)m_keyboard.inputMap[_action];

    return m_keyboard.inputState.keyDown[key] && !m_keyboard.lastInputState.keyDown[key];
}

bool InputSystem::IsKeyboardKeyFirstReleased(Action _action) noexcept {
    const uint8_t &key = (uint8_t)m_keyboard.inputMap[_action];

    return !m_keyboard.inputState.keyDown[key] && m_keyboard.lastInputState.keyDown[key];
}

bool InputSystem::IsMouseButtonPressed(Action _action) noexcept {
    return m_mouse.inputState.buttons[(uint8_t)m_mouse.inputMap[_action]];
}

bool InputSystem::IsMouseButtonFirstPressed(Action _action) noexcept {
    const uint8_t &button = (uint8_t)m_mouse.inputMap[_action];

    return m_mouse.inputState.buttons[button] && !m_mouse.lastInputState.buttons[button];
}

bool InputSystem::IsMouseButtonFirstReleased(Action _action) noexcept {
    const uint8_t &button = (uint8_t)m_mouse.inputMap[_action];

    return !m_mouse.inputState.buttons[button] && m_mouse.lastInputState.buttons[button];
}

float InputSystem::GetMouseWheelDelta() noexcept { return m_mouse.inputState.wheelDelta * m_mouse.flipWheel; }

glm::vec2 InputSystem::GetMouseCursorDelta() noexcept {
    return (m_mouse.inputState.cursorPosition - m_mouse.lastInputState.cursorPosition) *
           glm::vec2{m_mouse.flipAxis[0], m_mouse.flipAxis[1]};
}

bool InputSystem::IsControllerButtonPressed(Action _action) noexcept {
    return m_controller.inputState.buttons[(uint8_t)m_controller.buttonsInputMap[_action]];
}

bool InputSystem::IsControllerButtonFirstPressed(Action _action) noexcept {
    const uint8_t &button = (uint8_t)m_controller.buttonsInputMap[_action];

    return m_controller.inputState.buttons[button] && !m_controller.lastInputState.buttons[button];
}

bool InputSystem::IsControllerButtonFirstReleased(Action _action) noexcept {
    const uint8_t &button = (uint8_t)m_controller.buttonsInputMap[_action];

    return !m_controller.inputState.buttons[button] && m_controller.lastInputState.buttons[button];
}

float InputSystem::GetControllerTriggerValue(Action _action) noexcept {
    return m_controller.inputState.triggers[(uint8_t)m_controller.triggersInputMap[_action]];
}

glm::vec2 InputSystem::GetControllerSticksDelta(Action _action) noexcept {
    const uint8_t &stick = (uint8_t)m_controller.sticksInputMap[_action];

    return (m_controller.inputState.sticks[stick] - m_controller.lastInputState.sticks[stick]) *
           glm::vec2{m_controller.flipAxis[0], m_controller.flipAxis[1]};
}

void InputSystem::LoadSettings() noexcept {
    try {
        if (!core::FileExists(L"InputSettings.json")) core::CreateFile(L"InputSettings.json");

        auto data = ReadJSON(L"InputSettings.json");

        m_mouse.flipAxis[0] = data["Mouse"]["FlipAxisX"] == 1 ? 1 : -1;
        m_mouse.flipAxis[1] = data["Mouse"]["FlipAxisY"] == 1 ? 1 : -1;
        m_controller.flipAxis[0] = data["Controller"]["FlipAxisXL"] == 1 ? 1 : -1;
        m_controller.flipAxis[1] = data["Controller"]["FlipAxisYL"] == 1 ? 1 : -1;
        m_controller.flipAxis[2] = data["Controller"]["FlipAxisXR"] == 1 ? 1 : -1;
        m_controller.flipAxis[3] = data["Controller"]["FlipAxisYR"] == 1 ? 1 : -1;

        for (const auto &[k, v] : data["Keyboard"]["InputMap"].items()) {
            m_keyboard.inputMap[k] = v;
        }

        for (const auto &[k, v] : data["Mouse"]["InputMap"].items()) {
            m_mouse.inputMap[k] = v;
        }

        for (const auto &[k, v] : data["Controller"]["ButtonsInputMap"].items()) {
            m_controller.buttonsInputMap[k] = v;
        }

        for (const auto &[k, v] : data["Controller"]["SticksInputMap"].items()) {
            m_controller.sticksInputMap[k] = v;
        }

        for (const auto &[k, v] : data["Controller"]["TriggersInputMap"].items()) {
            m_controller.triggersInputMap[k] = v;
        }

        for (const auto &[k, v] : data["Controller"]["AxisInputMap"].items()) {
            m_controller.sticksInputMap[k] = v;
        }
    } catch (const std::exception &) {
        nlohmann::json data;

        data["Keyboard"] = nlohmann::json::object();
        data["Mouse"] = nlohmann::json::object();
        data["Controller"] = nlohmann::json::object();
        data["Keyboard"]["InputMap"] = nlohmann::json::object();
        data["Mouse"]["InputMap"] = nlohmann::json::object();
        data["Controller"]["InputMap"] = nlohmann::json::object();

        data["Mouse"]["FlipAxisX"] = m_mouse.flipAxis[0];
        data["Mouse"]["FlipAxisY"] = m_mouse.flipAxis[1];
        data["Controller"]["FlipAxisXL"] = m_controller.flipAxis[0];
        data["Controller"]["FlipAxisYL"] = m_controller.flipAxis[1];
        data["Controller"]["FlipAxisXR"] = m_controller.flipAxis[2];
        data["Controller"]["FlipAxisYR"] = m_controller.flipAxis[3];

        for (const auto &[k, v] : m_keyboard.inputMap) data["Keyboard"]["InputMap"][k] = v;
        for (const auto &[k, v] : m_mouse.inputMap) data["Mouse"]["InputMap"][k] = v;
        for (const auto &[k, v] : m_controller.buttonsInputMap) data["Controller"]["ButtonsInputMap"][k] = v;
        for (const auto &[k, v] : m_controller.sticksInputMap) data["Controller"]["SticksInputMap"][k] = v;
        for (const auto &[k, v] : m_controller.triggersInputMap) data["Controller"]["TriggersInputMap"][k] = v;

        if (!core::FileExists(L"InputSettings.json")) core::CreateFile(L"InputSettings.json");

        core::WriteJSON(L"InputSettings.json", data);
    }
}

void InputSystem::SaveSettings() noexcept {
    nlohmann::json data;

    data["Keyboard"] = nlohmann::json::object();
    data["Mouse"] = nlohmann::json::object();
    data["Controller"] = nlohmann::json::object();
    data["Keyboard"]["InputMap"] = nlohmann::json::object();
    data["Mouse"]["InputMap"] = nlohmann::json::object();
    data["Controller"]["ButtonsInputMap"] = nlohmann::json::object();
    data["Controller"]["SticksInputMap"] = nlohmann::json::object();
    data["Controller"]["TriggersInputMap"] = nlohmann::json::object();

    data["Mouse"]["FlipAxisX"] = m_mouse.flipAxis[0];
    data["Mouse"]["FlipAxisY"] = m_mouse.flipAxis[1];
    data["Controller"]["FlipAxisXL"] = m_controller.flipAxis[0];
    data["Controller"]["FlipAxisYL"] = m_controller.flipAxis[1];
    data["Controller"]["FlipAxisXR"] = m_controller.flipAxis[2];
    data["Controller"]["FlipAxisYR"] = m_controller.flipAxis[3];

    for (const auto &[k, v] : m_keyboard.inputMap) data["Keyboard"]["InputMap"][k] = v;
    for (const auto &[k, v] : m_mouse.inputMap) data["Mouse"]["InputMap"][k] = v;
    for (const auto &[k, v] : m_controller.buttonsInputMap) data["Controller"]["ButtonsInputMap"][k] = v;
    for (const auto &[k, v] : m_controller.sticksInputMap) data["Controller"]["SticksInputMap"][k] = v;
    for (const auto &[k, v] : m_controller.triggersInputMap) data["Controller"]["TriggersInputMap"][k] = v;

    core::WriteJSON(L"InputSettings.json", data);
}

const InputSystem *InputSystem::Get() noexcept { return m_instance; }

std::unique_ptr<InputSystem> InputSystem::CreateNative() noexcept {
#ifdef PLATFORM_WINDOWS
    return std::make_unique<platform::Win32InputSystem>();
#endif
}

}  // namespace Rake::core
