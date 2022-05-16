#pragma once

#include "Common.def.h"

namespace Rake::Renderer
{

enum class RendererType : U32
{
    DirectX = 0xFF,
    Vulkan = 0x0F,
    Metal = 0x00
};

typedef struct RendererData
{
} RendererData;

class Renderer final
{
  public:
    virtual ~Renderer() = default;

  public:
    virtual bool Init(RendererType _type) = 0;
    virtual void Deinit() = 0;
};

} // namespace Rake::Renderer
