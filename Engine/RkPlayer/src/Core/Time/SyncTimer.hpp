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

class SyncTimer final
{
  private:
    F32 m_timeScale;
    duration<F32> m_deltaTime;
    const time_point<high_resolution_clock> m_startTime = high_resolution_clock::now();
    time_point<high_resolution_clock> m_lastStartTime = m_startTime;
    static SyncTimer *m_instance;

  public:
    SyncTimer(F32 _timeScale);
    ~SyncTimer();

  public:
    __RAKE_API void Tick(const U32 _frameRate);
    __RAKE_API void Reset();

  public:
    __RAKE_API long long GetStartTime()
    {
        return m_startTime.time_since_epoch().count();
    }

    __RAKE_API F32 GetElapsedTime()
    {
        auto elapsedTime = high_resolution_clock::now() - m_startTime;
        return elapsedTime.count();
    }

    __RAKE_API F32 GetDeltaTime()
    {
        return m_deltaTime.count();
    }

    __RAKE_API F32 GetTimeScale()
    {
        return m_timeScale;
    }
};

} // namespace Rake::Core
