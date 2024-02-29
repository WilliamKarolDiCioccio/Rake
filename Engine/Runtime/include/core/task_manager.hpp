#pragma once

#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

#include "base.hpp"

namespace Rake::core {

/**
 * @class TaskManager
 * @brief Manages and executes tasks with priorities in a multi-threaded environment.
 */
class TaskManager final {
    using Func = std::function<void()>;

   private:
    /**
     * @struct Task
     * @brief Represents a task with an associated callback function and priority.
     */
    struct Task {
        float priority = 0.f;
        Func setup, job, callback;
    };

    struct Compare {
        NODISCARD bool operator()(const Task &a, const Task &b) const noexcept { return a.priority < b.priority; }
    };

    std::function<void()> m_envSetup;
    std::vector<std::thread> m_threads;
    std::priority_queue<Task, std::vector<Task>, Compare> m_tasks;
    std::mutex m_mutex;
    std::condition_variable m_condition;

    bool m_isRunning;
    bool m_isPaused;

   public:
    /**
     * @brief Constructs a TaskManager instance.
     * @param _envSetup A function to appropriately setup each thread execution enviroment.
     */
    RK_API TaskManager(Func &&_envSetup);

    /**
     * @brief Destroys the TaskManager instance.
     */
    RK_API ~TaskManager();

   public:
    /**
     * @brief Adds a task to the TaskManager with a specified priority and callback.
     * @param _job The job function.
     * @param _callback The callback function.
     * @param _priority The priority of the task.
     */
    RK_API void AddTask(Func &&_job, Func &&_callback, float _priority);

    /**
     * @brief Starts the TaskManager with a specified number of threads.
     * @param _numThreads The number of worker threads to start.
     */
    RK_API void Start(int32_t _numThreads = std::thread::hardware_concurrency());

    /**
     * @brief Pauses the execution of tasks by the TaskManager.
     */
    RK_API void Pause();

    /**
     * @brief Resumes the execution of tasks by the TaskManager.
     */
    RK_API void Resume();
};

}  // namespace Rake::core
