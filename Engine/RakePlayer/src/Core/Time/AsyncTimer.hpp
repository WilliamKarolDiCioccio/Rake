/*****************************************************************/ /**
 * \file   AsyncTimer.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   April 2022
 *********************************************************************/

#pragma once

#include <thread>

#include "Common.h"

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
    using TimePoint = system_clock::time_point;
    template <typename T> using Duration = duration<T>;

  public:
    __RAKE_PLAYER_API AsyncTimer();
    __RAKE_PLAYER_API ~AsyncTimer();

    __RAKE_PLAYER_API void Start();
    __RAKE_PLAYER_API void Stop();

    template <typename Function> void SetCall(Function _function)
    {
    }

  private:
    TimerState m_state;

  private:
    std::thread m_thread;
};

} // namespace Rake::Core
