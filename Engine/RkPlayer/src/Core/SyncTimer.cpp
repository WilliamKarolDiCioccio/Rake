#include "RkPch.h"

#include "SyncTimer.hpp"

namespace Rake::Core
{

SyncTimer *SyncTimer::m_timerInstance = nullptr;

SyncTimer::SyncTimer()
{
    if (!m_timerInstance)
    {
        m_lastStartTime = m_startTime;

        this->Reset();

        m_timeScale = 1.0f;
        m_deltaTime = std::chrono::duration<F32>(0.0f);
    }
    else
    {
        throw RkException("", NULL, __FILE__, __LINE__, true);
    }
}

SyncTimer::~SyncTimer()
{
    m_deltaTime = duration<F32>(0.0f);
}

void SyncTimer::Tick()
{
    m_deltaTime = high_resolution_clock::now() - m_lastStartTime;

    if (m_deltaTime.count() >= 1.0f / 60.0f)
        this->Reset();
}

void SyncTimer::Reset()
{
    m_lastStartTime = high_resolution_clock::now();
}

void SyncTimer::SetTimescale(F32 _newTimeScale)
{
    m_timeScale = _newTimeScale;
}

} // namespace Rake::Core
