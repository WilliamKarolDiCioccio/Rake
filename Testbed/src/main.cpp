#include <RKRuntime/main.h>

#include "Testbed.hpp"

std::unique_ptr<Rake::application::Application> RkCreateApplication() noexcept {
    return std::make_unique<Testbed::Testbed>();
}

int main(int argc, const char *argv[]) {
    if (!RkMain(argc, argv)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
