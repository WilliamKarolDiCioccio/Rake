#pragma once

#include <chrono>
#include <string>

#include "base.hpp"

namespace Rake::core {

class Timer final {
   private:
    std::chrono::steady_clock::time_point m_startTime{};
    std::chrono::steady_clock::time_point m_lastStartTime{};
    std::chrono::duration<double, std::milli> m_deltaTime = std::chrono::duration<double, std::milli>::zero();

    uint64_t m_ticks = 0;
    double m_FPSCount = 0.f;

   public:
    RK_API Timer();
    RK_API ~Timer();

   public:
    RK_API void Tick();
    RK_API void Reset();
    RK_API static std::string GetTimestamp(const std::string &_format) noexcept;

   public:
    NODISCARD std::chrono::steady_clock::time_point GetStartTime() const noexcept { return m_startTime; }

    NODISCARD std::chrono::milliseconds GetElapsedTime() const noexcept {
        auto elapsedTime = std::chrono::steady_clock::now() - m_startTime;

        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime);
    }

    NODISCARD std::chrono::milliseconds GetDeltaTime() const noexcept {
        return std::chrono::duration_cast<std::chrono::milliseconds>(m_deltaTime);
    }

    NODISCARD inline double GetFPSCount() const noexcept { return m_FPSCount; }
};

}  // namespace Rake::core
