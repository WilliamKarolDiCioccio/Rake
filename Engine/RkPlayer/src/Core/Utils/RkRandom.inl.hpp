/*****************************************************************/ /**
 * \file   RkRandom.inl.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include <stdlib.h>
#include <string>
#include <vector>

#include "Common.def.h"

namespace Rake::Core
{

class RkRandom final
{
  private:
    const char m_num[11] = "0123456789";
    const char m_charHigh[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char m_charLow[27] = "abcdefghijklmnopqrstuvwxyz";

  private:
    RkRandom() = default;

  public:
    static constexpr char *GenerateSring()
    {
        return;
    }

    static constexpr char *GenerateString(const U32 _lenght)
    {
        return;
    }

    static constexpr std::vector<U32> GenerateRGBColor()
    {
        U32 colorDepth = rand() % 255 + 1;

        return;
    }
};

} // namespace Rake::Core
