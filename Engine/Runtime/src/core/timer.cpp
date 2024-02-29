#include "pch.hpp"

#include "core/timer.hpp"

using namespace std::chrono_literals;

namespace Rake::core {

Timer::Timer() : m_startTime(std::chrono::steady_clock::now()), m_lastStartTime(m_startTime) { Reset(); }

Timer::~Timer() { Reset(); }

void Timer::Tick() {
    m_deltaTime = std::chrono::steady_clock::now() - m_lastStartTime;

    m_ticks++;

    Reset();
}

void Timer::Reset() {
    static auto last = std::chrono::steady_clock::now();

    if (std::chrono::steady_clock::now() - last >= 1s) {
        m_FPSCount = static_cast<double>(m_ticks);

        m_ticks = 0;

        last = std::chrono::steady_clock::now();
    }

    m_lastStartTime = std::chrono::steady_clock::now();
}

std::string Timer::GetTimestamp(const std::string &_format) noexcept {
    char timestring[256];

    time_t rawtime;
    time(&rawtime);

    tm *timeinfo;
    timeinfo = localtime(&rawtime);

    std::strftime(timestring, sizeof(timestring), _format.c_str(), timeinfo);

    return timestring;
}

}  // namespace Rake::core
