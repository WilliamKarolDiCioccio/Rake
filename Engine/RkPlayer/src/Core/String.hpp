/*****************************************************************/ /**
 * \file   String.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include <wchar.h>
#include <cstdint>

#include "Core/Base.hpp"

namespace Rake::Core
{

using StringID = uint32_t;

static inline wchar_t *ASCIIToUTF8()
{
    return nullptr;
}

static inline char *UTF8ToASCII()
{
    return nullptr;
}

} // namespace Rake::Core
