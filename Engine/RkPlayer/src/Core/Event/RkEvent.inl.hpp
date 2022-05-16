/*****************************************************************/ /**
 * \file   RkEvent.inl.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   April 2022
 *********************************************************************/

#pragma once

#include "Common.def.h"

namespace Rake::Core
{

enum class EventType : U32
{
    ShutdownRequest = 0xF
};

class RkEvent final
{
  public:
    EventType m_type;

  public:
    RkEvent(EventType _type) : m_type(_type){};

  public:
    inline EventType GetType() const
    {
        return m_type;
    }
};

#define SHUTDOWN_REQUEST EventType::ShutdownRequest

} // namespace Rake::Core
