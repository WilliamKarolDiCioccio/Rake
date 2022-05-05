/*****************************************************************/ /**
 * \file   RkEventHandler.inl.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   April 2022
 *********************************************************************/

#pragma once

#include <stack>
#include <queue>

#include "Common.h"

#include "Core/Event/RkEvent.inl.hpp"

namespace Rake::Core
{

class EventBus
{
  public:
    virtual void Dispatch(RkEvent _event) noexcept = 0;

  public:
    void AddEvent()
    {
    }

    void RemoveEvent()
    {
    }

  protected:
    std::queue<RkEvent> m_eventQueue;
};

} // namespace Rake::Core
