/*****************************************************************/ /**
 * \file   RkEvent.inl.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   May 2022
 *********************************************************************/

#pragma once

#include "Common.def.h"

namespace Rake::Core
{

enum class EventType : U32
{
    ShutdownRequest = 0x0001
};

enum class EventCategory : U32
{
    ApplicationEvent = 0x0001
};

class RkEvent
{
  private:
    EventType m_type;

  public:
    RkEvent(EventType _type) : m_type(_type){};
    ~RkEvent(){};

  public:
    EventType GetType() const
    {
        return m_type;
    }
};

#define RK_BIND_ON_EVENT(action) this->action;

#define SHUTDOWN_REQUEST EventType::ShutdownRequest()

} // namespace Rake::Core
