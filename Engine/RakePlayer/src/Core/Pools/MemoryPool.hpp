/*****************************************************************/ /**
 * \file   MemoryPool.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include <memory>

#include "Common.h"

namespace Rake::Core
{

typedef struct CharPool
{
    static void *operator new(std::size_t _n);
    static void operator delete(void *_ptr, size_t size);
} CharPool;

void *CharPool::operator new(std::size_t _n)
{
}

void CharPool::operator delete(void *_ptr, size_t size)
{
}

typedef struct IntPool
{
    static inline void *operator new(std::size_t _count);
    static inline void operator delete(void *pointer, size_t size);
} IntPool, B32Pool;

void *CharPool::operator new(std::size_t _n)
{
}

void CharPool::operator delete(void *_ptr, size_t size)
{
}

typedef struct FloatPool
{
    static inline void *operator new(std::size_t _count);
    static inline void operator delete(void *pointer, size_t size);
} FloatPool, F32Pool;

void *FloatPool::operator new(std::size_t _n)
{
}

void FloatPool::operator delete(void *_ptr, size_t size)
{
}

typedef struct DoublePool
{
    static inline void *operator new(std::size_t _count);
    static inline void operator delete(void *pointer, size_t size);
} DoublePool, F64Pool;

void *DoublePool::operator new(std::size_t _n)
{
}

void DoublePool::operator delete(void *_ptr, size_t size)
{
}

} // namespace Rake::Core
