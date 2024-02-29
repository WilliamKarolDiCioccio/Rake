#pragma once

#include <signal.h>

#include "application/application.hpp"

extern std::unique_ptr<Rake::application::Application> RkCreateApplication(int argc, const char *argv[]) noexcept;

static inline std::unique_ptr<Rake::application::Application> g_app = nullptr;

bool RkMain(int _argc = 1, const char *_argv[] = nullptr) {
    g_app = RkCreateApplication(_argc, _argv);

    const auto singalHandler = [](int _signal) {
        g_app->Stop();
        exit(_signal);
    };

    signal(SIGINT, singalHandler);

    g_app->Start();
    g_app->Update();

    return true;
}
