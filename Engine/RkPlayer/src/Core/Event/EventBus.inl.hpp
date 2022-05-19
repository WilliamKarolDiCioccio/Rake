/*****************************************************************/ /**
 * \file   EventBus.inl.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   May 2022
 *********************************************************************/

#pragma once

#include <queue>

#include "Common.def.h"

#include "Core/Event/RkEvent.inl.hpp"

namespace Rake::Core
{

class EventBus
{
  private:
    EventBus() = default;

  public:
    static void Dispatch(const RkEvent &_event) noexcept
    {
        switch (_event.GetCategory())
        {
        case APPLICATION_EVENT: {
        }
        case WINDOW_EVENT: {
        }
        default:
            break;
        }
    }
};

} // namespace Rake::Core
