#pragma once

#include "core/Internal/Config.h"
#include "core/Internal/Assert.h"
#include "core/Internal/Warnings.h"

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

#ifdef PLAYER_EXPORT
#define RK_API DLL_EXPORT
#else
#define RK_API DLL_IMPORT
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

#define RK_SET_BIT(byte, bitPos)   (byte |= (1 << bitPos))
#define RK_CLEAR_BIT(byte, bitPos) (byte &= ~(1 << bitPos))
#define RK_FLIP_BIT(byte, bitPos)  (byte ^= (1 << bitPos))
#define RK_CHECK_BIT(byte, bitPos) (byte & (1 << bitPos))

namespace Rake {

class RK_API NonCopyable {
   protected:
    NonCopyable() = default;
    virtual ~NonCopyable() = default;

   private:
    NonCopyable(NonCopyable &&) = default;
    NonCopyable &operator=(NonCopyable &&) = default;
    NonCopyable(const NonCopyable &) = delete;
    NonCopyable &operator=(const NonCopyable &) = delete;
};

class RK_API NonMovable {
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
