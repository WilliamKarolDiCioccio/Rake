#include "src/RkPch.hpp"

#if defined(PLATFORM_WINDOWS)

#include "Win32App.hpp"

namespace Rake::Windows
{

Win32App::Win32App()
{
    hMutex = OpenMutex(MUTEX_ALL_ACCESS, NULL, L"RakeInstance");

    if (hMutex == NULL)
        hMutex = CreateMutex(NULL, NULL, L"RakeInstance");
    else
    {
    }

    processId = GetCurrentProcessId();
}

Win32App::~Win32App()
{
    if (hMutex != NULL)
        ReleaseMutex(hMutex);
}

void Win32App::PumpPlatformMessages()
{
    MSG msg;

    if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

} // namespace Rake::Windows

#endif
