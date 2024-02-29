#pragma once

#include "base.hpp"

#ifdef PLATFORM_WINDOWS

#include "win32_common.hpp"

namespace Rake::platform {

struct MemoryDeviceInfo {
    ULONGLONG totalPhysicalMemory;
    ULONGLONG freePhysicalMemory;

    MemoryDeviceInfo(ULONGLONG _total, ULONGLONG _free) : totalPhysicalMemory(_total), freePhysicalMemory(_free) {}
};

/**
 * @brief List memory devices and their information.
 * 
 * @return Vector containing MemoryDeviceInfo for each memory device.
 */
RK_API std::vector<MemoryDeviceInfo> ListMemoryDevices();

/**
 * @brief Get the total physical memory size in megabytes.
 * 
 * @return Total physical memory size in megabytes.
 */
RK_API size_t GetTotalMemory();

/**
 * @brief Get the free physical memory size in megabytes.
 * 
 * @return Free physical memory size in megabytes.
 */
RK_API size_t GetFreeMemory();

struct StorageDeviceInfo {
    std::wstring driveLetter;
    ULONGLONG totalPhysicalStorage;
    ULONGLONG freePhysicalStorage;

    StorageDeviceInfo(const std::wstring &_letter, ULONGLONG _total, ULONGLONG _free)
        : driveLetter(_letter), totalPhysicalStorage(_total), freePhysicalStorage(_free) {}
};

/**
 * @brief List storage devices and their information.
 * 
 * @return Vector containing StorageDeviceInfo for each storage device.
 */
RK_API std::vector<StorageDeviceInfo> ListStorageDevices();

/**
 * @brief Locks a file in Windows Explorer.
 *
 * This function attempts to lock a file specified by its path in Windows Explorer.
 * The file should exist and be accessible for this function to work.
 *
 * @param _path The path to the file that should be locked.
 * @return True if the file is successfully locked, false otherwise.
 */
RK_API bool LockFileInExplorer(const std::wstring &_path);

/**
 * @brief Hides a file in Windows Explorer.
 *
 * This function sets the "hidden" attribute for a file specified by its path in Windows Explorer.
 * The file should exist and be accessible for this function to work.
 *
 * @param _path The path to the file that should be hidden.
 * @return True if the file is successfully hidden, false otherwise.
 */
RK_API bool HideFileInExplorer(const std::wstring &_path);

/**
 * @brief Creates a console window for text-based input and output.
 *
 * @param _title The title to set for the console window.
 * @return True if the console is successfully created; otherwise, false.
 */
RK_API bool CreateConsole(const std::wstring &_title);

/**
 * @brief Destroys the previously created console window.
 *
 * @return True if the console is successfully destroyed; otherwise, false.
 */
RK_API bool DestroyConsole();

/**
 * @brief Retrieves all environment variables and returns them in a vector of wstrings.
 *
 * @return A vector of wstrings containing all environment variables.
 */
RK_API std::vector<std::wstring> ListEnvironmentVariables();

/**
 * @brief Checks if an environment variable exists.
 *
 * @param _varName The name of the environment variable to check.
 * @return True if the environment variable exists; otherwise, false.
 */
RK_API bool EnvironmentVariableExists(const std::wstring &_varName);

/**
 * @brief Sets an environment variable.
 *
 * @param _varName The name of the environment variable.
 * @param _varValue The value to set for the environment variable.
 * @return True if the operation is successful; otherwise, false.
 */
RK_API bool CreateOrSetEnvironmentVariable(const std::wstring &_varName, const std::wstring &_varValue);

/**
 * @brief Deletes an environment variable.
 *
 * @param _varName The name of the environment variable to delete.
 * @return True if the environment variable is successfully deleted; otherwise, false.
 */
RK_API bool DeleteEnvironmentVariable(const std::wstring &_varName);

/**
 * @brief Gets the value of an environment variable.
 *
 * @param _varName The name of the environment variable.
 * @param _varValue Output parameter to store the value of the environment variable.
 * @return True if the environment variable exists and its value is retrieved; otherwise, false.
 */
RK_API bool GetEnvironmentVariable(const std::wstring &_varName, std::wstring &_varValue);

/**
 * @brief Checks if a registry key exists.
 *
 * @param _hKey The registry hive to check (e.g., HKEY_LOCAL_MACHINE).
 * @param _keyPath The path to the registry key.
 * @return True if the registry key exists; otherwise, false.
 */
RK_API bool RegistryKeyExists(HKEY _hKey, const std::wstring &_keyPath);

/**
 * @brief Creates or sets a registry key and its value.
 *
 * @param _hKey The registry hive to create or set the key.
 * @param _keyPath The path to the registry key.
 * @param _valueName The name of the value to set.
 * @param _valueData The data to set for the value.
 * @return True if the registry key and value are successfully created or set; otherwise, false.
 */
RK_API bool CreateOrSetRegistryValue(
    HKEY _hKey, const std::wstring &_keyPath, const std::wstring &_valueName, const std::wstring &_valueData);

/**
 * @brief Deletes a registry key and its subkeys.
 *
 * @param _hKey The registry hive to delete the key.
 * @param _keyPath The path to the registry key.
 * @return True if the registry key and its subkeys are successfully deleted; otherwise, false.
 */
RK_API bool DeleteRegistryKey(HKEY _hKey, const std::wstring &_keyPath);

/**
 * @brief Gets the value of a registry key.
 *
 * @param _hKey The registry hive to read from.
 * @param _keyPath The path to the registry key.
 * @param _valueName The name of the value to retrieve.
 * @param _valueData Output parameter to store the retrieved value.
 * @return True if the registry value is successfully retrieved; otherwise, false.
 */
RK_API bool GetRegistryValue(
    HKEY _hKey, const std::wstring &_keyPath, const std::wstring &_valueName, std::wstring &_valueData);

/**
 * @brief Calls an external executable with optional command line arguments and creation flags.
 *
 * @param _executablePath The path to the executable to run.
 * @param _commandLineArguments Optional command line arguments.
 * @param _creationFlags Optional process creation flags.
 * @return True if the executable is successfully called; otherwise, false.
 */
RK_API bool CallExecutable(
    const std::wstring &_executablePath, const std::wstring &_commandLineArguments = L"", DWORD _creationFlags = 0);

/**
 * @brief Loads a dynamic library (DLL) into the current process.
 *
 * @param _path The path to the dynamic library.
 * @return True if the library is successfully loaded; otherwise, false.
 */
RK_API bool LoadDynamicLibrary(const std::wstring &_path);

/**
 * @brief Unloads a previously loaded dynamic library (DLL).
 *
 * @param _path The path to the dynamic library to unload.
 * @return True if the library is successfully unloaded; otherwise, false.
 */
RK_API bool UnloadDynamicLibrary(const std::wstring &_path);

/**
 * @brief Loads a function from a previously loaded dynamic library.
 *
 * @param _path The path to the dynamic library containing the function.
 * @param _funcName The name of the function to load.
 * @return A pointer to the loaded function, or nullptr if loading fails.
 */
RK_API void *LoadFunction(const std::wstring &_path, const std::string &_funcName);

}  // namespace Rake::platform

#endif
