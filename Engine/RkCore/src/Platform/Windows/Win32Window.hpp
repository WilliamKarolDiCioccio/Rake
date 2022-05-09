/*****************************************************************/ /**
 * \file   WindowsWindow.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Common.h"

#if defined(PLATFORM_WINDOWS)

#include "GUI/Desktop/Window.hpp"

namespace Rake::GUI
{

class Win32Window final : public Window
{
  public:
    Win32Window();
    ~Win32Window();

  public:
    void Refresh() override;
    void MakeCurrent() override;

  public:
    void MinimizeWindow() override;
    void MaximizeWindow() override;
    void FullscreenWindow() override;
    void ShouldShow(const B8 _shouldShow) override;
    void SetIcon(const char *&_iconPath) override;
    void SetTitle(const char *&_title) override;

  private:
    void *m_handle = nullptr;
};

} // namespace Rake::GUI

#endif
