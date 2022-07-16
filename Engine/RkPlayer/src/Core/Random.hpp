/*****************************************************************/ /**
 * \file   Random.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include <ctime>
#include <random>
#include <wchar.h>

#include "Core/Base.hpp"

namespace Rake::Core
{

static const char alphaNum[] = "0123456789"
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                               "abcdefghijklmnopqrstuvwxyz";

static inline std::string RandString(B32 _len)
{
    INCLUSIVE_CLAMP(_len, 1, 255);

    std::string temp;
    temp.reserve(_len);

    for (int i = 0; i < _len; ++i)
        temp += alphaNum[rand() % (sizeof(alphaNum) - 1)];

    return temp;
}

} // namespace Rake::Core
