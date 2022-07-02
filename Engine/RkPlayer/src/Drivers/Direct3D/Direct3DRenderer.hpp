#pragma once

#if defined(PLATFORM_WINDOWS)

#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>

#include "Engine/Renderer/Renderer.hpp"

namespace Rake::Drivers::Direct3D
{

class Direct3DRenderer : public Engine::Graphics::Renderer
{
  private:
    B8 m_useWARP = false;

  public:
    Direct3DRenderer();

  public:
    B8 InitAPI() override;

  private:
    B8 CheckDeviceSuitability() override;
    U32 RateDeviceSuitability() override;
    B8 CheckDeviceExtensionSupport() override;
};

} // namespace Rake::Drivers::Direct3D

#endif
