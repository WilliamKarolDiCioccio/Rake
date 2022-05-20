/*****************************************************************/ /**
 * \file   Common.def.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include <RkBase/internal/Config.h>

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

static_assert(sizeof(U8) == 1);
static_assert(sizeof(U16) == 2);
static_assert(sizeof(U32) == 4);
static_assert(sizeof(U64) == 8);
static_assert(sizeof(I8) == 1);
static_assert(sizeof(I16) == 2);
static_assert(sizeof(I32) == 4);
static_assert(sizeof(I64) == 8);
static_assert(sizeof(F32) == 4);
static_assert(sizeof(F64) == 8);
static_assert(sizeof(B32) == 4);
static_assert(sizeof(B8) == 1);

#include <stdint.h>

using UI32 = uint_fast32_t;
using UI64 = uint_fast64_t;

static_assert(sizeof(UI32) == 4);
static_assert(sizeof(UI64) == 8);

#include <wchar.h>

using CHAR16 = char16_t;
using CHAR32 = char32_t;

static_assert(sizeof(CHAR16) == 2);
static_assert(sizeof(CHAR32) == 4);

#if defined(COMPILER_MSVC)
#define VA_ARGS(...) __VA_ARGS__
#ifdef PLAYER_EXPORT
#define RAKE_API __declspec(dllexport)
#else
#define RAKE_API __declspec(dllimport)
#endif
#define RK_INLINE   __forceinline
#define RK_NOINLINE __declspec(noinline)
#define DECL_CALL   __cdecl
#define ALIGNOF     __alignof
#elif defined(COMPILER_CLANG) || defined(COMPILER_GCC)
#define VA_ARGS(...) ##__VA_ARGS__
#ifdef PLAYER_EXPORT
#define RAKE_API __attribute__((visibility("default")))
#else
#define RAKE_API
#endif
#define RK_INLINE   __attribute__((always_inline)) inline
#define RK_NOINLINE __attribute__((noinline))
#define DECL_CALL   __stdcall
#define ALIGNOF
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
