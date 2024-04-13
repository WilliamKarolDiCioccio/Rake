#include "pch.hpp"

#include "core/task_manager.hpp"

namespace Rake::core {

TaskManager::TaskManager(Func &&_envSetup) : m_envSetup(_envSetup), m_isRunning(true), m_isPaused(false){};

TaskManager::~TaskManager() {
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_isRunning = false;
        lock.unlock();
        m_condition.notify_all();
    }

    for (std::thread &thread : m_threads) thread.join();
}

void TaskManager::AddTask(Func &&_job, Func &&_callback, float _priority) {
    Task task = {
        .priority = _priority,
        .job = _job,
        .callback = _callback,
    };

    std::unique_lock<std::mutex> lock(m_mutex);
    m_tasks.emplace(task);
    lock.unlock();
    m_condition.notify_one();
}

void TaskManager::Start(uint32_t _numThreads) {
    for (int i = 0; i < _numThreads; ++i) {
        m_threads.emplace_back([this] {
            m_envSetup();

            while (true) {
                std::unique_lock<std::mutex> lock(m_mutex);
                m_condition.wait(lock, [this] { return !m_isRunning || !m_tasks.empty(); });

                if (!m_isRunning && m_tasks.empty()) return;

                if (m_isPaused) continue;

                auto task = m_tasks.top();
                m_tasks.pop();
                lock.unlock();
                task.job();
                task.callback();
            }
        });
    }
}

void TaskManager::Pause() {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_isPaused = true;
}

void TaskManager::Resume() {
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_isPaused = false;
    }

    m_condition.notify_all();
}

}  // namespace Rake::core
