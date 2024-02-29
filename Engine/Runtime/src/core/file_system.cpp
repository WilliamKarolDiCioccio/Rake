#include "pch.hpp"

#include "core/file_system.hpp"

#ifdef PLATFORM_WINDOWS
#include "platform/win32/win32_process.hpp"
#endif
#include "RKSTL/string.hpp"

#define JSON_DEFAULT_INDENT 2

namespace fs = std::filesystem;

namespace Rake::core {

bool FileExists(const std::wstring &_path) { return fs::exists(_path); }

size_t GetFileSize(const std::wstring &_path) {
    if (!fs::exists(_path)) {
        throw RkException(L"File '{}' does not exist!", _path);
    } else {
        return fs::file_size(_path);
    }
}

std::filesystem::perms GetFilePermissions(const std::wstring &_path) {
    if (!fs::exists(_path)) {
        throw RkException(L"File '{}' does not exist!", _path);
    } else {
        return fs::status(_path).permissions();
    }
}

void SetFilePermissions(const std::wstring &_path, int _permissions) {
    if (!fs::exists(_path)) {
        throw RkException(L"File '{}' does not exist!", _path);
    } else {
        fs::permissions(_path, static_cast<fs::perms>(_permissions));
    }
}

void RenameFile(const std::wstring &_oldFilename, const std::wstring &_newFilename) {
    if (!fs::exists(_oldFilename)) {
        throw RkException(L"File '{}' does not exist!", _oldFilename);
    } else {
        fs::rename(_oldFilename, _newFilename);
    }
}

void CreateFile(const std::wstring &_path) {
    std::wofstream file(_path);

    file << '\0';

    if (!file || !fs::exists(_path)) throw RkException(L"Failed to create or open file '{}'!", _path);
}

void RemoveFile(const std::wstring &_path) {
    if (!fs::exists(_path)) {
        throw RkException(L"File '{}' does not exist!", _path);
    } else {
        fs::remove(_path);
    }
}

void CopyFile(const std::wstring &_srcFilename, const std::wstring &_dstFilename) {
    if (!fs::exists(_srcFilename)) {
        throw RkException(L"File '{}' does not exist!", _srcFilename);
    } else {
        fs::copy_file(_srcFilename, _dstFilename);
    }
}

void WriteFile(const std::wstring &_path, const std::wstring &_text, int _openMode) {
    if (!fs::exists(_path)) throw RkException(L"File '{}' does not exist!", _path);

    std::wofstream file;

    file.open(_path, _openMode);

    if (!file.is_open()) throw RkException(L"Failed to open file '{}'!", _path);

    file << _text;
}

std::wstring ReadFile(const std::wstring &_path) {
    if (!fs::exists(_path)) throw RkException(L"File '{}' does not exist!", _path);

    std::wifstream file;

    file.open(_path, FileOpenMode::read);

    if (!file.is_open()) throw RkException(L"Failed to open file '{}'!", _path);

    std::wstring buffer;

    while (!file.eof()) {
        std::wstring line;
        std::getline(file, line);

        buffer += line;
    }

    return buffer;
}

void WriteAtLine(const std::wstring &_path, const std::wstring &_text, size_t _line) {
    if (!fs::exists(_path)) throw RkException(L"File '{}' does not exist!", _path);

    std::wfstream file;

    file.open(_path, FileOpenMode::write | FileOpenMode::append);

    if (!file.is_open()) throw RkException(L"Failed to open file '{}'!", _path);

    std::wstring buffer;

    size_t currentLine = 1;

    while (currentLine < _line) {
        std::wstring line;
        std::getline(file, line);

        buffer += line;

        currentLine++;
    }

    buffer += _text;

    while (!file.eof()) {
        std::wstring line;
        std::getline(file, line);

        buffer += line;
    }

    file << buffer.c_str();
}

std::wstring ReadAtLine(const std::wstring &_path, size_t _line) {
    if (!fs::exists(_path)) throw RkException(L"File '{}' does not exist!", _path);

    std::wifstream file;

    file.open(_path, FileOpenMode::read);

    if (!file.is_open()) throw RkException(L"Failed to open file '{}'!", _path);

    std::wstring buffer;

    size_t currentLine = 1;

    while (!file.eof() && currentLine <= _line) {
        std::getline(file, buffer);

        currentLine++;
    }

    return buffer;
}

std::vector<std::wstring> ReadFromLineToLine(const std::wstring &_path, size_t _startLine, size_t _endLine) {
    if (!fs::exists(_path)) throw RkException(L"File '{}' does not exist!", _path);

    std::vector<std::wstring> lines(_endLine - _startLine);

    std::wifstream file;

    file.open(_path, FileOpenMode::read);

    if (!file.is_open()) throw RkException(L"Failed to open file '{}'!", _path);

    std::wstring line;
    size_t currentLine = 0;

    while (std::getline(file, line)) {
        currentLine++;

        if (currentLine >= _startLine && currentLine <= _endLine) lines.emplace_back(line);

        if (currentLine > _endLine) break;
    }

    return lines;
}

std::vector<std::wstring> ReadByLine(const std::wstring &_path) {
    if (!fs::exists(_path)) throw RkException(L"File '{}' does not exist!", _path);

    std::wifstream file;

    file.open(_path, FileOpenMode::read);

    if (!file.is_open()) throw RkException(L"Failed to open file '{}'!", _path);

    std::vector<std::wstring> lines = {};

    while (!file.eof()) {
        std::wstring line;
        std::getline(file, line);

        lines.push_back(line);
    }

    return lines;
}

void WriteBinary(const std::wstring &_path, const std::vector<char> &_data, uint32_t _count) {
    if (!fs::exists(_path)) throw RkException(L"File '{}' does not exist!", _path);

    std::wofstream file;

    file.open(_path, FileOpenMode::writeBinary);

    if (!file.is_open()) throw RkException(L"Failed to open file '{}'!", _path);

    file.write(reinterpret_cast<const wchar_t *>(_data.data()), _count);
}

std::vector<uint8_t> ReadBinary(const std::wstring &_path, size_t _count) {
    if (!fs::exists(_path)) throw RkException(L"File '{}' does not exist!", _path);

    std::wifstream file;

    file.open(_path, FileOpenMode::readBinary);

    if (!file.is_open()) throw RkException(L"Failed to open file '{}'!", _path);

    std::vector<uint8_t> data(_count);

    file.read(reinterpret_cast<wchar_t *>(data.data()), _count);

    return data;
}

void WriteJSON(const std::wstring &_path, const nlohmann::json &_json) {
    if (!fs::exists(_path)) throw RkException(L"File '{}' does not exist!", _path);

    std::wofstream file;

    file.open(_path, FileOpenMode::write);

    if (!file.is_open()) throw RkException(L"Failed to open file '{}'!", _path);

    file << libraries::ByteToWideString(_json.dump(JSON_DEFAULT_INDENT));

    file.close();
}

nlohmann::json ReadJSON(const std::wstring &_path) {
    if (!fs::exists(_path)) throw RkException(L"File '{}' does not exist!", _path);

    std::ifstream file;

    file.open(_path, FileOpenMode::read);

    if (!file.is_open()) throw RkException(L"Failed to open file '{}'!", _path);

    nlohmann::json data = nlohmann::json::parse(file);

    return data;
}

void CreateDirectory(const std::wstring &_dir) { fs::create_directories(_dir); }

void RemoveDirectory(const std::wstring &_dir, bool _recurse) {
    if (_recurse) {
        fs::remove_all(_dir);
    } else {
        fs::remove(_dir);
    }
}

FileWatcher::FileWatcher(const std::wstring &_path, std::chrono::milliseconds _interval)
    : m_path(_path), m_interval(_interval) {
    for (auto &file : fs::recursive_directory_iterator(m_path)) {
        m_paths[file.path().wstring()] = fs::last_write_time(file);
    }
}

void FileWatcher::Start(const std::function<void(const std::wstring &, FileStatus)> &_callback) noexcept {
    m_isRunning.store(true, std::memory_order_relaxed);

    std::shared_mutex pathsMutex;

    std::thread([this, _callback]() {
        while (m_isRunning.load(std::memory_order_relaxed)) {
            auto it = m_paths.begin();

            while (it != m_paths.end()) {
                if (!fs::exists(it->first)) {
                    _callback(it->first, FileStatus::erased);

                    it = m_paths.erase(it);
                } else {
                    ++it;
                }
            }

            for (const auto &file : fs::recursive_directory_iterator(m_path)) {
                const auto lastWriteTime = fs::last_write_time(file);
                const auto filePath = file.path().wstring();

                if (!m_paths.contains(filePath)) {
                    m_paths[filePath] = lastWriteTime;

                    _callback(filePath, FileStatus::created);
                } else if (m_paths[filePath] != lastWriteTime) {
                    m_paths[filePath] = lastWriteTime;

                    _callback(filePath, FileStatus::modified);
                }
            }

            std::this_thread::sleep_for(m_interval);
        }
    }).detach();
}

void FileWatcher::Stop() noexcept { m_isRunning.store(false, std::memory_order_relaxed); }

}  // namespace Rake::core
