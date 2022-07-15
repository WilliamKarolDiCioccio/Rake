#include <EntryPoint.h>

using namespace Rake::Application;

namespace Testbed
{

class TestbedApp final : public APP_FRAMEWORK
{
  public:
    TestbedApp(AppData _appData) : APP_FRAMEWORK(std::forward<AppData>(_appData)){};

  private:
    void OnStart() override{};
    void OnResume() override{};
    void OnUpdate() override{};
    void OnPause() override{};
    void OnStop() override{};
};

} // namespace Testbed

AppFramework *RkCreateApplication()
{
    AppData appData = {IS_CHEAT_MODE, L"Testbed", "\0", "\0"};
    ParseCmdLineArgs(appData);

    return new Testbed::TestbedApp(appData);
}
