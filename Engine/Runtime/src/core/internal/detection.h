#pragma once

#if defined(__x86_64__) || defined(_M_X64) || defined(__amd64__)
#define ARCHITECTURE_X86_64
#define ARCHITECTURE_NAME "x86_64"
#elif defined(__i386__) || defined(_M_IX86) || defined(__X86__) || defined(_X86_)
#define ARCHITECTURE_X86
#define ARCHITECTURE_NAME "i386"
#elif defined(__aarch64__) || defined(_M_ARM64)
#define ARCHITECTURE_ARM_64
#define ARCHITECTURE_NAME "ARM64"
#elif defined(__arm__) || defined(_M_ARM)
#define ARCHITECTURE_ARM_32
#define ARCHITECTURE_NAME "ARM32"
#elif defined(__powerpc64__) || defined(__ppc64__) || defined(__PPC64__) || defined(_ARCH_PPC64)
#define ARCHITECTURE_POWERPC_64
#define ARCHITECTURE_NAME "PowerPC64"
#elif defined(__powerpc__) || defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) ||      \
    defined(_ARCH_PPC)
#define ARCHITECTURE_POWERPC_32
#define ARCHITECTURE_NAME "PowerPC32"
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
#endif

#if defined(__clang__)
#define COMPILER_CLANG 1
#define COMPILER_NAME  "Clang"
#elif defined(_MSC_VER)
#include <intrin.h>
#define COMPILER_MSVC 1
#define COMPILER_NAME "MSVC"
#endif

#if defined(_WIN64) || defined(_WIN32)
#define PLATFORM_NAME    "Windows"
#define PLATFORM_WINDOWS 1
#define DESKTOP_DEVICE   1
#elif defined(__ANDROID__)
#define PLATFORM_NAME    "Android"
#define PLATFORM_ANDROID 1
#define MOBILE_DEVICE    1
#endif

#if __cplusplus == 202002L
#define CPP_STANDARD_20
#elif __cplusplus == 201703L
#define CPP_STANDARD_17
#endif

#if !defined(UNICODE) && !defined(_UNICODE)
#define SINGLE_BYTE_CHARSET
#elif defined(UNICODE) || defined(_UNICODE)
#define MULTI_BYTE_CHARSET
#endif
