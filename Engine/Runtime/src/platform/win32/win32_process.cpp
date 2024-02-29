#include "pch.hpp"

#ifdef PLATFORM_WINDOWS

#include "platform/win32/win32_process.hpp"

#pragma warning(disable : 6387)

namespace Rake::platform {

std::vector<MemoryDeviceInfo> ListMemoryDevices() {
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);

    DISPLAY_DEVICE displayDevice;
    displayDevice.cb = sizeof(displayDevice);
    std::vector<MemoryDeviceInfo> devices;

    for (DWORD deviceIndex = 0; EnumDisplayDevicesW(NULL, deviceIndex, &displayDevice, 0); ++deviceIndex) {
        devices.emplace_back(memoryStatus.ullTotalPhys, memoryStatus.ullAvailPhys);
    }

    return devices;
}

size_t GetTotalMemory() {
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);

    GlobalMemoryStatusEx(&memoryStatus);

    return static_cast<size_t>(memoryStatus.ullTotalPhys / (1024 * 1024));
}

size_t GetFreeMemory() {
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);

    GlobalMemoryStatusEx(&memoryStatus);

    return static_cast<size_t>(memoryStatus.ullAvailPhys / (1024 * 1024));
}

std::vector<StorageDeviceInfo> ListStorageDevices() {
    DWORD drives = GetLogicalDrives();
    std::vector<StorageDeviceInfo> devices;

    for (int driveIndex = 0; driveIndex < 26; ++driveIndex) {
        if (drives & (1 << driveIndex)) {
            wchar_t driveLetter[4];
            swprintf(driveLetter, L"%c:\\", driveIndex + L'A');

            ULARGE_INTEGER totalSpace, freeSpace;

            if (GetDiskFreeSpaceExW(driveLetter, NULL, &totalSpace, &freeSpace)) {
                devices.emplace_back(driveLetter, totalSpace.QuadPart, freeSpace.QuadPart);
            }
        }
    }

    return devices;
}

bool LockFileInExplorer(const std::wstring &_path) {
    HANDLE hFile = CreateFileW(_path.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        return false;
    }

    if (LockFile(hFile, 0, 0, 0xFFFFFFFF, 0xFFFFFFFF)) {
        return true;
    } else {
        CloseHandle(hFile);
        return false;
    }
}

bool HideFileInExplorer(const std::wstring &_path) {
    if (SetFileAttributesW(_path.c_str(), FILE_ATTRIBUTE_HIDDEN)) {
        return true;
    } else {
        return false;
    }
}

bool CreateConsole(const std::wstring &_title) {
    if (!AllocConsole()) return false;

    FILE *fp = nullptr;

    if (::GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE) {
        if (freopen_s(&fp, "CONIN$", "r", stdin) != NULL) {
            return false;
        }

        setvbuf(stdin, NULL, _IONBF, 0);
    }

    if (::GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE) {
        if (freopen_s(&fp, "CONOUT$", "w", stdout) != NULL) {
            return false;
        }

        setvbuf(stdout, NULL, _IONBF, 0);
    }

    if (::GetStdHandle(STD_ERROR_HANDLE) != INVALID_HANDLE_VALUE) {
        if (freopen_s(&fp, "CONOUT$", "w", stderr) != NULL) {
            return false;
        }

        setvbuf(stderr, NULL, _IONBF, 0);
    }

    std::ios::sync_with_stdio(true);

    SetConsoleTitleW(_title.c_str());

    return true;
}

bool DestroyConsole() {
    FILE *fp = nullptr;

    if (freopen_s(&fp, "NUL:", "r", stdin) != 0) {
        return false;
    }

    setvbuf(stdin, NULL, _IONBF, 0);

    if (freopen_s(&fp, "NUL:", "w", stdout) != 0) {
        return false;
    }

    setvbuf(stdout, NULL, _IONBF, 0);

    if (freopen_s(&fp, "NUL:", "w", stderr) != 0) {
        return false;
    }

    setvbuf(stderr, NULL, _IONBF, 0);

    if (!FreeConsole()) return false;

    return true;
}

std::vector<std::wstring> ListEnvironmentVariables() {
    LPWCH environmentBlock = GetEnvironmentStringsW();

    if (environmentBlock == nullptr) {
        return std::vector<std::wstring>();
    }

    std::vector<std::wstring> envVariables;
    LPWSTR currentVariable = environmentBlock;

    while (*currentVariable != L'\0') {
        std::wstring variable(currentVariable);

        envVariables.push_back(variable);

        currentVariable += variable.length() + 1;
    }

    FreeEnvironmentStringsW(environmentBlock);

    return envVariables;
}

