#pragma once

RK_DISABLE_WARNINGS
#include <wrl.h>
#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
RK_RESTORE_WARNINGS

#undef min
#undef max
#undef SetIcon
#undef SetCursor
#undef CreateWindow
#undef CreateFile
#undef CopyFile
#undef MoveFile
#undef DeleteFile
#undef FindFirstFile
#undef FindNextFile
#undef CreateDirectory
#undef RemoveDirectory
#undef GetEnvironmentVariable
#undef SetEnvironmentVariable
#undef DeleteEnvironmentVariable
#undef RegCreateKey
#undef RegCreateKeyEx
#undef RegOpenKey
#undef RegOpenKeyEx
#undef RegSetValue
#undef RegSetValueEx
#undef RegDeleteKey
#undef RegDeleteTree
