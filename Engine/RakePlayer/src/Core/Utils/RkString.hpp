/*****************************************************************/ /**
 * \file   RkString.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include <string>
#include <cctype>

#include "Common.h"

namespace Rake
{
namespace Utils
{

static inline std::string Repeat(std::string _str, U32 _iterations)
{
    std::string repeated = _str;

    for (U32 i = 0; i < _iterations; i++)
    {
        repeated += _str;
    }

    return repeated;
}

} // namespace Utils
} // namespace Rake
