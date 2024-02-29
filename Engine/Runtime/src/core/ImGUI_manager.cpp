#include "pch.hpp"

#include "core/ImGUI_manager.hpp"

namespace Rake::core {

void ImGUIManager::SetupIO() {
    ImGuiIO &io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    constexpr float fontSize = 22.f;

    io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/roboto_regular.ttf", fontSize);
}

void ImGUIManager::SetupTheme() {
    ImGui::StyleColorsDark();

    ImGuiStyle &style = ImGui::GetStyle();

    style.WindowRounding = 10.0f;
    style.ChildRounding = 5.0f;
    style.FrameRounding = 5.0f;
    style.GrabRounding = 0.0f;
    style.PopupRounding = 0.25f;
    style.ScrollbarRounding = 0.0f;

    ImVec4 *colors = ImGui::GetStyle().Colors;

    ImVec4 darkGrey = ImVec4(0.008f, 0.008f, 0.008f, 1.0f);  // Dark grey color

    colors[ImGuiCol_MenuBarBg] = darkGrey;  // Dark grey

    colors[ImGuiCol_WindowBg] = darkGrey;  // Dark grey

    colors[ImGuiCol_Header] = darkGrey;                               // Dark grey
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.2f, 0.0f, 0.0f, 1.0f);  // Red (hovered)
    colors[ImGuiCol_HeaderActive] = ImVec4(0.3f, 0.0f, 0.0f, 1.0f);   // Red (pressed)

    colors[ImGuiCol_Button] = darkGrey;                               // Dark grey
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.2f, 0.0f, 0.0f, 1.0f);  // Red (hovered)
    colors[ImGuiCol_ButtonActive] = ImVec4(0.3f, 0.0f, 0.0f, 1.0f);   // Red (pressed)

    colors[ImGuiCol_FrameBg] = darkGrey;                               // Dark grey
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.2f, 0.0f, 0.0f, 1.0f);  // Red (hovered)
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.3f, 0.0f, 0.0f, 1.0f);   // Red (pressed)

    colors[ImGuiCol_Tab] = darkGrey;                               // Dark grey
    colors[ImGuiCol_TabHovered] = ImVec4(0.5f, 0.0f, 0.0f, 1.0f);  // Red (hovered)
    colors[ImGuiCol_TabActive] = ImVec4(0.3f, 0.0f, 0.0f, 1.0f);   // Red (active)
    colors[ImGuiCol_TabUnfocused] = darkGrey;                      // Dark grey (unfocused)
    colors[ImGuiCol_TabUnfocusedActive] = darkGrey;                // Dark grey (unfocused, active)

    colors[ImGuiCol_TitleBg] = darkGrey;           // Dark grey
    colors[ImGuiCol_TitleBgActive] = darkGrey;     // Dark grey (active)
    colors[ImGuiCol_TitleBgCollapsed] = darkGrey;  // Dark grey (collapsed)
}

}  // namespace Rake::core
