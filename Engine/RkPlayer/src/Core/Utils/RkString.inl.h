/*****************************************************************/ /**
 * \file   RkString.inl.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Types.h"

#ifdef COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable : 6384)
#endif

template <typename T> B32 StrCompare(const T *_toCompare, const T *_toCompareTo)
{
    while (*_toCompare == *_toCompareTo && _toCompareTo != '\0')
    {
        _toCompare++;
        _toCompareTo++;
    }

    return (B32)(T)(*_toCompare) - (B32)(T)(*_toCompareTo);
}

template <typename T> void EmptyStr(T *&_string)
{
    return _string[0] = '\0';
}

template <typename T> T FirstStrChar(const T *_string)
{
    return _string[0];
}

template <typename T> T LastStrChar(const T *_string)
{
    return _string[sizeof(_string)];
}

#ifdef COMPILER_MSVC
#pragma warning(pop)
#endif
