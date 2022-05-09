#include "RkPch.hpp"

#include "Core/Time/SyncTimer.hpp"

namespace Rake::Core
{

SyncTimer *SyncTimer::m_instance = nullptr;

SyncTimer::SyncTimer()
{

    if (!SyncTimer::m_instance)
    {
        this->Reset();

        this->m_elapsedTime = Duration<F32>(0.0f);
        this->m_deltaTime = Duration<F32>(0.0f);

        SyncTimer::m_instance = this;
    }
    else
    {
        throw std::runtime_error("Attemp to create a second sync timer");
    }
}

void SyncTimer::Reset()
{
    this->m_startTime = system_clock::now();
}

void SyncTimer::Tick()
{
    this->m_currentTime = system_clock::now();
}

} // namespace Rake::Core
