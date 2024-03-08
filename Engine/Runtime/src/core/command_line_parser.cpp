#include "pch.hpp"

#include "core/command_line_parser.hpp"

namespace Rake::core {

std::unordered_map<std::string, CommandLineParser::Option> CommandLineParser::options;

bool CommandLineParser::IsOption(const char* _option) { return options.find(_option) != options.end(); }

void CommandLineParser::ParseOptions(int _argc, const char* _argv[]) {
    if (_argc <= 1) {
        return;
    } else if (_argc >= 32) {
        RK_LOG_ERROR(L"Too many command line options/values, skipping!");
        return;
    }

    for (int opt = 1; opt < _argc; ++opt) {
        if (!IsOption(_argv[opt])) {
            RK_LOG_ERROR(L"Unknown option/value '{}', skipping!", libraries::ByteToWideString(_argv[opt]));
            continue;
        }

        if (m_options.at(_argv[opt]).expectsValueList) {
            int val = opt + 1;
            while (val < _argc && !IsOption(_argv[val])) {
                if (m_options.at(_argv[opt]).handler(_argv[val])) {
                        RK_LOG_DEBUG(
                        L"Set value '{}' for option '{}!'",
                        libraries::ByteToWideString(_argv[val]),
                        libraries::ByteToWideString(_argv[opt]));
                    } else {
                        RK_LOG_ERROR(
                        L"Failed to set value '{}' for option '{}'!",
                        libraries::ByteToWideString(_argv[val]),
                        libraries::ByteToWideString(_argv[opt]));
                    }
                ++val;
                }
            opt = val - 1;
        } else {
            if (m_options.at(_argv[opt]).handler("")) {
                RK_LOG_DEBUG(L"Set option '{}'!", libraries::ByteToWideString(_argv[opt]));
            } else {
                RK_LOG_ERROR(L"Failed to set option '{}'!", libraries::ByteToWideString(_argv[opt]));
            }
        } else {
            RK_LOG_ERROR(L"Unknown command line option '{}', skipping!", libraries::ByteToWideString(_argv[i]));
        }
    }
}

void CommandLineParser::RegisterOption(
    const std::string& _optionName,
    bool _expectsValueList,
    bool _requestsTermination,
    std::function<bool(const char*)> _handler) {
    m_options[_optionName] = Option(_expectsValueList, _requestsTermination, _handler);
}

void CommandLineParser::UnregisterOption(const std::string& _optionName) { m_options.erase(_optionName); }

void CommandLineParser::UnregisterAllOptions() { m_options.clear(); }

}  // namespace Rake::core
