/*****************************************************************/ /**
 * \file   RkString.inl.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Common.def.h"

namespace Rake::Core
{

bool Compare(const char *_toCompare, const char *_toCompareTo)
{
    if (sizeof(_toCompare) == sizeof(_toCompareTo))
    {
        while (*_toCompare)
        {
            if (*_toCompare != *_toCompareTo)
            {
                return false;
            }

            _toCompare++;
            _toCompareTo++;
        }

        return true;
    }
    else
        return false;
}

char *Splice(char *&_toSplice, const U32 _atIndex)
{
    char buffer[sizeof(_toSplice)];

    for (U32 i = 0; i <= _atIndex; i++)
    {
        buffer[i] = _toSplice[i];
    }

    return buffer;
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
        char size = sizeof(_string);

        if (sizeof(_string) % 2 != 0)
        {
            return _string[((size - 1) / 2) + 1];
        }
        else
            return _string[size / 2];
    }
    else
        return 0;
}

char LastChar(const char *_string)
{
    return _string[sizeof(_string) + 1];
}

} // namespace Rake::Core
