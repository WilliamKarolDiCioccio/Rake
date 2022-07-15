/*****************************************************************/ /**
 * \file   Event.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   July 2022
 *********************************************************************/

#pragma once

#include <functional>

#include "Core/Base.hpp"

namespace Rake::Core
{

enum class EventCategory : U32
{
    ApplicationEvent,
    WindowEvent
};

class Event
{
  private:
    EventCategory m_category;
    B8 m_isHandled;

  protected:
    virtual ~Event();

  public:
    EventCategory GetCategory() const
    {
        return this->m_category;
    }

    void Discard(B8 _discard)
    {
        m_isHandled = _discard;
    }
};

} // namespace Rake::Core
