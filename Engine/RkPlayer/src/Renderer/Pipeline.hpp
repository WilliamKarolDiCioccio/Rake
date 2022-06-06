#pragma once

#include "Types.h"

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
