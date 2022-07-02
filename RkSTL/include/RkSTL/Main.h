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
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
#define RK_GUI_MAIN() main(int argc, char *argv[])
#endif

#include <windows.h>
#include <shellapi.h>

void ParseCommandLineArguments()
{
    int argc;
    wchar_t **argv = ::CommandLineToArgvW(::GetCommandLineW(), &argc);

    for (size_t i = 0; i < argc; ++i)
    {
    }
}
