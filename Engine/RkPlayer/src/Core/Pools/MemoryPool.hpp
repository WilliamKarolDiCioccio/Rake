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
template <typename T> class MemoryPool
{
  public:
    virtual const char *m_mem[MEBIBYTES(4)];

  public:
    MemoryPool()
    {
    }
    MemoryPool(const MemoryPool &_oldObj)
    {
    }
    ~MemoryPool()
    {
    }

  private:
    void *operator new(std::size_t _n)
    {
    }
    void operator delete(void *_ptr, size_t &size)
    {
    }

  public:
    void Allocate()
    {
        void *mem;
    }
};

} // namespace Rake::Core
