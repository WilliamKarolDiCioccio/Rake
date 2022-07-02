/*****************************************************************/ /**
 * \file   Base.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   June 2022
 *********************************************************************/

#pragma once

#include "Tools/Assert.h"

#if defined(COMPILER_MSVC)
#define DLL_EXPORT     __declspec(dllexport)
#define DLL_IMPORT     __declspec(dllimport)
#define RK_INLINE      __forceinline
#define RK_NOINLINE    __declspec(noinline)
#define DECL_CALL      __cdecl
#define SIZEOF(object) sizeof(object)
#define ALIGNOF(type)  __alignof(type)
#define ALIGNAS(size)  alignas(size)
#elif defined(COMPILER_CLANG) || defined(COMPILER_GCC)
#define DLL_EXPORT __attribute__((visibility("default")))
#define DLL_IMPORT
#define RK_INLINE   __attribute__((always_inline)) inline
#define RK_NOINLINE __attribute__((noinline))
#define DECL_CALL   __stdcall
#define ALIGNOF(type)
#define ALIGNAS(size)
#endif

#if defined(PLAYER_EXPORT)
#define RAKE_API DLL_EXPORT
#else
#define RAKE_API DLL_IMPORT
#endif

/**********************************************************************/

#include <wchar.h>
#include <stdint.h>

namespace Rake
{

using U8 = unsigned char;
using U16 = unsigned short;
using U32 = unsigned int;
using U64 = unsigned long long;
using I8 = signed char;
using I16 = signed short;
using I32 = signed int;
using I64 = signed long long;
using F32 = float;
using F64 = double;
using B32 = int;
using B8 = bool;

RK_STATIC_ASSERT(sizeof(U8) == 1);
RK_STATIC_ASSERT(sizeof(U16) == 2);
RK_STATIC_ASSERT(sizeof(U32) == 4);
RK_STATIC_ASSERT(sizeof(U64) == 8);
RK_STATIC_ASSERT(sizeof(I8) == 1);
RK_STATIC_ASSERT(sizeof(I16) == 2);
RK_STATIC_ASSERT(sizeof(I32) == 4);
RK_STATIC_ASSERT(sizeof(I64) == 8);
RK_STATIC_ASSERT(sizeof(F32) == 4);
RK_STATIC_ASSERT(sizeof(F64) == 8);
RK_STATIC_ASSERT(sizeof(B32) == 4);
RK_STATIC_ASSERT(sizeof(B8) == 1);

} // namespace Rake

/**********************************************************************/

#define GIBIBYTES(amount) amount * 1024 * 1024 * 1024
#define MEBIBYTES(amount) amount * 1024 * 1024
#define KIBIBYTES(amount) amount * 1024

#define GIGABYTES(amount) amount * 1000 * 1000 * 1000
#define MEGABYTES(amount) amount * 1000 * 1000
#define KILOBYTES(amount) amount * 1000

#define SET_BIT(byte, bitPos)   ((byte) |= (1 << (bitPos)))
#define CLEAR_BIT(byte, bitPos) ((byte) &= ~(1 << (bitPos)))
#define FLIP_BIT(byte, bitPos)  ((byte) ^= (1 << (bitPos)))
#define CHECK_BIT(byte, bitPos) ((byte) & (1 << (bitPos)))

#define INCLUSIVE_CLAMP(x, min, max) (x <= min) ? min : (x >= max) ? max : x
#define EXCLUSIVE_CLAMP(x, min, max) (x < min) ? min : (x > max) ? max : x

/**********************************************************************/

#include <stdlib.h>
#include <signal.h>

namespace Rake
{

static inline void RaiseInterrupt(int _signum)
{
    exit(_signum);
}

} // namespace Rake

#define RK_SIGINT  Rake::RaiseInterrupt(SIGINT)
#define RK_SIGILL  Rake::RaiseInterrupt(SIGILL)
#define RK_SIGFPE  Rake::RaiseInterrupt(SIGFPE)
#define RK_SIGSEGV Rake::RaiseInterrupt(SIGSEGV)
#define RK_SIGTERM Rake::RaiseInterrupt(SIGTERM)
#define RK_SIGABRT Rake::RaiseInterrupt(SIGABRT)
