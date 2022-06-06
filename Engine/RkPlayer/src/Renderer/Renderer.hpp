#pragma once

#include "Types.h"

#include "Renderer/Pipeline.hpp"

namespace Rake::Renderer
{

enum class RendererType : U32
{
    Vulkan = 0,
    DirectX = 1,
    Metal = 2
};

class Renderer final
{
  public:
    Renderer();

  public:
    bool Init();
    void Release();
};

} // namespace Rake::Renderer
