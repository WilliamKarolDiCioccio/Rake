#include "pch.hpp"

#include "core/command_line_parser.hpp"

namespace Rake::core {

std::unordered_map<std::string, CommandLineParser::Option> CommandLineParser::options;

bool CommandLineParser::IsOption(const char* _option) { return options.find(_option) != options.end(); }

void CommandLineParser::ParseOptions(int _argc, const char* _argv[]) {
    if (_argc <= 1) {
        return;
    } else if (_argc >= 32) {
        RK_LOG_ERROR(L"Too many command line options/arguments, skipping!");
        return;
    }

    for (int i = 1; i < _argc; ++i) {
        if (IsOption(_argv[i])) {
            std::string option = _argv[i];
            if (options.at(_argv[i]).expectsValueList) {
                while (i + 1 < _argc && !IsOption(_argv[i + 1])) {
                    if (options.at(_argv[i]).handler(_argv[i + 1])) {
                        RK_LOG_DEBUG(
                            L"Set argument '{}' for option '{}!'",
                            libraries::ByteToWideString(_argv[i + 1]),
                            libraries::ByteToWideString(_argv[i]));
                    } else {
                        RK_LOG_ERROR(
                            L"Failed to parse argument '{}' for option '{}', skipping!",
                            libraries::ByteToWideString(_argv[i + 1]),
                            libraries::ByteToWideString(_argv[i]));
                    }
                    ++i;
                }
            } else {
                options.at(_argv[i]).handler("");
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
    options[_optionName] = Option(_expectsValueList, _requestsTermination, _handler);
}

}  // namespace Rake::core
