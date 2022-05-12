/*****************************************************************/ /**
 * \file   ConfigLoader.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   April 2022
 *********************************************************************/

#pragma once

#include <nlohmann/json.hpp>

#include "Common.h"

namespace Rake::Core
{

class ConfigLoader final
{
  public:
    static void ReadFrom(const char *_fileAbsolutePath);

  private:
};

} // namespace Rake::Core
