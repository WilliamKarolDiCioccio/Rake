#include "src/RkPch.hpp"

#include "Core/Timers/SyncTimer.hpp"

namespace Rake::Core
{

SyncTimer *SyncTimer::m_instance = nullptr;

SyncTimer::SyncTimer(F32 _timeScale) : m_timeScale(_timeScale)
{
    if (SyncTimer::m_instance == nullptr)
    {
        SyncTimer::m_instance == this;
    }
    else
        throw std::runtime_error("Attemp to create a sencond SyncTimer instance");
}

SyncTimer::~SyncTimer()
{
    m_deltaTime = duration<F32>(0.0f);
    delete (m_instance);
    RK_ASSERT(!m_instance);
}

void SyncTimer::Tick(const U32 _frameRate)
{
    m_deltaTime = high_resolution_clock::now() - m_lastStartTime;

    if (m_deltaTime.count() >= 1.0f)
        this->Reset();
}

void SyncTimer::Reset()
{
    m_lastStartTime = high_resolution_clock::now();
}

} // namespace Rake::Core
