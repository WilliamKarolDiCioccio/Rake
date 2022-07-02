/*****************************************************************/ /**
 * \file   RkPch.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include <iostream>
#include <fstream>

#include <time.h>
#include <memory>

#include <math.h>
#include <numeric>

#include <algorithm>
#include <functional>

#include <string>
#include <array>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <iterator>

#include <utility>
#include <format>
#include <sstream>

#include <thread>
#include <mutex>
#include <future>
#include <atomic>

/**********************************************************************/

#include "Core/Config.h"
#include "Core/Base.hpp"

#include "Tools/Assert.h"
#include "Tools/Log.hpp"

#include "Core/Error/RkException.hpp"
#include "Core/Pool/MemoryPool.hpp"
#include "Core/Pool/ThreadPool.hpp"

/**********************************************************************/

#ifdef PLATFORM_WINDOWS
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <wrl.h>
#endif
