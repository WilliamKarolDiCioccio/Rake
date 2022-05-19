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

enum class EventCategory : U32
{
    ApplicationEvent = 0x0001,
    WindowEvent = 0x0002
};

#define APPLICATION_EVENT EventCategory::ApplicationEvent
#define WINDOW_EVENT      EventCategory::WindowEvent

enum class EventType : U32
{
    ShutdownRequest = 0x0001
};

#define SHUTDOWN_REQUEST EventType::ShutdownRequest

class RkEvent
{
  private:
    EventCategory m_category;
    EventType m_type;

  public:
    RkEvent(EventCategory _category, EventType _type) : m_category(_category), m_type(_type){};
    ~RkEvent(){};

  public:
    EventCategory GetCategory() const
    {
        return m_category;
    }

    EventType GetType() const
    {
        return m_type;
    }
};

#define RK_BIND_ON_EVENT(action) this->action;

} // namespace Rake::Core
