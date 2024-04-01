﻿#pragma once

#include <signal.h>

#include "application/application.hpp"
#include "core/command_line_parser.hpp"

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
