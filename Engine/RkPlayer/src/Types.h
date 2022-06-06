/*****************************************************************/ /**
 * \file   Types.h
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
