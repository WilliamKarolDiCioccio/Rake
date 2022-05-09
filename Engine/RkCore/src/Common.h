/*****************************************************************/ /**
 * \file   Common.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include <RkBase/internal/Config.h>

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

} // namespace Rake

#if defined(COMPILER_MSVC)
#define VA_ARGS(...) __VA_ARGS__
#ifdef PLAYER_EXPORT
#define __RAKE_API __declspec(dllexport)
#else
#define __RAKE_API __declspec(dllimport)
#endif
#define __RK_INLINE   __forceinline
#define __RK_NOINLINE __declspec(noinline)
#define __DECL_CALL   __cdecl
#elif defined(COMPILER_CLANG) || defined(COMPILER_GCC)
#define VA_ARGS(...) ##__VA_ARGS__
#ifdef PLAYER_EXPORT
#define __RAKE_API __attribute__((visibility("default")))
#else
#define __RAKE_API
#endif
#define __RK_INLINE   __attribute__((always_inline)) inline
#define __RK_NOINLINE __attribute__((noinline))
#define __DECL_CALL   __stdcall
#else
#error "Unable to specify compiler macros"
#endif

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

#define FORWARD(Args, args) std::forward<Args>(args)...
