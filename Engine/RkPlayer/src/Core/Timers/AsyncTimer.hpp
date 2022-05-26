/*****************************************************************/ /**
 * \file   AsyncTimer.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   April 2022
 *********************************************************************/

#pragma once

#include <atomic>
#include <thread>
#include <chrono>
#include <vector>

#include "Common.def.h"

#include "Core/Pools/ThreadPool.hpp"

namespace Rake::Core
{

using namespace std::chrono;
using namespace std::chrono_literals;

class AsyncTimer final : public std::thread
{
  private:
    std::atomic<B8> m_isRunning = true;
    std::atomic<B8> m_isPaused = false;
    std::vector<std::thread> m_threads;

  public:
    RAKE_API explicit AsyncTimer(const B8 _multithreaded){};

  public:
    RAKE_API void Start();
    RAKE_API void Pause();
    RAKE_API void Stop();
    RAKE_API void SetTimeout(auto _function, milliseconds _delay);
    RAKE_API void SetInterval(auto _function, milliseconds _interval, U32 _times);

  public:
    RAKE_API inline thread::id GetID()
    {
        return this->get_id();
    }
};

} // namespace Rake::Core
