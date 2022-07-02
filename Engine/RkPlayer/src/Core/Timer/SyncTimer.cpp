#include "src/RkPch.h"

#include "SyncTimer.hpp"

namespace Rake::Core::Timer
{

SyncTimer *SyncTimer::m_instance = nullptr;

SyncTimer::SyncTimer()
{
    if (SyncTimer::m_instance == nullptr)
    {
        SyncTimer::m_instance == this;
    }
    else
    {
        throw std::runtime_error("Attemp to create a sencond SyncTimer instance");
    }
}

SyncTimer::~SyncTimer()
{
    m_deltaTime = duration<F32>(0.0f);
    delete (m_instance);
}

void SyncTimer::Tick()
{
    m_deltaTime = high_resolution_clock::now() - m_lastStartTime;

    if (m_deltaTime.count() >= 1.0f)
        this->Reset();
}

void SyncTimer::Reset()
{
    m_lastStartTime = high_resolution_clock::now();
}

void SyncTimer::SetTimescale(const F32 _newTimeScale)
{
    m_timeScale = _newTimeScale;
}

} // namespace Rake::Core::Timer
