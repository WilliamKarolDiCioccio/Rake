#pragma once

namespace Rake::Engine::Graphics
{

enum class GraphicsAPI : U32
{
    DirectX12 = 4
};

class Renderer
{
  private:
    static B8 m_isInitialized;

  public:
    virtual ~Renderer() = default;
    static std::unique_ptr<Renderer> CreateRenderer();

  public:
    virtual B8 InitAPI() = 0;

  protected:
    virtual B8 CheckDeviceSuitability() = 0;
    virtual U32 RateDeviceSuitability() = 0;
    virtual B8 CheckDeviceExtensionSupport() = 0;
};

} // namespace Rake::Engine::Graphics

#define API_DIRECTX Rake::Engine::Graphics::GraphicsAPI::DirectX12
