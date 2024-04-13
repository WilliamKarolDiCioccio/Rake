#pragma once

#include <functional>
#include <unordered_map>
#include <string>

#include "RKRuntime/base.hpp"

#include <RKSTL/enum.hpp>

namespace Rake::core {

/**
 * @brief The command line option value types.
 */
enum class CmdOptionValueTypes : uint8_t {
    None = 0 << 0,
    Single = 1 << 0,
    Multiple = 1 << 1,
};

/**
 * @brief The command line parser class is used to manage and parse command line arguments.
 * 
 * @note The command line parser is a static class and should be used as such.
 */
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
    /**
     * @brief Parse the command line arguments.
     * 
     * @param _argc The number of arguments.
     * @param _argv The arguments.
     */
    static void ParseCommandLine(int _argc, const char* _argv[]);

    /**
     * @brief Register a command line option.
     * 
     * @param _name The name of the option
     * @param _description The description of the option
     * @param _help The help message of the option
     * @param _valueType The value type of the option
     * @param _abort If the option should abort the execution
     * @param _handler The handler of the option
	 */
    static void RegisterOption(
        const std::string _name,
        const std::string& _description,
        const std::string& _help,
        CmdOptionValueTypes _valueType,
        bool _abort,
        std::function<bool(const std::string&)> _handler);

    /**
     * @brief Unregister a command line option.
     * 
     * @param _optionName The name of the option.
     * 
     * @note This function can unregister the default options.
     */
    static void UnregisterOption(const std::string& _optionName);

    /**
     * @brief Unregister all command line options.
     * 
     * @note This function will unregister the default options.
	 */
    static void UnregisterAllOptions();

   public:
    /**
     * @brief Check if the execution was aborted.
     * 
     * @return bool True if the execution was aborted, false otherwise.
	 */
    NODISCARD static inline bool ExecutionAborted() noexcept { return m_abort; }

    /**
     * @brief Get the command line arguments.
     * 
     * @return The command line arguments.
     * 
     * @note The first argument is the first option and not the executable name.
     */
    NODISCARD static inline const std::vector<std::string>& GetArgv() noexcept { return m_args; }

    /**
     * @brief Get the number of command line arguments.
     * 
     * @return uint8_t The number of command line arguments.
     * 
     * @note The executable name does not count as an argument.
     */
    NODISCARD static inline uint8_t GetArgc() noexcept { return m_args.size(); }

    /**
     * @brief Get the executable name.
     * 
     * @return const std::string& The executable name.
	 */
    NODISCARD static inline const std::string& GetExecutableName() noexcept { return m_executableName; }

    /**
     * @brief Get the executable path.
     * 
     * @return The executable path.
     */
    NODISCARD static inline const std::string& GetExecutablePath() noexcept { return m_executablePath; }
};

}  // namespace Rake::core
