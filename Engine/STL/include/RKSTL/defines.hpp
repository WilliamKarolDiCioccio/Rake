#pragma once

#include "assert.h"
#include "warnings.h"

#ifdef COMPILER_MSVC
#define DLL_EXPORT       __declspec(dllexport)
#define DLL_IMPORT       __declspec(dllimport)
#define FORCE_INLINE     __forceinline
#define PROHIBIT_INLINE  __declspec(noinline)
#define VECTORCALL       __vectorcall
#define CURRENT_FUNCTION __func__
#define RESTRICT         __restrict
#define INTERFACE        __interface
#else
#error "Unknown or not supported compiler toolchain!"
#endif

#define NODISCARD    [[nodiscard("")]]
#define MAYBE_UNUSED [[maybe_unused]]
#define NORETURN     [[noreturn]]
#define FALLTHROUGH  [[fallthrough]]
#define LIKELY       [[likely]]
#define UNLIKELY     [[unlikely]]

#define RK_GIBIBYTES(amount) amount * 1024 * 1024 * 1024
#define RK_MEBIBYTES(amount) amount * 1024 * 1024
#define RK_KIBIBYTES(amount) amount * 1024
#define RK_GIGABYTES(amount) amount * 1000 * 1000 * 1000
#define RK_MEGABYTES(amount) amount * 1000 * 1000
#define RK_KILOBYTES(amount) amount * 1000

RK_STATIC_ASSERT(sizeof(unsigned char) == 1);
RK_STATIC_ASSERT(sizeof(unsigned short) == 2);
RK_STATIC_ASSERT(sizeof(unsigned int) == 4);
RK_STATIC_ASSERT(sizeof(unsigned long long) == 8);
RK_STATIC_ASSERT(sizeof(signed char) == 1);
RK_STATIC_ASSERT(sizeof(signed short) == 2);
RK_STATIC_ASSERT(sizeof(signed int) == 4);
RK_STATIC_ASSERT(sizeof(signed long long) == 8);
RK_STATIC_ASSERT(sizeof(float) == 4);
RK_STATIC_ASSERT(sizeof(double) == 8);
RK_STATIC_ASSERT(sizeof(int) == 4);
RK_STATIC_ASSERT(sizeof(bool) == 1);

#define RK_EXPAND(x) x

#define RK_SET_BIT(byte, bitPos)   (byte |= (1 << bitPos))
#define RK_CLEAR_BIT(byte, bitPos) (byte &= ~(1 << bitPos))
#define RK_FLIP_BIT(byte, bitPos)  (byte ^= (1 << bitPos))
#define RK_CHECK_BIT(byte, bitPos) (byte & (1 << bitPos))

#define _RK_STRINGIFY_L2(arg) #arg
#define _RK_STRINGIFY_L1(arg) _RK_STRINGIFY_L2(arg)
#define RK_STRINGIFY(arg)     _RK_STRINGIFY_L1(arg)

#define _RK_CONCAT_L2(arg1, arg2) arg1##arg2
#define _RK_CONCAT_L1(arg1, arg2) _RK_CONCAT_L2(arg1, arg2)
#define RK_CONCAT(arg1, arg2)     _RK_CONCAT_L1(arg1, arg2)

#define _RK_FIRST_ARG(firstArg, ...) firstArg
#define RK_FIRST_ARG(...)            RK_EXPAND(_RK_FIRST_ARG(__VA_ARGS__))

#define _RK_RSEQ_N() 5, 4, 3, 2, 1, 0

#define _RK_VA_ARG_COUNT_IMPL(_1, _2, _3, _4, _5, N, ...) N

#define _RK_VA_ARG_COUNT(...) RK_EXPAND(_RK_VA_ARG_COUNT_IMPL(__VA_ARGS__)))

#define RK_VA_ARG_COUNT(...) RK_EXPAND(_RK_VA_ARG_COUNT(__VA_ARGS__, _RK_RSEQ_N()))

#define _RK_FOREACH(n, macro, ...) RK_EXPAND(_RK_CONCAT(_RK_FOREACH_, n)(macro, __VA_ARGS__))

#define RK_FOREACH(macro, ...) RK_EXPAND(_RK_FOREACH(RK_VA_ARG_COUNT(__VA_ARGS__), macro, __VA_ARGS__)))

namespace Rake {

class NonCopyable {
   protected:
    NonCopyable() = default;
    virtual ~NonCopyable() = default;

   private:
    NonCopyable(NonCopyable &&) = default;
    NonCopyable &operator=(NonCopyable &&) = default;
    NonCopyable(const NonCopyable &) = delete;
    NonCopyable &operator=(const NonCopyable &) = delete;
};

class NonMovable {
   protected:
    NonMovable() = default;
    virtual ~NonMovable() = default;

   private:
    NonMovable(const NonMovable &) = default;
    NonMovable &operator=(const NonMovable &) = default;
    NonMovable(NonMovable &&) = delete;
    NonMovable &operator=(NonMovable &&) = delete;
};

}  // namespace Rake
