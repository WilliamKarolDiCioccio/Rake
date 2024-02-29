#pragma once

#include <application/application.hpp>

using namespace Rake;

namespace Testbed {

class Testbed final : public application::Application {
   private:
    struct MenusState {};

    MenusState m_menusState = {};

   public:
    Testbed(int _argc, const char *_argv[]);
    ~Testbed() override;

   private:
    void OnStart() noexcept override;
    void OnResume() noexcept override{};
    void OnUpdate() noexcept override;
    void OnPause() noexcept override{};
    void OnStop() noexcept override;
    void OnImGuiRender(core::Window *_windowHandle) noexcept override;
};

}  // namespace Testbed
