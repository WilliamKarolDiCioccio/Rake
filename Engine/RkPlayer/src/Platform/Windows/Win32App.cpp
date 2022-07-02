#include "src/RkPch.h"

#if defined(PLATFORM_WINDOWS) == 1

#include "Win32App.hpp"

namespace Rake::Platform::Windows
{

Win32App::Win32App()
{
    if (!this->CheckMutex())
        RK_SIGTERM;
}

Win32App::~Win32App()
{
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

B8 Windows::Win32App::CheckMutex()
{
    HANDLE mutex = OpenMutex(MUTEX_ALL_ACCESS, NULL, L"RakeInstance");

    if (mutex == NULL)
    {
        mutex = CreateMutex(NULL, NULL, L"RakeInstance");
        return true;
    }
    else
    {
        ReleaseMutex(mutex);
        throw Core::Error::RkException("Another instance of the program is already registered!", __FILE__, __LINE__);
        return false;
    }
}

} // namespace Rake::Platform::Windows

#endif
