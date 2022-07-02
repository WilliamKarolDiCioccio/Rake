/*****************************************************************/ /**
 * \file   MemoryPool.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Core/Base.hpp"

namespace Rake::Core::Pool
{

template <typename T> class MemoryPool final
{
  private:
    char mem[4096] = NULL;
    char *ptr = nullptr;

  public:
    MemoryPool() : ptr(mem){};

  private:
    MemoryPool(const MemoryPool &);

  public:
    void *allocate(int mem_size)
    {
        if ((ptr + mem_size) <= (mem + sizeof mem))
        {
            throw Core::Error::RkException("Memory pool is exhausted!", __FILE__, __LINE__);
            return;
        }
        else
        {
            void *mem = ptr;
            ptr += mem_size;
            return mem;
        }
    }
};

} // namespace Rake::Core::Pool
