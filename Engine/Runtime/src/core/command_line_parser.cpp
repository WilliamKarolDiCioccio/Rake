#include "pch.hpp"

#include "core/command_line_parser.hpp"

namespace Rake::core {

std::unordered_map<std::string, CommandLineParser::Option> CommandLineParser::m_options;

bool CommandLineParser::IsOption(const char* _option) { return m_options.find(_option) != m_options.end(); }

void CommandLineParser::ParseOptions(int _argc, const char* _argv[]) {
    if (_argc <= 1) {
        return;
    } else if (_argc >= 32) {
        std::cerr << "Too many command line options/values, skipping!\n";
        return;
    }

    for (int opt = 1; opt < _argc; ++opt) {
        if (!IsOption(_argv[opt])) {
            std::cerr << "Unknown option/value '" << _argv[opt] << "', skipping!\n";
            continue;
        }

        if (m_options.at(_argv[opt]).expectsValueList) {
            int val = opt + 1;
            while (val < _argc && !IsOption(_argv[val])) {
                if (m_options.at(_argv[opt]).handler(_argv[val])) {
                    std::cout << "Set value '" << _argv[val] << "' for option '" << _argv[opt] << "'\n";
                } else {
                    std::cerr << "Failed to set value '" << _argv[val] << "' for option '" << _argv[opt] << "'!\n";
                }
                ++val;
            }
            opt = val - 1;
        } else {
            if (m_options.at(_argv[opt]).handler("")) {
                std::cout << "Set option '" << _argv[opt] << "'!\n";
            } else {
                std::cerr << "Failed to set option '" << _argv[opt] << "'!\n";
        }
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
