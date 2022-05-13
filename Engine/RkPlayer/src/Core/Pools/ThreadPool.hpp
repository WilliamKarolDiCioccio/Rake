/*****************************************************************/ /**
 * \file   ThreadPool.hpp
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   May 2022
 *********************************************************************/

#pragma once

#include <thread>

#include "Common.h"

namespace Rake::Core
{

class ThreadPool final
{
  private:
    using UI32 = Rake::Scientific::UI32;
    using UI64 = Rake::Scientific::UI64;

  private:
    const UI32 m_threadCount = std::thread::hardware_concurrency();
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
    void AddTask();
    void RemoveTask();

  public:
    inline UI32 GetThreadsCount() const noexcept
    {
        return m_threadCount;
    }

    inline UI32 GetTasksCount() const
    {
        return m_tasksCount;
    }

    inline UI32 GetRunningTasks() const
    {
        return m_runningTasks;
    }

    inline UI32 GetDelayedTasks() const
    {
        return m_delayedTasks;
    }
};

} // namespace Rake::Core
