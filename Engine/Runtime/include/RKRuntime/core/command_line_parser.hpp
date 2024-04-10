#pragma once

#include <functional>
#include <unordered_map>
#include <string>

#include "RKRuntime/base.hpp"

#include <RKSTL/enum.hpp>

namespace Rake::core {

enum class CmdOptionValueTypes : uint8_t {
    None = 0 << 0,
    Single = 1 << 0,
    Multiple = 1 << 1,
};

class RK_API CommandLineParser {
   private:
    struct Option {
        std::string name;
        std::string description;
        std::string help;
        libraries::EnumFlags<CmdOptionValueTypes> valueType;
        bool abort;
        std::function<bool(const std::string&)> handler;

        Option() : valueType(CmdOptionValueTypes::None), abort(false), handler({}){};
        Option(
            const std::string _name,
            const std::string& _description,
            const std::string& _help,
            CmdOptionValueTypes _valueType,
            bool _abort,
            std::function<bool(const std::string&)> _handler)
            : name(_name),
              description(_description),
              help(_help),
              valueType(_valueType),
              abort(_abort),
              handler(_handler) {}
    };

    static std::string m_executableName;
    static std::string m_executablePath;
    static std::vector<std::string> m_args;
    static bool m_abort;
    static std::unordered_map<std::string, Option> m_options;

   private:
    CommandLineParser() = delete;

   private:
    static bool IsOptionRegistered(const std::string& _option);
    static uint8_t OptionSpellCheck(const std::string& _mispelledOption, const std::string& _correctOption);
    static std::string SuggetCorrectOption(const std::string& _mispelledOption);
    static std::vector<std::pair<std::string, std::vector<std::string>>> ExtractOptionArgumentsPairs(
        const std::vector<std::string>& _args);
    static bool HandleOptionArgumentsPair(const std::pair<std::string, std::vector<std::string>>& _args);
    static void RegisterDefaultOptions();

   public:
    static void ParseCommandLine(int _argc, const char* _argv[]);
    static void RegisterOption(
        const std::string _name,
        const std::string& _description,
        const std::string& _help,
        CmdOptionValueTypes _valueType,
        bool _abort,
        std::function<bool(const std::string&)> _handler);
    static void UnregisterOption(const std::string& _optionName);
    static void UnregisterAllOptions();

   public:
    NODISCARD static inline bool ExecutionAborted() noexcept { return m_abort; }
    NODISCARD static inline const std::vector<std::string>& GetArgv() noexcept { return m_args; }
    NODISCARD static inline uint8_t GetArgc() noexcept { return m_args.size(); }
    NODISCARD static inline const std::string& GetExecutableName() noexcept { return m_executableName; }
    NODISCARD static inline const std::string& GetExecutablePath() noexcept { return m_executablePath; }
};

}  // namespace Rake::core
