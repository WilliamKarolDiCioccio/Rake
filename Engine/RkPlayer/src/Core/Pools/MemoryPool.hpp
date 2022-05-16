/*****************************************************************/ /**
 * \file   MemoryPool.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include <memory>

#include "Common.def.h"

namespace Rake::Core
{
template <typename T> class MemoryPool
{
  public:
    const char *m_mem;

  public:
    MemoryPool();
    ~MemoryPool();

  private:
    void *operator new(std::size_t _n);
    void operator delete(void *_ptr, size_t &size);

  public:
    void ResetPool();
    void Malloc();
    void Free();
};

} // namespace Rake::Core
