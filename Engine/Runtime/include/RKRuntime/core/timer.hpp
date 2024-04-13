#pragma once

#include <chrono>
#include <string>

#include "RKRuntime/base.hpp"

namespace Rake::core {

/**
 * @brief The Timer class is used to measure time.
 * 
 * @details
 * The timer class keeps track of the ticks per second and to calculate the delta time.
 */
class RK_API Timer final {
   private:
    std::chrono::steady_clock::time_point m_startTime{};
    std::chrono::steady_clock::time_point m_lastStartTime{};
    std::chrono::duration<double, std::milli> m_deltaTime = std::chrono::duration<double, std::milli>::zero();

    uint64_t m_ticks = 0;
    double m_FPSCount = 0.f;

   public:
    Timer();
    ~Timer();

   public:
    /**
     * @brief Increment the tick count.
     * 
     * @note Never call this method on the Application class built-in timer.
	 */
    void Tick();

    /**
     * @brief Reset the tick count and update timer data.
     * 
     * @note Never call this method on the Application class built-in timer.
	 */
    void Reset();

   public:
    NODISCARD std::chrono::steady_clock::time_point GetStartTime() const noexcept { return m_startTime; }

    /**
	 * @brief Get the elapsed time.
	 *
	 * @return The elapsed time in milliseconds.
     */
    NODISCARD std::chrono::milliseconds GetElapsedTime() const noexcept {
        auto elapsedTime = std::chrono::steady_clock::now() - m_startTime;

        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime);
    }

    /**
     * @brief Get the delta time.
     * 
     * @return The delta time in milliseconds.
	 */
    NODISCARD std::chrono::milliseconds GetDeltaTime() const noexcept {
        return std::chrono::duration_cast<std::chrono::milliseconds>(m_deltaTime);
    }

    /**
     * @brief Get the FPS count
     *
     * @return The current FPS count
	 */
    NODISCARD inline double GetFPSCount() const noexcept { return m_FPSCount; }

    /**
	 * @brief Get the timestamp in the given format.
	 *
	 * @return The timestamp in the given format.
     */
    static std::string GetTimestamp(const std::string &_format) noexcept;
};

}  // namespace Rake::core
