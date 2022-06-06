/*****************************************************************/ /**
 * \file   MemoryPool.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include <memory>

#include "Types.h"

namespace Rake::Core
{

template <typename T> class MemoryPool
{
  public:
    const T *m_mem;

  public:
    RAKE_API MemoryPool(){};
    RAKE_API ~MemoryPool(){};

  private:
    /*void *operator new()
    {
    }
    void operator delete()
    {
    }*/

  public:
    RAKE_API void ResetPool(){};
    RAKE_API void *Allocate(const size_t &_size){};
    RAKE_API void Deallocate(){};
    RAKE_API void RkZeroMemory(){};
};

} // namespace Rake::Core
