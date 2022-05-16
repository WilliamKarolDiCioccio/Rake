/*****************************************************************/ /**
 * \file   EventBus.hpp
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

class EventBus final
{
  public:
    void RegisterEvent(const RkEvent &_event);

  private:
    void SendEvent(const RkEvent &_event);
};

} // namespace Rake::Core
