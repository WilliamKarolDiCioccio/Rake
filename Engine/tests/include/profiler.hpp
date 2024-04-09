#pragma once

#include <gtest/gtest.h>

#include <thread>
#include <vector>

#include <RKRuntime/tools/profiler.hpp>

TEST(ProfilerTest, NestedFunctionTest) {
    Rake::tools::Profiler::Initialize(L"NestedFunctionTestSession", L"./profiles");

    auto outerFunction = []() {
        Rake::tools::Profiler::BeginProfile(L"OuterFunction", Rake::tools::ProfileCategory::function);

        auto innerFunction = []() {
            Rake::tools::Profiler::BeginProfile(L"InnerFunction", Rake::tools::ProfileCategory::function);

            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            Rake::tools::Profiler::EndProfile();
        };

        innerFunction();

        Rake::tools::Profiler::EndProfile();
    };

    outerFunction();

    Rake::tools::Profiler::Shutdown();
}

TEST(ProfilerTest, ThreadSafetyTest) {
    Rake::tools::Profiler::Initialize(L"ThreadSafetyTestSession", L"./profiles");

    auto threadFunc = [](int _idx) {
        auto profileName = L"ThreadProfile" + std::to_wstring(_idx);

        Rake::tools::Profiler::BeginProfile(profileName, Rake::tools::ProfileCategory::function);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        Rake::tools::Profiler::EndProfile();
    };

    std::vector<std::thread> threads;

    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(threadFunc, i);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    Rake::tools::Profiler::Shutdown();
}
