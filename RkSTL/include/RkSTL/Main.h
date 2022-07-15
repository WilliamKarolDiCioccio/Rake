/*****************************************************************/ /**
 * \file   Main.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   April 2022
 *********************************************************************/

#pragma once

#include "internal/Detection.h"

#if defined(PLATFORM_WINDOWS) == 1
#define RK_GUI_MAIN() int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS) && defined(ARCHITECTURE_X86_64)
#define RK_GUI_MAIN() __fastcall main(int _argc, wchar_t *_argv[])
#else
#define RK_GUI_MAIN() main(int _argc, wchar_t *_argv[])
#endif
