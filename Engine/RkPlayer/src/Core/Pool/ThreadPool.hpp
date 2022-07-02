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

namespace Rake::Core::Pool
{

class ThreadPool final
{
  private:
    std::atomic<B8> m_workersRunning = false;
    std::atomic<B8> m_workersPaused = false;

  private:
    const std::uint_fast32_t m_threadCount = std::thread::hardware_concurrency();
    std::vector<std::thread> m_threads;
    std::uint_fast32_t m_tasksCount = 0;
    std::uint_fast32_t m_runningTasks = 0;
    std::uint_fast32_t m_delayedTasks = 0;

  public:
    RAKE_API ThreadPool();
    RAKE_API ~ThreadPool();

  private:
    bool Init();
    void Release();
    void WaitForTasks();
    void ResetPool();

  public:
    RAKE_API void AddTask(auto *_func, ...);
    RAKE_API void RemoveTask(auto *_func);
    RAKE_API void ParallelizeLoop(const auto _firstFunc, const auto _secondFunc, const auto _loop, std::uint_fast32_t _blocks = 0);

  public:
    RAKE_API inline std::uint_fast32_t GetThreadsCount() const noexcept
    {
        return this->m_threadCount;
    }

    RAKE_API inline std::uint_fast32_t GetTasksCount() const
    {
        return this->m_tasksCount;
    }

    RAKE_API inline std::uint_fast32_t GetRunningTasks() const
    {
        return this->m_runningTasks;
    }

    RAKE_API inline std::uint_fast32_t GetDelayedTasks() const
    {
        return this->m_delayedTasks;
    }
};

} // namespace Rake::Core::Pool
