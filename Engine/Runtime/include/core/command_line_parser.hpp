#pragma once

#include <functional>
#include <unordered_map>
#include <string>

#include "base.hpp"

namespace Rake::core {

class RK_API CommandLineParser {
   private:
    struct Option {
        bool expectsValueList;
        bool requestsTermination;
        std::function<bool(const char*)> handler;

        Option() : expectsValueList(false), requestsTermination(false), handler({}){};
        Option(bool _expectsValueList, bool _requestsTermination, std::function<bool(const char*)> _handler)
            : expectsValueList(_expectsValueList), requestsTermination(_requestsTermination), handler(_handler) {}
    };

    static std::unordered_map<std::string, Option> m_options;

   private:
    CommandLineParser() = delete;

   public:
    static bool IsOption(const char* _option);
    static uint8_t OptionSpellCheck(const std::string& _mispelledOption, const std::string& _correctOption);
    static void ParseOptions(int argc, const char* argv[]);
    static void RegisterOption(
        const std::string& optionName,
        bool _expectsValueList,
        bool _requestsTermination,
        std::function<bool(const char*)> _handler);
    static void UnregisterOption(const std::string& optionName);
    static void UnregisterAllOptions();
};

}  // namespace Rake::core
