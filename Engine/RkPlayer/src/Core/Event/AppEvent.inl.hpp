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
#include "Core/RkApplication/AppFramework.hpp"

namespace Rake::Core
{

class AppEvent final : public RkEvent
{
  public:
    AppEvent(){};
};

} // namespace Rake::Core
