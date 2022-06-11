/*****************************************************************/ /**
 * \file   RkMain.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   April 2022
 *********************************************************************/

#pragma once

#include "internal/Config.h"

#if defined(PLATFORM_WINDOWS)
#define RK_GUI_MAIN()        int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
#define RK_CONSOLE_MAIN(...) int APIENTRY tmain(...)
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
#define RK_GUI_MAIN(...)     main()
#define RK_CONSOLE_MAIN(...) main()
#endif
