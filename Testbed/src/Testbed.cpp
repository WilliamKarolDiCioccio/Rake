#include <Main.h>
#include <Version.h>

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

std::unique_ptr<APP_FRAMEWORK> RkCreateApplication()
{
    AppData appData = {CHEAT_MODE, L"Testbed - Version 0.0.1 - Build 'Irrelevant'", "\0", "\0"};

    return std::make_unique<Testbed::TestbedApp>(appData);
}
