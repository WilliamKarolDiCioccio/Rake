#pragma once

#include "RKRuntime/base.hpp"

#ifdef PLATFORM_WINDOWS

#include "RKRuntime/core/input_system.hpp"

#include "win32_common.hpp"

#include <GameInput.h>

namespace Rake::platform::Win32 {

class Win32InputSystem final : public core::InputSystem {
   private:
    Microsoft::WRL::ComPtr<IGameInput> m_gameInput;

    GameInputCallbackToken deviceCallbackToken = NULL;

    Microsoft::WRL::ComPtr<IGameInputDevice> m_keyboardDevice;
    Microsoft::WRL::ComPtr<IGameInputDevice> m_mouseDevice;
    Microsoft::WRL::ComPtr<IGameInputDevice> m_gamepadDevice;

    Microsoft::WRL::ComPtr<IGameInputReading> m_reading;

   public:
    Win32InputSystem();
    ~Win32InputSystem() override;

   public:
    void Poll() noexcept override;

   private:
    static void CALLBACK DeviceCallback(
        _In_ GameInputCallbackToken callbackToken,
        _In_ void *context,
        _In_ IGameInputDevice *device,
        _In_ uint64_t timestamp,
        _In_ GameInputDeviceStatus currentStatus,
        _In_ GameInputDeviceStatus previousStatus) noexcept;
};

}  // namespace Rake::platform::Win32

#endif
