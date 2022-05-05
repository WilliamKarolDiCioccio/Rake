/*****************************************************************/ /**
 * \file   Timer.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include <chrono>
#include <string>

#include "Common.h"

namespace Rake::Core
{

using namespace std::chrono;
using namespace std::chrono_literals;

class SyncTimer final
{
  private:
    using TimePoint = system_clock::time_point;
    template <typename T> using Duration = duration<T>;

  private:
    TimePoint m_startTime;
    TimePoint m_currentTime;
    Duration<F32> m_elapsedTime;
    Duration<F32> m_deltaTime;
    F32 m_timeScale;

  private:
    void Reset();

  private:
    static SyncTimer *m_instance;

  public:
    SyncTimer();
    ~SyncTimer(){};

  public:
    void Tick();

  public:
    inline F32 *GetTimeScale()
    {
        return &m_timeScale;
    }

    inline long long GetStartTime()
    {
        auto tmp = m_startTime.time_since_epoch();
        auto time = tmp.count();
        return time;
    }

    inline long long RkGetCurrentTime()
    {
        auto tmp = m_currentTime.time_since_epoch();
        auto time = tmp.count();
        return time;
    }
};

} // namespace Rake::Core
