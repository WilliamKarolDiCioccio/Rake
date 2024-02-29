#include <iostream>
#include <gtest/gtest.h>

#include "profiler.hpp"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();

    std::cout << "\nPress Enter to exit...";
    std::cin.get();

    return result;
}
