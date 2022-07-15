/*****************************************************************/ /**
 * \file   ThreadPool.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   May 2022
 *********************************************************************/

#pragma once

#include <cstdint>
#include <thread>
#include <atomic>
#include <future>
#include <mutex>
#include <queue>
#include <vector>

#include "Core/Base.hpp"

namespace Rake::Core
{

class ThreadPool final
{
  private:
    std::uint_fast32_t m_threadCount = std::thread::hardware_concurrency();
    std::vector<std::thread> m_threads;
    std::uint_fast32_t m_tasksCount;
    std::uint_fast32_t m_runningTasks;
    std::uint_fast32_t m_delayedTasks;

  public:
    ThreadPool();
    ~ThreadPool();

  private:
    B8 Init()
    {
        return true;
    }
    void Release()
    {
    }
    void WaitForTasks()
    {
    }
    void ResetPool()
    {
    }

  public:
    auto AddTask(void *_func, ...) -> decltype(&_func)
    {
    }
    void RemoveTask(void *_func)
    {
    }
};

} // namespace Rake::Core
