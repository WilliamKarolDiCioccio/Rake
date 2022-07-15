/*****************************************************************/ /**
 * \file   Timer.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#ifdef GetCurrentTime
#undef GetCurrentTime
#endif

#include <chrono>

#include "Core/Base.hpp"

namespace Rake::Core
{

using namespace std::chrono;

class SyncTimer final
{
  private:
    static SyncTimer *m_timerInstance;

  private:
    F32 m_timeScale;
    duration<F32> m_deltaTime;
    const time_point<high_resolution_clock> m_startTime;
    time_point<high_resolution_clock> m_lastStartTime;

  public:
    SyncTimer();
    ~SyncTimer();

  public:
    void Tick();
    void Reset();
    void SetTimescale(F32 _newTimeScale);

  public:
    inline long long GetStartTime() const
    {
        return this->m_startTime.time_since_epoch().count();
    }

    inline F32 GetElapsedTime() const
    {
        auto elapsedTime = high_resolution_clock::now() - m_startTime;
        return elapsedTime.count();
    }

    inline F32 GetDeltaTime() const
    {
        return this->m_deltaTime.count();
    }

    inline F32 GetTimeScale() const
    {
        return this->m_timeScale;
    }
};

} // namespace Rake::Core
