#pragma once

RK_DISABLE_WARNINGS
#include <nlohmann/json.hpp>
RK_RESTORE_WARNINGS

#include "RKRuntime/base.hpp"

namespace Rake::core {

/**
 * @brief Structure containing constants for file open modes.
 */
struct FileOpenMode {
    static inline constexpr int read = std::ios::in;
    static inline constexpr int write = std::ios::out;
    static inline constexpr int binary = std::ios::binary;
    static inline constexpr int append = std::ios::app;
    static inline constexpr int atEnd = std::ios::ate;
    static inline constexpr int truncate = std::ios::trunc;
    static inline constexpr int readBinary = read | binary;
    static inline constexpr int writeBinary = write | binary;
    static inline constexpr int appendBinary = append | binary;
    static inline constexpr int readWrite = read | write;
    static inline constexpr int readWriteBinary = read | write | binary;
};

/**
 * @brief Structure containing constants for file permissions.
 */
struct FilePermissions {
    static inline constexpr std::filesystem::perms read = std::filesystem::perms::owner_read;
    static inline constexpr std::filesystem::perms write = std::filesystem::perms::owner_write;
    static inline constexpr std::filesystem::perms execute = std::filesystem::perms::owner_exec;
    static inline constexpr std::filesystem::perms readWrite = read | write;
    static inline constexpr std::filesystem::perms readExecute = read | execute;
    static inline constexpr std::filesystem::perms writeExecute = write | execute;
    static inline constexpr std::filesystem::perms readWriteExecute = read | write | execute;
};

/**
 * @brief Checks if a file exists at the given path.
 *
 * @param _path The path to the file.
 * @return true if the file exists, false otherwise.
 */
RK_API NODISCARD bool FileExists(const std::wstring &_path);

/**
 * @brief Get the size of a file at the given path.
 *
 * @param _path The path to the file.
 * @return The size of the file in bytes.
 */
RK_API NODISCARD size_t GetFileSize(const std::wstring &_path);

/**
 * @brief Get the permissions of a file at the given path.
 *
 * @param _path The path to the file.
 * @return The permissions of the file.
 */
RK_API NODISCARD std::filesystem::perms GetFilePermissions(const std::wstring &_path);

/**
 * @brief Set the permissions of a file at the given path.
 *
 * @param _path The path to the file.
 * @param _permissions The new permissions to set.
 */
RK_API void SetFilePermissions(const std::wstring &_path, int _permissions);

/**
 * @brief Create an empty file at the given path.
 *
 * @param _path The path to the file to be created.
 */
RK_API void CreateFile(const std::wstring &_path);

/**
 * @brief Remove a file at the given path.
 *
 * @param _path The path to the file to be removed.
 */
RK_API void RemoveFile(const std::wstring &_path);

/**
 * @brief Copy a file from the source path to the destination path.
 *
 * @param _srcPath The source path of the file.
 * @param _dstPath The destination path to copy the file to.
 */
RK_API void CopyFile(const std::wstring &_srcPath, const std::wstring &_dstPath);

/**
 * @brief Rename a file from the old filename to the new filename.
 *
 * @param _oldFilename The current name of the file.
 * @param _newFilename The new name for the file.
 */
RK_API void RenameFile(const std::wstring &_oldFilename, const std::wstring &_newFilename);

/**
 * @brief Write text to a file at the given path.
 *
 * @param _path The path to the file.
 * @param _text The text to write to the file.
 * @param _openMode The file open mode (e.g., read, write, binary, append, etc.).
 */
RK_API void WriteFile(const std::wstring &_path, const std::wstring &_text, int _openMode);

/**
 * @brief Read the contents of a text file at the given path.
 *
 * @param _path The path to the file to read.
 * @return The content of the file as a wide string.
 */
RK_API std::wstring ReadFile(const std::wstring &_path);

/**
 * @brief Write text to a specific line in a file at the given path.
 *
 * @param _path The path to the file.
 * @param _text The text to write to the file.
 * @param _line The line number where the text should be written.
 */
RK_API void WriteAtLine(const std::wstring &_path, const std::wstring &_text, size_t _line);

/**
 * @brief Read the content of a specific line in a text file at the given path.
 *
 * @param _path The path to the file.
 * @param _line The line number to read.
 * @return The content of the specified line as a wide string.
 */
RK_API std::wstring ReadAtLine(const std::wstring &_path, size_t _line);

/**
 * @brief Read lines from a text file, starting from a specific line and ending at another line.
 *
 * @param _path The path to the file.
 * @param _startLine The line to start reading from.
 * @param _endLine The line to stop reading at.
 * @return A vector of wide strings containing the lines read.
 */
RK_API std::vector<std::wstring> ReadFromLineToLine(const std::wstring &_path, size_t _startLine, size_t _endLine);

/**
 * @brief Read all lines from a text file.
 *
 * @param _path The path to the file.
 * @return A vector of wide strings containing all lines in the file.
 */
RK_API std::vector<std::wstring> ReadByLine(const std::wstring &_path);

/**
 * @brief Write binary data to a file at the given path.
 *
 * @param _path The path to the file.
 * @param _data The binary data to write.
 * @param _count The number of bytes to write.
 */
RK_API void WriteBinary(const std::wstring &_path, const std::vector<char> &_data, uint32_t _count);

/**
 * @brief Read binary data from a file at the given path.
 *
 * @param _path The path to the file.
 * @param _count The number of bytes to read.
 * @return A vector of uint8_t containing the read binary data.
 */
RK_API std::vector<uint8_t> ReadBinary(const std::wstring &_path, size_t _count);

/**
 * @brief Write a JSON object to a file at the given path.
 *
 * @param _path The path to the JSON file.
 * @param _json The JSON object to write to the file.
 */
RK_API void WriteJSON(const std::wstring &_path, const nlohmann::json &_json);

/**
 * @brief Read a JSON object from a file at the given path.
 *
 * @param _path The path to the JSON file.
 * @return The JSON object read from the file.
 */
RK_API nlohmann::json ReadJSON(const std::wstring &_path);

/**
 * @brief Create a directory at the given path.
 *
 * @param _dir The path to the directory to be created.
 */
RK_API void CreateDirectory(const std::wstring &_dir);

/**
 * @brief Remove a directory at the given path.
 *
 * @param _dir The path to the directory to be removed.
 * @param _recurse Set to true to recursively remove the directory and its contents.
 */
RK_API void RemoveDirectory(const std::wstring &_dir, bool _recurse);

/**
 * @brief FileWatcher class for monitoring changes in a directory.
 */
class FileWatcher final {
   private:
    enum class FileStatus {
        erased,
        created,
        modified,
    };

    std::wstring m_path;
    std::atomic<bool> m_isRunning;
    std::chrono::milliseconds m_interval;
    std::unordered_map<std::wstring, std::filesystem::file_time_type> m_paths;

   public:
    /**
     * @brief Constructor for the FileWatcher class.
     *
     * @param _path The path to the directory to watch.
     * @param _interval The interval for checking changes.
     */
    RK_API explicit FileWatcher(const std::wstring &_path, std::chrono::milliseconds _interval);

   public:
    /**
     * @brief Start monitoring the directory for changes.
     *
     * @param _callback The callback function to execute when changes occur.
     */
    RK_API void Start(const std::function<void(const std::wstring &, FileStatus)> &_callback) noexcept;

    /**
     * @brief Stop the FileWatcher.
     */
    RK_API void Stop() noexcept;
};

}  // namespace Rake::core
