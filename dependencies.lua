VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}

IncludeDir["GLEW"] = "%{wks.location}/Engine/thirdparties/GLEW/include"
IncludeDir["mathfu"] = "%{wks.location}/Engine/thirdparties/mathfu"
IncludeDir["json"] = "%{wks.location}/thirdparties/json/single_include"
IncludeDir["spdlog"] = "%{wks.location}/Engine/thirdparties/spdlog/include"
IncludeDir["imgui"] = "%{wks.location}/Engine/thirdparties/imgui"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}

LibraryDir["GLEW"] = "%{wks.location}/Engine/thirdparties/GLEW/lib/Release/x64"
LibraryDir["imgui"] = "%{wks.location}/Engine/thirdparties/imgui/bin/Release-windows-x86_64"
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/lib"

Library = {}

Library["GLEW"] = "%{wks.location}/Engine/thirdparties/GLEW/lib/Release/x64/glew32.lib"
Library["imgui"] = "%{wks.location}/Engine/thirdparties/imgui/bin/Release-windows-x86_64/ImGui.lib"
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"