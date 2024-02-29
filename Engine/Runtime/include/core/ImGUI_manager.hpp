#pragma once

RK_DISABLE_WARNINGS
#include <imgui.h>
RK_RESTORE_WARNINGS

#include "base.hpp"

namespace Rake::core {

class ImGUIManager final {
   private:
    ImGUIManager() = default;

   public:
    static void SetupIO();
    static void SetupTheme();
};

}  // namespace Rake::core
