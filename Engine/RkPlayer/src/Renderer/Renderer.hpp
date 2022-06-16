#pragma once

#include "Types.h"

namespace Rake::Renderer
{

enum class RendererAPI : U32
{
    DirectX12 = 1,
    Metal = 2,
    OpenGL = 3,
    Vulkan = 4
};

enum class RendererType : U32
{
    _2D = 1,
    _3D = 2
};

class Renderer final
{
  private:
    static Renderer *m_rendererInstance;

  public:
    Renderer(const RendererAPI _rendererApi, const RendererType _type);

  public:
    B8 Init();
    void Release();

  public:
    virtual void Present() = 0;

  private:
    virtual void InitAPI() = 0;
    virtual void CreateSurface() = 0;
    virtual void SetupDevice() = 0;
    virtual void DestroyDevice() = 0;
    virtual void SetupSwapChain() = 0;
    virtual void DestroySwapChain() = 0;

  private:
    virtual void PickPhysicalDevice() = 0;
    virtual void CreateLogicalDevive() = 0;
    virtual void ConfigureSwapCahin() = 0;
    virtual void CreateSwapChain() = 0;

  public:
    virtual B8 CheckDeviceSuitability() = 0;
    virtual U32 RateDeviceSuitability() = 0;
    virtual B8 CheckDeviceExtensionSupport() = 0;
};

} // namespace Rake::Renderer

#define API_DIRECTX Rake::Renderer::RendererAPI::DirectX12
#define API_METAL   Rake::Renderer::RendererAPI::Metal
#define API_OPENGL  Rake::Renderer::RendererAPI::OpenGL
#define API_VULKAN  Rake::Renderer::RendererAPI::Vulkan

#define _2D Rake::Renderer::RendererType::_2D
#define _3D Rake::Renderer::RendererType::_3D
