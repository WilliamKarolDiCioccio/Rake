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

namespace Rake::Core::Timer
{

using namespace std::chrono;

class SyncTimer final
{
  private:
    static SyncTimer *m_instance;

  private:
    F32 m_timeScale = 1.0f;
    duration<F32> m_deltaTime = 0ms;
    const time_point<high_resolution_clock> m_startTime = high_resolution_clock::now();
    time_point<high_resolution_clock> m_lastStartTime = m_startTime;

  public:
    SyncTimer();
    ~SyncTimer();

  public:
    RAKE_API void Tick();
    RAKE_API void Reset();

  public:
    RAKE_API void SetTimescale(F32 _newTimeScale);

  public:
    RAKE_API long long GetStartTime()
    {
        return m_startTime.time_since_epoch().count();
    }

    RAKE_API F32 GetElapsedTime()
    {
        auto elapsedTime = high_resolution_clock::now() - m_startTime;
        return elapsedTime.count();
    }

    RAKE_API F32 GetDeltaTime()
    {
        return m_deltaTime.count();
    }

    RAKE_API F32 GetTimeScale()
    {
        return m_timeScale;
    }
};

} // namespace Rake::Core::Timer
