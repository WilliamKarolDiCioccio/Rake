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

#include "Common.def.h"

namespace Rake::Core
{

class ThreadPool final
{
  private:
    std::atomic<B8> m_workersRunning = false;
    std::atomic<B8> m_workersPaused = false;

  private:
    const UI32 m_threadCount = std::thread::hardware_concurrency();
    std::vector<std::thread> m_threads;
    UI32 m_tasksCount = 0;
    UI32 m_runningTasks = 0;
    UI32 m_delayedTasks = 0;

  public:
    ThreadPool();
    ~ThreadPool();

  private:
    bool Init();
    void Release();
    void WaitForTasks();
    void ResetPool();

  public:
    RAKE_API void AddTask(auto _func, ...);
    RAKE_API void RemoveTask(auto _func);
    RAKE_API void ParallelizeLoop(const auto _firstFunc, const auto _secondFunc, const auto _loop, UI32 _blocks = 0);

  public:
    RAKE_API inline UI32 GetThreadsCount() const noexcept
    {
        return this->m_threadCount;
    }

    RAKE_API inline UI32 GetTasksCount() const
    {
        return this->m_tasksCount;
    }

    RAKE_API inline UI32 GetRunningTasks() const
    {
        return this->m_runningTasks;
    }

    RAKE_API inline UI32 GetDelayedTasks() const
    {
        return this->m_delayedTasks;
    }
};

} // namespace Rake::Core
