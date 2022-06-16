/*****************************************************************/ /**
 * \file   Config.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   April 2022
 *********************************************************************/

#pragma once

#if defined(COMPILER_MSVC)
#define DLL_EXPORT  __declspec(dllexport)
#define DLL_IMPORT  __declspec(dllimport)
#define RK_INLINE   __forceinline
#define RK_NOINLINE __declspec(noinline)
#define DECL_CALL   __cdecl
#define ALIGNOF     __alignof
#elif defined(COMPILER_CLANG) || defined(COMPILER_GCC)
#define DLL_EXPORT __attribute__((visibility("default")))
#define DLL_IMPORT
#define RK_INLINE   __attribute__((always_inline)) inline
#define RK_NOINLINE __attribute__((noinline))
#define DECL_CALL   __stdcall
#define ALIGNOF
#endif