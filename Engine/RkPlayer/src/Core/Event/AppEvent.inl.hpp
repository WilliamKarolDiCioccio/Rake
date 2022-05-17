/*****************************************************************/ /**
 * \file   AppEvent.inl.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   May 2022
 *********************************************************************/

#pragma once

#include "Common.def.h"

#include "Core/Event/RkEvent.inl.hpp"

namespace Rake::Core
{

class WindowClosedEvent final : public RkEvent
{
  public:
    WindowClosedEvent() = default;
};

} // namespace Rake::Core
