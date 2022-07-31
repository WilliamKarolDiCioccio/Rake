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
#include <set>
#include <map>
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

#include "Core/Config.h"
#include "Core/Base.hpp"

#include "Tools/Assert.h"
#include "Tools/Log.hpp"
#include "Core/Exception.hpp"

#include "Core/ThreadPool.hpp"
#include "Core/String.hpp"
#include "Core/Random.hpp"

#include "Core/Internal/Detection.h"

#if defined(PLATFORM_WINDOWS)
#include "Platform/Windows/Win32Utils.hpp"
#endif
