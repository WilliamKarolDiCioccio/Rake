#pragma once

#include <signal.h>

#include "application/application.hpp"
#include "core/command_line_parser.hpp"

extern std::unique_ptr<Rake::application::Application> RkCreateApplication() noexcept;

std::unique_ptr<Rake::application::Application> g_app = nullptr;

void RegisterOptions() {
    Rake::core::CommandLineParser::RegisterOption("--license", false, true, [](const char* _arg) {
        std::wcout << Rake::core::ReadFile(L"LICENSE.txt") << std::endl;
        return true;
    });

    Rake::core::CommandLineParser::RegisterOption("--readme", false, true, [](const char* _arg) {
        std::wcout << Rake::core::ReadFile(L"README.txt") << std::endl;
        return true;
    });

    Rake::core::CommandLineParser::RegisterOption("--python-ffi", true, false, [](const char* _arg) {
        return Rake::engine::scripting::PythonFFISystem::ParseOptionArguments(_arg);
    });

    Rake::core::CommandLineParser::RegisterOption("--renderer", true, false, [](const char* _arg) {
        return Rake::engine::graphics::RendererSystem::ParseOptionArguments(_arg);
    });
}

bool RkMain(int _argc = 1, const char* _argv[] = nullptr) {
    RegisterOptions();

    Rake::core::CommandLineParser::ParseOptions(_argc, _argv);

    g_app = RkCreateApplication();

    const auto singalHandler = [](int _signal) {
        g_app->Stop();
        exit(_signal);
    };

    signal(SIGINT, singalHandler);

    g_app->Start();
    g_app->Update();

    return true;
}
