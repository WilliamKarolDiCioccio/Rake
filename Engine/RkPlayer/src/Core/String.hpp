/*****************************************************************/ /**
 * \file   String.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include <wchar.h>
#include <vector>

#include "Core/Base.hpp"

namespace Rake::Core
{

static inline std::string Stringify()
{
    std::wstringstream wss;

    return "";
}
static inline void Reverse(std::string &_string)
{
    std::reverse(_string.begin(), _string.end());
}

static inline U32 CountWords()
{
    return NULL;
}

static inline std::vector<wchar_t *> GetWords()
{
}

} // namespace Rake::Core
