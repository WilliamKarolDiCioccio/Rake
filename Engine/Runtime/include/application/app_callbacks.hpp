#pragma once

#include <functional>

namespace Rake::application {

class Callback {
   public:
    static inline std::function<void(void)> callback;

   public:
    virtual ~Callback() = default;

   public:
    static inline void Do() noexcept { return callback(); }
};

class StopCallback final : public Callback {
   public:
    ~StopCallback() override = default;
};

class PauseCallback final : public Callback {
   public:
    ~PauseCallback() override = default;
};

class ResumeCallback final : public Callback {
   public:
    static inline std::function<void(void)> callback;

    ~ResumeCallback() override = default;
};

}  // namespace Rake::application
