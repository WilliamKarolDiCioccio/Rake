#pragma once

#include "Common.def.h"

namespace Rake::Renderer
{

class Pipeline
{
  public:
    virtual ~Pipeline() = default;

  public:
    virtual bool CreateDevice();
};

} // namespace Rake::Renderer
