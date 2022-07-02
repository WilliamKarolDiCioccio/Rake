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

#define ASSERTIONS_ENABLED RK_TRUE
#define LOGGER_ENABLED     RK_TRUE

#if defined(LOGGER_ENABLED) == RK_TRUE
#define DEFAULT_LOGGER        "DefaultLogger"
#define DEFAULT_LOG_PATTERN   "[%l][%H:%M:%S.%e] %v"
#define DEFAULT_LOG_FILE_NAME "logs/session_log.log"
#define LOG_FILES_PER_SESSION 5
#endif
