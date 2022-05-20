/*****************************************************************/ /**
 * \file   RkPch.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Common.def.h"

#ifdef PLATFORM_WINDOWS
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <windowsx.h>
#endif

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

#include "Core/Tools/Log.inl.hpp"
#include "Core/Tools/Assert.inl.hpp"

#include "Core/Error/RkException.hpp"
#include "Core/Utils/RkString.inl.h"
