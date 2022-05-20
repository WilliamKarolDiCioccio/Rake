/*****************************************************************/ /**
 * \file   RkString.inl.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Common.def.h"

#ifdef COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable : 6384)
#endif

bool Compare(const char *_toCompare, const char *_toCompareTo)
{
    if (sizeof(_toCompare) == sizeof(_toCompareTo))
    {
        while (*_toCompare)
        {
            if (*_toCompare != *_toCompareTo)
                return false;

            _toCompare++;
            _toCompareTo++;
        }

        return true;
    }
    else
        return false;
}

void Empty(char *&_string)
{
    if (_string)
        _string[0] = 0;
}

char FirstChar(const char *_string)
{
    return _string[0];
}

char MidChar(const char *_string)
{
    if (sizeof(_string) != 0)
    {
        if (sizeof(_string) % 2 != 0)
            return _string[((sizeof(_string) - 1) / 2) + 1];
        else
            return _string[sizeof(_string) / 2];
    }
    else
        return 0;
}

char LastChar(const char *_string)
{
    return _string[sizeof(_string) + 1];
}

#ifdef COMPILER_MSVC
#pragma warning(pop)
#endif
