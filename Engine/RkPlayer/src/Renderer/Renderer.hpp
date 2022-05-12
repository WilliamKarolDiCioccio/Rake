#pragma once

#include "Common.h"

namespace Rake
{
namespace Player
{

enum class RendererType
{
    Vulkan,
    DirectX,
    Metal
};

typedef struct RendererData
{
} RendererData;

class Renderer
{
  public:
    F32 m_clearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};

  public:
    virtual ~Renderer() = default;

    virtual bool Init() = 0;
    virtual void Deinit() = 0;

    virtual void ResizeViewport() = 0;
    virtual void ClearScreen() = 0;
};

} // namespace Player

} // namespace Rake
