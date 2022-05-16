/*****************************************************************/ /**
 * \file   ThreadPool.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   May 2022
 *********************************************************************/

#pragma once

#include <thread>
#include <atomic>
#include <future>
#include <mutex>

#include "Common.def.h"

namespace Rake::Core
{

class ThreadPool final
{
  private:
    using UI32 = Rake::Scientific::UI32;
    using UI64 = Rake::Scientific::UI64;

  private:
    const UI32 m_threadCount = std::thread::hardware_concurrency();
    std::atomic<B8> m_workersRunning = false;
    UI32 m_tasksCount = 0;
    UI32 m_runningTasks = 0;
    UI32 m_delayedTasks = 0;

  public:
    ThreadPool();
    ~ThreadPool();

  private:
    void CreateThreads();
    void DestroyThreads();

  public:
    void ResetPool();
    void AddTask();
    void RemoveTask();

  public:
    inline UI32 GetThreadsCount() const noexcept
    {
        return this->m_threadCount;
    }

    inline UI32 GetTasksCount() const
    {
        return this->m_tasksCount;
    }

    inline UI32 GetRunningTasks() const
    {
        return this->m_runningTasks;
    }

    inline UI32 GetDelayedTasks() const
    {
        return this->m_delayedTasks;
    }
};

} // namespace Rake::Core
