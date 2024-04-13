#pragma once

#include <signal.h>

#include "RKRuntime/application/application.hpp"
#include "RKRuntime/core/command_line_parser.hpp"

/**
 * @brief Creates the application instance. This function must be implemented by the user.
 */
extern std::unique_ptr<Rake::application::Application> RkCreateApplication() noexcept;

std::unique_ptr<Rake::application::Application> g_app = nullptr;

void RegisterOptions() {
    Rake::core::CommandLineParser::RegisterOption(
        "license",
        "Prints the license information.",
        "",
        Rake::core::CmdOptionValueTypes::None,
        true,
        [](const std::string& _arg) {
            std::wcout << Rake::core::ReadFile(L"LICENSE.txt") << std::endl;
            return true;
        });

    Rake::core::CommandLineParser::RegisterOption(
        "readme",
        "Prints the readme information.",
        "",
        Rake::core::CmdOptionValueTypes::None,
        true,
        [](const std::string& _arg) {
            std::wcout << Rake::core::ReadFile(L"README.txt") << std::endl;
            return true;
        });

    Rake::core::CommandLineParser::RegisterOption(
        "python-ffi",
        "Python FFI options.",
        "",
        Rake::core::CmdOptionValueTypes::Multiple,
        false,
        [](const std::string& _arg) { return Rake::engine::scripting::PythonFFISystem::ParseOptionArguments(_arg); });

    Rake::core::CommandLineParser::RegisterOption(
        "renderer",
        "Renderer options.",
        "",
        Rake::core::CmdOptionValueTypes::Multiple,
        false,
        [](const std::string& _arg) { return Rake::engine::graphics::RendererSystem::ParseOptionArguments(_arg); });
}

/**
 * @brief Main function for the Rake engine.
 * 
 * @param _argc The number of arguments. Must be passed from the main function.
 * @param _argv The arguments. Must be passed from the main function.
 * @return bool Returns true if the engine was successfully executed.
 */
bool RkMain(int _argc = 1, const char* _argv[] = nullptr) {
    RegisterOptions();

    Rake::core::CommandLineParser::ParseCommandLine(_argc, _argv);

    if (Rake::core::CommandLineParser::ExecutionAborted()) return true;

    g_app = RkCreateApplication();

    const auto singalHandler = [](int _signal) {
        g_app->Stop();
        exit(_signal);
    };

    signal(SIGINT, singalHandler);
    signal(SIGTERM, singalHandler);

    g_app->Start();
    g_app->Update();

    return true;
}
