#include "pch.hpp"

#include "core/command_line_parser.hpp"

namespace Rake::core {

std::unordered_map<std::string, CommandLineParser::Option> CommandLineParser::m_options;

bool CommandLineParser::IsOption(const char* _option) { return m_options.find(_option) != m_options.end(); }

uint8_t Rake::core::CommandLineParser::OptionSpellCheck(
    const std::string& _mispelledOption, const std::string& _correctOption) {
    std::vector<std::vector<int>> dp(_mispelledOption.size() + 1, std::vector<int>(_correctOption.size() + 1, 0));

    for (int i = 0; i <= _mispelledOption.size(); ++i) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= _correctOption.size(); ++j) {
        dp[0][j] = j;
    }

    for (int i = 1; i <= _mispelledOption.size(); ++i) {
        for (int j = 1; j <= _correctOption.size(); ++j) {
            if (_mispelledOption[i - 1] == _correctOption[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = std::min({dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j]}) + 1;
            }
        }
    }

    return dp[_mispelledOption.size()][_correctOption.size()];
}

void CommandLineParser::ParseOptions(int _argc, const char* _argv[]) {
    if (_argc <= 1) {
        return;
    } else if (_argc >= 32) {
        std::cerr << "Too many command line options/values, skipping!\n";
        return;
    }

    for (int opt = 1; opt < _argc; ++opt) {
        if (!IsOption(_argv[opt])) {
            uint8_t minDistance = 3;
            std::string correctOption = _argv[opt];

            for (const auto& [k, v] : m_options) {
                uint8_t distance = OptionSpellCheck(_argv[opt], k);

                if (distance < minDistance) {
                    minDistance = distance;
                    correctOption = k;
                }
            }

            if (correctOption != _argv[opt]) {
                std::cerr << "Mispelled option '" << _argv[opt] << "'!"
                          << " Did you mean '" << correctOption << "'\n";
            } else {
                std::cerr << "Unknown option '" << _argv[opt] << "'!\n";
            }

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
