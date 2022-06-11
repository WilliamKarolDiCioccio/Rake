#include <Core/EntryPoint.h>

using namespace Rake::Core;

namespace Testbed
{

class TestbedApp final : public APP_FRAMEWORK
{
  public:
    TestbedApp(AppInfo _info) : Rake::Core::AppFramework(std::forward<AppInfo>(_info)){};

  private:
    void OnStart() override{};
    void OnResume() override{};
    void OnUpdate() override{};
    void OnPause() override{};
    void OnStop() override{};
};

} // namespace Testbed

AppInfo myAppInfo = {IS_CHEAT_MODE, L"Testbed", NULL, NULL};

AppFramework *RkCreateApplication()
{
    return new Testbed::TestbedApp(myAppInfo);
}
