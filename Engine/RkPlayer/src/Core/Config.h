/*****************************************************************/ /**
 * \file   EngineConfig.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#define RK_TRUE  (1 == 1)
#define RK_FALSE !RK_TRUE

#define ASSERTIONS_ENABLED         RK_TRUE
#define LOGGER_ENABLED             RK_TRUE
#define EXCEPTION_HANDLING_ENABLED RK_TRUE

#define DEFAULT_WINDOW_WIDTH  1280
#define DEFAULT_WINDOW_HEIGHT 720
#define DEFAULT_WINDOW_TITLE  L"Rake"

#define MINIMUM_WINDOW_WIDTH  1280
#define MINIMIM_WINDOW_HEIGHT 720

#define STANDARD_WINDOW_COUNT 1
#define MAXIMUM_WINDOW_COUNT  2

#define MONITOR_SUITABILITY_PARAMETERS
