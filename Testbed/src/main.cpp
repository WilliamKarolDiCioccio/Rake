#include <main.h>

#include "Testbed.hpp"

std::unique_ptr<Rake::application::Application> RkCreateApplication(int argc, const char *argv[]) noexcept {
    return std::make_unique<Testbed::Testbed>(argc, argv);
}

int main(int argc, const char *argv[]) {
    if (!RkMain(argc, argv)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
