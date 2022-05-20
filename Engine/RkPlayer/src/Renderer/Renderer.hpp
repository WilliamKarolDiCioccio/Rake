#pragma once

#include "Common.def.h"

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
    virtual ~Renderer() = default;
};

} // namespace Rake::Renderer
