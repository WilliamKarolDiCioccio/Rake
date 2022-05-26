#include "src/RkPch.hpp"

#include "Core/Pools/ThreadPool.hpp"

namespace Rake::Core
{

ThreadPool::ThreadPool()
{
}

ThreadPool::~ThreadPool()
{
}

bool ThreadPool::Init()
{
    return true;
}

void ThreadPool::Release()
{
}

void ThreadPool::AddTask(auto _task, ...)
{
    for (U32 i = 0; i <= m_threads.size(); i++)
    {
        if (m_threads[i].joinable())
        {
            m_threads[i].join();
            break;
        }
    }

    m_tasksCount++;
}

void ThreadPool::RemoveTask(auto _task)
{
    m_tasksCount--;
}

void ThreadPool::ParallelizeLoop(const auto _firstFunc, const auto _secondFunc, const auto _loop, UI32 _blocks)
{
}

void ThreadPool::WaitForTasks()
{
    while (true)
    {
        if (m_tasksCount == 0)
            break;
    }
}

void ThreadPool::ResetPool()
{
}

} // namespace Rake::Core
