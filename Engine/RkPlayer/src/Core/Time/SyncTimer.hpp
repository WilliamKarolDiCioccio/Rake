/*****************************************************************/ /**
 * \file   Timer.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#undef GetCurrentTime

#include <chrono>

#include "Common.def.h"

namespace Rake::Core
{

using namespace std::chrono;
using namespace std::chrono_literals;

typedef struct TimerData
{
    const time_point<high_resolution_clock> startTime = high_resolution_clock::now();
    time_point<system_clock> currentTime;
    duration<F32> elapsedTime;
    duration<F32> deltaTime;
    F32 timeScale;
} TimerData, timer_data;

class SyncTimer final
{
  private:
    TimerData m_data;
    static SyncTimer *m_instance;
    B8 m_isTicking;

  public:
    SyncTimer(F32 _timescale);
    ~SyncTimer(){};

  public:
    __RAKE_API void Tick();
    __RAKE_API void Start();
    __RAKE_API void Pause();
    __RAKE_API void Resume();
    __RAKE_API void Stop();
    __RAKE_API void Reset();

  public:
    __RAKE_API long long GetStartTime()
    {
        return m_data.startTime.time_since_epoch().count();
    }

    __RAKE_API long long GetCurrentTime()
    {
        return m_data.currentTime.time_since_epoch().count();
    }

    __RAKE_API F32 GetElapsedTime()
    {
        return m_data.elapsedTime.count();
    }

    __RAKE_API F32 GetDeltaTime()
    {
        return m_data.deltaTime.count();
    }

    __RAKE_API F32 GetTimeScale()
    {
        return m_data.timeScale;
    }
};

} // namespace Rake::Core
