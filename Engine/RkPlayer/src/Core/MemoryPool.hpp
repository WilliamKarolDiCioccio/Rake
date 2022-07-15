/*****************************************************************/ /**
 * \file   MemoryPool.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Core/Base.hpp"

namespace Rake::Core
{

template <typename T> class MemoryPool final
{
  private:
    std::array<char, KIBIBYTES(4)> mem = {};
    char *ptr = nullptr;

  public:
    MemoryPool() : ptr(mem){};
    MemoryPool(const MemoryPool &);

  public:
    void *allocate(int mem_size)
    {
        if ((ptr + mem_size) <= (mem + sizeof mem))
        {
            throw RkException("Memory pool is exhausted!", NULL, __FILE__, __LINE__);
            return nullptr;
        }
        else
        {
            void *mem = ptr;
            ptr += mem_size;
            return mem;
        }
    }
};

} // namespace Rake::Core
