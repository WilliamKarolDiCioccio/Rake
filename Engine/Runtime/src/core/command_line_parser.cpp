#include "pch.hpp"

#include "core/command_line_parser.hpp"

#include <filesystem>

namespace Rake::core {

std::string CommandLineParser::m_executableName;
std::string CommandLineParser::m_executablePath;
std::vector<std::string> CommandLineParser::m_args;
bool CommandLineParser::m_abort;
std::unordered_map<std::string, CommandLineParser::Option> CommandLineParser::m_options;

bool CommandLineParser::IsOptionRegistered(const std::string& _option) {
    return m_options.find(_option) != m_options.end();
}

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

std::string CommandLineParser::SuggetCorrectOption(const std::string& _mispelledOption) {
    uint8_t minDistance = 3;
    std::string correctOption = _mispelledOption;

    for (const auto& [k, v] : m_options) {
        uint8_t distance = OptionSpellCheck(_mispelledOption, k);

        if (distance < minDistance) {
            minDistance = distance;
            correctOption = k;
        }
    }

    return correctOption;
}

std::vector<std::pair<std::string, std::vector<std::string>>> CommandLineParser::ExtractOptionArgumentsPairs(
    const std::vector<std::string>& _args) {
    std::vector<std::pair<std::string, std::vector<std::string>>> optArgsPairs;

    for (auto i = 0; i < _args.size(); ++i) {
        if (_args[i].starts_with("--") || _args[i].starts_with("-")) {
            optArgsPairs.push_back({_args[i], {}});

            if (i == _args.size() - 1) break;

            for (auto j = i + 1; j < _args.size(); ++j) {
                if (_args[j].starts_with("--") || _args[j].starts_with("-")) {
                    break;
                } else {
                    optArgsPairs.back().second.emplace_back(_args[j]);
                }
            }

            i += optArgsPairs.back().second.size();
        } else {
            std::cerr << "Argument '" << _args[i] << "' is not an option, skipping!\n";
        }
    }

    return optArgsPairs;
}

bool CommandLineParser::HandleOptionArgumentsPair(const std::pair<std::string, std::vector<std::string>>& _args) {
    if (!IsOptionRegistered(_args.first)) {
        std::cerr << "Unknown option '" << _args.first << "', discarded!\n";

        const auto suggestion = SuggetCorrectOption(_args.first);

        if (suggestion != _args.first) std::cerr << "Maybe you meant '" << suggestion << "'!\n";

        return true;
    }

    const auto& option = m_options.at(_args.first);

    if (option.abort) m_abort = true;

    if (option.valueType != CmdOptionValueTypes::None && _args.second.empty()) {
        std::cerr << "Option '" << _args.first << "' requires arguments, discarded!\n";
        return false;
    } else if (option.valueType == CmdOptionValueTypes::None && !_args.second.empty()) {
        std::cerr << "Option '" << _args.first << "' does not accept any arguments, skipping!\n";
        return true;
    } else if (option.valueType == CmdOptionValueTypes::Single && _args.second.size() > 1) {
        std::cerr << "Option '" << _args.first << "' accepts only one argument, skipping!\n";
        return false;
    } else if (option.valueType == CmdOptionValueTypes::Multiple && _args.second.size() < 1) {
        std::cerr << "Option '" << _args.first << "' requires at least two arguments, skipping!\n";
        return false;
    }

    if (option.valueType == CmdOptionValueTypes::None) {
        return option.handler(std::string());
    } else {
        for (const auto& arg : _args.second) {
            if (!option.handler(arg)) return false;
        }
    }

    return true;
}

void CommandLineParser::RegisterDefaultOptions() {
    RegisterOption("help", "Prints the help message", "", CmdOptionValueTypes::None, true, [](const std::string&) {
        std::cout << "Help message:\n";

        for (const auto& [k, v] : m_options) {
            std::cout << k << ":\t" << v.help << '\n';
        }

        return true;
    });

    RegisterOption("abort", "Aborts the program", "", CmdOptionValueTypes::None, true, [](const std::string&) {
        return true;
    });
}

void CommandLineParser::ParseCommandLine(int _argc, const char* _argv[]) {
    RegisterDefaultOptions();

    if (_argc == 1) {
        std::cerr << "No command line options/values, skipping!\n";
        return;
    } else if (_argc >= 32) {
        std::cerr << "Too many command line options/values, skipping!\n";
        return;
    }

    m_executablePath = std::filesystem::path(_argv[0]).parent_path().string();
    m_executableName = std::filesystem::path(_argv[0]).filename().string();

    for (int i = 1; i < _argc; ++i) {
        m_args.push_back(_argv[i]);
    }

    const auto optArgsPairs = ExtractOptionArgumentsPairs(m_args);

    for (const auto& optArgsPair : optArgsPairs) {
        if (!HandleOptionArgumentsPair(optArgsPair)) {
            std::cerr << "Failed to handle option/arguments pair, aborting!\n";
            m_abort = true;
        }
    }
}

void Rake::core::CommandLineParser::RegisterOption(
    const std::string _name,
    const std::string& _description,
    const std::string& _help,
    CmdOptionValueTypes _valueType,
    bool _requestsTermination,
    std::function<bool(const std::string&)> _handler) {
    RK_ASSERT(!_name.empty());

    if (_name.length() == 1) {
        RK_ASSERT((m_options.find('-' + _name) == m_options.end()));
        m_options[('-' + _name)] = Option(_name, _description, _help, _valueType, _requestsTermination, _handler);
    } else {
        RK_ASSERT(m_options.find("--" + _name) == m_options.end());
        m_options[("--" + _name)] = Option(_name, _description, _help, _valueType, _requestsTermination, _handler);
    }
}

void CommandLineParser::UnregisterOption(const std::string& _optionName) { m_options.erase(_optionName); }

void CommandLineParser::UnregisterAllOptions() { m_options.clear(); }

}  // namespace Rake::core
