/*****************************************************************/ /**
 * \file   Config.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   April 2022
 *********************************************************************/

#pragma once

#if defined(__x86_64__) || defined(_M_X64) || defined(__amd64__)
#define ARCHITECTURE_X86_64
#define ARCHITECTURE_NAME "x86_64 64-bits"
#elif defined(__i386__) || defined(_M_IX86) || defined(__X86__) || defined(_X86_)
#define ARCHITECTURE_X86
#define ARCHITECTURE_NAME "i386 32-bits"
#elif defined(__aarch64__) || defined(_M_ARM64)
#define ARCHITECTURE_ARM_64
#define ARCHITECTURE_NAME "ARM 64-bits"
#elif defined(__arm__) || defined(_M_ARM)
#define ARCHITECTURE_ARM_32
#define ARCHITECTURE_NAME "x86_64 64-bits"
#elif defined(__powerpc64__) || defined(__ppc64__) || defined(__PPC64__) || defined(_ARCH_PPC64)
#define ARCHITECTURE_POWERPC_64
#define ARCHITECTURE_NAME "PowerPC 64-bits"
#elif defined(__powerpc__) || defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC)
#define ARCHITECTURE_POWERPC_32
#define ARCHITECTURE_NAME "PowerPC 32-bits"
#else
#error "Unsupported architecture"
#endif

#if defined(__SSE__)
#define X86_CPU_INSTR_SET
#define CPU_INSTR_SET_NAME "SSE"
#elif defined(__SSE2__)
#define X86_CPU_INSTR_SET
#define CPU_INSTR_SET_NAME "SSE2"
#elif defined(__SSE3__)
#define X86_CPU_INSTR_SET
#define CPU_INSTR_SET_NAME "SSE3"
#elif defined(__SSE4_1__)
#define X86_CPU_INSTR_SET
#define CPU_INSTR_SET_NAME "SSE41"
#elif defined(__SSE4_2__)
#define X86_CPU_INSTR_SET
#define CPU_INSTR_SET_NAME "SSE42"
#elif defined(__AVX__)
#define X86_CPU_INSTR_SET
#define CPU_INSTR_SET_NAME "AVX"
#elif defined(__AVX2__)
#define X86_CPU_INSTR_SET
#define CPU_INSTR_SET_NAME "AVX2"
#elif defined(__AVX512F__)
#define X86_CPU_INSTR_SET
#define CPU_INSTR_SET_NAME "AVX512F"
#else
#pragma message("No Instruction Set optimizations possible")
#endif

#if defined(__clang__)
#define COMPILER_CLANG 1
#define COMPILER_NAME  "Clang"
#elif defined(_MSC_VER)
#include <intrin.h>
#define COMPILER_MSVC 1
#define COMPILER_NAME "MSVC"
#elif defined(__GNUC__)
#define COMPILER_GCC  1
#define COMPILER_NAME "GCC"
#elif defined(__MINGW32__)
#define COMPILER_MINGW 1
#define COMPILER_NAME  "MinGW"
#elif defined(__INTEL_COMPILER)
#define COMPILER_INTEL 1
#define COMPILER_NAME  "Intel"
#elif defined(__CC_ARM)
#define COMPILER_ARM  1
#define COMPILER_NAME "ARM"
#elif defined(__IBMC__)
#define IBM_COMPILER  1
#define COMPILER_NAME "IBMC, XL family"
#elif defined()
#else
#error "Unsupported compiler"
#endif

#include <limits.h>

#if ((LLONG_MAX) == (INT_MAX))
#define ENVIROMENT_32_BITS
#pragma message("Running in 32-bits enviroment is not recommended!")
#else
#define ENVIROMENT_64_BITS
#endif

#if defined(__32BIT__)
#define COMPILER_INVOKED_32_BITS
#pragma message("While invoking a 32-bits compiler you cannot target 64-bits machines unless 'virtualization' is supported!")
#else
#define COMPILER_INVOKED_64_BITS
#endif

#if defined(_WIN64) || defined(_WIN32)
#define PLATFORM_NAME    "Windows"
#define PLATFORM_WINDOWS 1
#define DESKTOP_DEVICE   1
#elif defined(__linux__) && !defined(__ANDROID__)
#define PLATFORM_NAME  "Linux"
#define PLATFORM_LINUX 1
#define DESKTOP_DEVICE 1
#elif defined(__ANDROID__)
#define PLATFORM_NAME    "Android"
#define PLATFORM_ANDROID 1
#define MOBILE_DEVICE    1
#elif defined(__APPLE__)
#define PRODUCTOR_NAME "Apple"
#define PRODUCTOR_APPLE
#include <external/TargetConditionals.h>
#if TARGET_OS_MAC == 1
#define PLATFORM_MACOS 1
#define PLATFORM_NAME  "Mac"
#define DESKTOP_DEVICE 1
#elif TARGET_OS_IPHONE == 1
#define PLATFORM_IPHONE 1
#define PLATFORM_NAME   "Iphone"
#define MOBILE_DEVICE   1
#elif TARGET_IPHONE_SIMULATOR == 1
#define PLATFORM_IPHONE_SIMULATOR 1
#define PLATFORM_NAME             "Iphone simulator"
#define EMULATED_DEVICE           1
#pragma message("Emulator support is experimental!")
#else
#error Unsupported Apple platform!
#endif
#else
#error Usupported platform!
#endif

#if __cplusplus == 202002L
#define CPP_STANDARD 2020
#elif __cplusplus == 201703L
#define CPP_STANDARD 2017
#elif __cplusplus == 201402L
#define CPP_STANDARD 2014
#elif __cplusplus == 201103L
#define CPP_STANDARD 2011
#elif __cplusplus == 199711L
#define CPP_STANDARD 1998
#else
#error "Unsupported C/C++ standard!"
#endif

#if defined(__ANSI__)
#pragma message("The LANGLVL(*ANSI) compiler option is in effect, compiler only allows ANSI/ISO C/C++ standards.")
#endif

#if defined(__ANDROID_API__) < 9
#define NO_STANDARD_LIBRARY 1
#else
#define NO_STANDARD_LIBRARY 0
#endif

#if !defined(UNICODE) && !defined(_UNICODE)
#define SINGLE_BYTE_CHARSET
#elif defined(UNICODE) || defined(_UNICODE)
#define MULTI_BYTE_CHARSET
#endif