bool EnvironmentVariableExists(const std::wstring &_varName) {
    return GetEnvironmentVariableW(_varName.c_str(), nullptr, 0) > 0;
}

bool CreateOrSetEnvironmentVariable(const std::wstring &_varName, const std::wstring &_varValue) {
    return SetEnvironmentVariableW(_varName.c_str(), _varValue.c_str()) != 0;
}

bool DeleteEnvironmentVariable(const std::wstring &_varName) {
    return SetEnvironmentVariableW(_varName.c_str(), nullptr) != 0;
}

bool GetEnvironmentVariable(const std::wstring &_varName, std::wstring &_varValue) {
    DWORD bufferSize = GetEnvironmentVariableW(_varName.c_str(), nullptr, 0);

    if (!bufferSize) return false;

    std::wstring buffer(bufferSize, L'\0');

    if (GetEnvironmentVariableW(_varName.c_str(), &buffer[0], bufferSize) > 0) {
        _varValue = buffer;
        return true;
    }

    return false;
}

bool RegistryKeyExists(HKEY _hKey, const std::wstring &_keyPath) {
    return RegOpenKeyExW(_hKey, _keyPath.c_str(), 0, KEY_READ, nullptr) == ERROR_SUCCESS;
}

bool CreateOrSetRegistryValue(
    HKEY _hKey, const std::wstring &_keyPath, const std::wstring &_valueName, const std::wstring &_valueData) {
    HKEY hSubKey;
    DWORD disposition;

    bool result = RegCreateKeyExW(_hKey, _keyPath.c_str(), 0, nullptr, 0, KEY_WRITE, nullptr, &hSubKey, &disposition) !=
                  ERROR_SUCCESS;

    if (!result) return false;

    result = RegSetValueExW(
                 hSubKey,
                 _valueName.c_str(),
                 0,
                 REG_SZ,
                 (const BYTE *)_valueData.c_str(),
                 static_cast<DWORD>(_valueData.size() * sizeof(wchar_t))) != ERROR_SUCCESS;

    if (!result) {
        RegCloseKey(hSubKey);
        return false;
    }

    RegCloseKey(hSubKey);

    return true;
}

bool DeleteRegistryKey(HKEY _hKey, const std::wstring &_keyPath) {
    return RegDeleteTreeW(_hKey, _keyPath.c_str()) == ERROR_SUCCESS;
}

bool GetRegistryValue(
    HKEY _hKey, const std::wstring &_keyPath, const std::wstring &_valueName, std::wstring &_valueData) {
    WCHAR buffer[MAX_PATH];
    DWORD dataSize = sizeof(buffer);

    if (RegGetValueW(_hKey, _keyPath.c_str(), _valueName.c_str(), RRF_RT_REG_SZ, nullptr, buffer, &dataSize) ==
        ERROR_SUCCESS) {
        _valueData = buffer;
        return true;
    }

    return false;
}

bool CallExecutable(
    const std::wstring &_executablePath, const std::wstring &_commandLineArguments, DWORD _creationFlags) {
    STARTUPINFOW startupInfo = {.cb = sizeof(STARTUPINFOW)};

    PROCESS_INFORMATION processInfo;

    std::wstring commandLine = _executablePath + L" " + _commandLineArguments;

    if (!CreateProcessW(
            NULL,
            &commandLine[0],
            NULL,
            NULL,
            FALSE,
            _creationFlags,
            NULL,
            NULL,
            &startupInfo,
            &processInfo))
        return false;

    WaitForSingleObject(processInfo.hProcess, INFINITE);

    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);

    return true;
}

static std::unordered_map<std::wstring, HMODULE> libraryHandles = {};

bool LoadDynamicLibrary(const std::wstring &_path) {
    HMODULE dllHandle = LoadLibraryW(_path.c_str());

    if (!dllHandle) return false;

    libraryHandles[_path] = dllHandle;

    return true;
}

bool UnloadDynamicLibrary(const std::wstring &_path) {
    if (FreeLibrary(libraryHandles[_path])) return false;

    libraryHandles[_path] = nullptr;

    return true;
}

void *LoadFunction(const std::wstring &_path, const std::string &_funcName) {
    void *funcHandle = GetProcAddress(libraryHandles[_path], _funcName.c_str());

    if (!funcHandle) throw std::runtime_error("Failed to get process address from DLL!");

    return funcHandle;
}

}  // namespace Rake::platform

#endif
