#include "RkPch.h"

#include "AsyncTimer.hpp"

namespace Rake::Core
{

void AsyncTimer::Start()
{
    m_isRunning = true;
}

void AsyncTimer::Pause()
{
    if (m_isPaused != true)
        m_isPaused = true;
    else
        m_isPaused = false;
}

void AsyncTimer::Stop()
{
    m_isRunning = false;
}

void AsyncTimer::SetTimeout(void *_function, milliseconds _delay)
{
    std::this_thread::sleep_for(_delay);
}

void AsyncTimer::SetInterval(void *_function, milliseconds _interval, U32 _times)
{
    std::this_thread::sleep_for(_interval);
}

} // namespace Rake::Core
