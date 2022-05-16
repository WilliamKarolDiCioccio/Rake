#include "Core/EntryPoint.h"
#include "Core/RkApplication/AppFramework.hpp"

namespace Testbed
{

template <typename... Args> class TestbedApplication final : public Rake::Core::AppFramework
{
  public:
    TestbedApplication(Args... args) : Rake::Core::AppFramework(std::forward<Args>(args)...){};

  private:
    void OnStart() override{};
    void OnResume() override{};
    void OnUpdate() override{};
    void OnPause() override{};
    void OnStop() override{};
};

} // namespace Testbed

Rake::Core::AppFramework *RkCreateApplication(const char *_appName, Rake::Core::ApplicationMode _mode)
{
    return new Testbed::TestbedApplication(_appName, _mode);
}
