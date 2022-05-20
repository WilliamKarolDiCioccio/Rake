/*****************************************************************/ /**
 * \file   AsyncTimer.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   April 2022
 *********************************************************************/

#pragma once

#include <thread>

#include "Common.def.h"

#include "Core/Pools/ThreadPool.hpp"

namespace Rake::Core
{

using namespace std::chrono;
using namespace std::chrono_literals;

typedef struct TimerState
{
    B8 isRunning = true;
    B8 isPaused = false;
    B8 isBackground = false;
} TimerState, timer_state;

class AsyncTimer final
{
  private:
    TimerState m_state;
    std::thread m_thread;
    using TimePoint = system_clock::time_point;
    template <typename T> using Duration = duration<T>;

  public:
    RAKE_API AsyncTimer();
    RAKE_API ~AsyncTimer();

    RAKE_API void Start();
    RAKE_API void Stop();

    RAKE_API void SetTimeout(auto _function, F64 _delay);
    RAKE_API void SetInterval(auto _function, F64 _interval);
};

} // namespace Rake::Core
