#pragma(suppress : 4100)

#include "pch.hpp"

#include "platform/win32/win32_input_system.hpp"

#ifdef PLATFORM_WINDOWS

namespace Rake::platform::Win32 {

void CALLBACK Win32InputSystem::DeviceCallback(
    _In_ GameInputCallbackToken callbackToken,
    _In_ void *context,
    _In_ IGameInputDevice *device,
    _In_ uint64_t timestamp,
    _In_ GameInputDeviceStatus currentStatus,
    _In_ GameInputDeviceStatus previousStatus) noexcept {
    const GameInputDeviceInfo *deviceInfo = device->GetDeviceInfo();
    const GameInputKind deviceKind = deviceInfo->supportedInput;

    if (!(previousStatus & GameInputDeviceConnected) && (currentStatus & GameInputDeviceConnected)) {
        if (deviceKind & GameInputKindKeyboard) {
            RK_LOG_DEBUG(L"Connected Keyboard device!");
        } else if (deviceKind & GameInputKindMouse) {
            RK_LOG_DEBUG(L"Connected Mouse device!");
        } else if (deviceKind & GameInputKindGamepad) {
            RK_LOG_DEBUG(L"Connected Controller device!");
        }
    } else if ((previousStatus & GameInputDeviceConnected) && !(currentStatus & GameInputDeviceConnected)) {
        if (deviceKind & GameInputKindKeyboard) {
            RK_LOG_DEBUG(L"Disconnected Keyboard device!");
        } else if (deviceKind & GameInputKindMouse) {
            RK_LOG_DEBUG(L"Disconnected Mouse device!");
        } else if (deviceKind & GameInputKindGamepad) {
            RK_LOG_DEBUG(L"Disconnected Controller device!");
        }
    }

    GameInputBatteryState batteryState = {};
    device->GetBatteryState(&batteryState);
}

Win32InputSystem::Win32InputSystem() {
    HRESULT hResult = GameInputCreate(&m_gameInput);

    if (FAILED(hResult)) throw RkException(L"GameInput failed to initialize: {}", hResult);

    hResult = m_gameInput->RegisterDeviceCallback(
        nullptr,
        GameInputKindGamepad | GameInputKindKeyboard | GameInputKindMouse,
        GameInputDeviceAnyStatus,
        GameInputAsyncEnumeration,
        this,
        &DeviceCallback,
        &deviceCallbackToken);

    if (FAILED(hResult)) throw RkException(L"GameInput failed to register device callback: {}", hResult);
}

Win32InputSystem::~Win32InputSystem() { m_gameInput->UnregisterCallback(deviceCallbackToken, UINT64_MAX); }

void Win32InputSystem::Poll() noexcept {
    m_keyboard.lastInputState = std::move(m_keyboard.inputState);
    m_mouse.lastInputState = std::move(m_mouse.inputState);
    m_controller.lastInputState = std::move(m_controller.inputState);

    m_keyboard.inputState = {};
    m_mouse.inputState = {};
    m_controller.inputState = {};

    if (SUCCEEDED(m_gameInput->GetCurrentReading(GameInputKindKeyboard, m_keyboardDevice.Get(), &m_reading))) {
        const UINT count = m_reading->GetKeyCount();

        if (count) {
            GameInputKeyState state[16] = {};

            if (m_reading->GetKeyState(_countof(state), state)) {
                for (UINT index = 0; index < count; ++index) {
                    UINT8 key = state[index].virtualKey;

                    m_keyboard.inputState.keyDown[key] = true;
                }
            }
        }
    }

    if (SUCCEEDED(m_gameInput->GetCurrentReading(GameInputKindMouse, m_mouseDevice.Get(), &m_reading))) {
        GameInputMouseState state = {};

        if (m_reading->GetMouseState(&state)) {
            m_mouse.inputState.cursorPosition.x = static_cast<float>(-state.positionX);
            m_mouse.inputState.cursorPosition.y = static_cast<float>(-state.positionY);
            m_mouse.inputState.wheelDelta = static_cast<float>(state.wheelY - m_mouse.lastInputState.wheelDelta);

            m_mouse.inputState.buttons[(uint8_t)RK_MOUSE_BUTTON_L] = state.buttons & GameInputMouseLeftButton;
            m_mouse.inputState.buttons[(uint8_t)RK_MOUSE_BUTTON_R] = state.buttons & GameInputMouseRightButton;
            m_mouse.inputState.buttons[(uint8_t)RK_MOUSE_BUTTON_M] = state.buttons & GameInputMouseMiddleButton;
            m_mouse.inputState.buttons[(uint8_t)RK_MOUSE_BUTTON_4] = state.buttons & GameInputMouseButton4;
            m_mouse.inputState.buttons[(uint8_t)RK_MOUSE_BUTTON_5] = state.buttons & GameInputMouseButton5;
        }
    }

    if (SUCCEEDED(m_gameInput->GetCurrentReading(GameInputKindGamepad, m_gamepadDevice.Get(), &m_reading))) {
        GameInputGamepadState state = {};

        if (m_reading->GetGamepadState(&state)) {
            m_controller.inputState.sticks[(uint8_t)RK_CONTROLLER_AXIS_L].x = state.leftThumbstickX;
            m_controller.inputState.sticks[(uint8_t)RK_CONTROLLER_AXIS_L].y = state.leftThumbstickY;
            m_controller.inputState.sticks[(uint8_t)RK_CONTROLLER_AXIS_R].x = state.rightThumbstickX;
            m_controller.inputState.sticks[(uint8_t)RK_CONTROLLER_AXIS_R].y = state.rightThumbstickY;
            m_controller.inputState.triggers[(uint8_t)RK_CONTROLLER_TRIGGER_L] = state.leftTrigger;
            m_controller.inputState.triggers[(uint8_t)RK_CONTROLLER_TRIGGER_R] = state.rightTrigger;

            m_controller.inputState.buttons[(uint8_t)RK_CONTROLLER_BUTTON_A] = state.buttons & GameInputGamepadA;
            m_controller.inputState.buttons[(uint8_t)RK_CONTROLLER_BUTTON_B] = state.buttons & GameInputGamepadB;
            m_controller.inputState.buttons[(uint8_t)RK_CONTROLLER_BUTTON_X] = state.buttons & GameInputGamepadX;
            m_controller.inputState.buttons[(uint8_t)RK_CONTROLLER_BUTTON_Y] = state.buttons & GameInputGamepadY;
            m_controller.inputState.buttons[(uint8_t)RK_CONTROLLER_BUTTON_UP] = state.buttons & GameInputGamepadDPadUp;
            m_controller.inputState.buttons[(uint8_t)RK_CONTROLLER_BUTTON_DOWN] =
                state.buttons & GameInputGamepadDPadDown;
            m_controller.inputState.buttons[(uint8_t)RK_CONTROLLER_BUTTON_L] = state.buttons & GameInputGamepadDPadLeft;
            m_controller.inputState.buttons[(uint8_t)RK_CONTROLLER_BUTTON_R] =
                state.buttons & GameInputGamepadDPadRight;
            m_controller.inputState.buttons[(uint8_t)RK_CONTROLLER_SHOULDER_L] =
                state.buttons & GameInputGamepadLeftShoulder;
            m_controller.inputState.buttons[(uint8_t)RK_CONTROLLER_SHOULDER_R] =
                state.buttons & GameInputGamepadRightShoulder;
        }
    }
}

}  // namespace Rake::platform::Win32

#endif
