/*****************************************************************/ /**
 * \file   RkMain.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   April 2022
 *********************************************************************/

#pragma once

#include "RkBase/internal/Config.h"

namespace RkBase
{

typedef struct CommandLineArguments
{

} CmdArgs;

inline CmdArgs RetriveCmdArgs()
{
    CmdArgs temp;
    return temp;
}

#define RETRIVE_ARGS RetriveArgs();

} // namespace RkBase

#if defined(PLATFORM_WINDOWS)
#define RK_GUI_MAIN(...) int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
#define RK_GUI_MAIN(...) main()
#endif

#define RK_DEBUG_MAIN
