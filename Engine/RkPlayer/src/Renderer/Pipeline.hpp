#pragma once

#include "Common.def.h"

namespace Rake::Renderer
{

class Pipeline
{
  public:
    virtual ~Pipeline() = default;

  public:
    virtual bool Init() = 0;
    virtual void Release() = 0;
};

} // namespace Rake::Renderer
