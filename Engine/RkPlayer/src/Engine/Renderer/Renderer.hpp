#pragma once

namespace Rake::Engine
{

enum class GraphicsAPI : U32
{
    Vulkan = 4
};

class Renderer
{
  private:
    static B8 m_isInitialized;

  public:
    virtual ~Renderer() = default;
    static std::unique_ptr<Renderer> CreateRenderer(GraphicsAPI _api);

  protected:
    virtual B8 InitAPI() = 0;
    virtual void ReleaseAPI() = 0;
};

} // namespace Rake::Engine

#define API_VULKAN Rake::Engine::GraphicsAPI::Vulkan
