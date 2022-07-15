/*****************************************************************/ /**
 * \file   EventBus.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   July 2022
 *********************************************************************/

#pragma once

#include <unordered_map>

#include "Core/Base.hpp"
#include "Event.hpp"

namespace Rake::Core
{

class EventBus final
{
  private:
    std::unordered_map<EventCategory, U32> m_observers;

  public:
    void Dispatch(const Event &_event)
    {
        if (m_observers.find(_event.GetCategory()) == m_observers.end())
            return;
    }
};

} // namespace Rake::Core
