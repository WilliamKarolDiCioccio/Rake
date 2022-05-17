/*****************************************************************/ /**
 * \file   EventBus.hpp
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
  public:
    void Dispatch(const RkEvent &_event) noexcept
    {
        switch (_event.GetType())
        {
        default:
            break;
        }
    }
};

} // namespace Rake::Core
