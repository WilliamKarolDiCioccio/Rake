#include "RkPch.hpp"

#include "Core/Time/SyncTimer.hpp"

namespace Rake::Core
{

SyncTimer *SyncTimer::m_instance = nullptr;

SyncTimer::SyncTimer(F32 _timescale)
{
    if (SyncTimer::m_instance == nullptr)
    {
        SyncTimer::m_instance == this;
    }
    else
        throw std::runtime_error("Attemp to create a sencond SyncTimer instance");
}

void SyncTimer::Tick()
{
    if (m_isTicking)
    {
        m_data.currentTime = std::chrono::system_clock::now();

        if (m_data.deltaTime.count() >= 1.0f)
            this->Reset();
    }
}

void SyncTimer::Start()
{
    this->m_isTicking = true;
}

void SyncTimer::Pause()
{
    this->m_isTicking = false;
}

void SyncTimer::Resume()
{
    this->m_isTicking = true;
}

void SyncTimer::Stop()
{
}

void SyncTimer::Reset()
{
}

} // namespace Rake::Core
