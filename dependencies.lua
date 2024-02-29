GAME_DK = os.getenv("GameDK")
KTX_SOFTWARE = os.getenv("KTX_SOFTWARE")
PYTHON_SDK = os.getenv("PYTHON_SDK")
VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["entt"] = "%{wks.location}/thirdparties/entt/single_include"
IncludeDir["GameDK"] = "%{GAME_DK}/230603/GRDK/GameKit/Include"
IncludeDir["imgui"] = "%{wks.location}/thirdparties/imgui"
IncludeDir["json"] = "%{wks.location}/thirdparties/json/single_include"
IncludeDir["KtxSoftware"] = "%{KTX_SOFTWARE}/include"
IncludeDir["PythonSDK"] = "%{PYTHON_SDK}/include"
IncludeDir["stb"] = "%{wks.location}/thirdparties/stb"
IncludeDir["tinygltf"] = "%{wks.location}/thirdparties/tinygltf"
IncludeDir["tinyobjloader"] = "%{wks.location}/thirdparties/tinyobjloader"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}
LibraryDir["GameDK"] = "%{GAME_DK}/230603/GRDK/GameKit/Lib/amd64"
LibraryDir["imgui"] = "%{wks.location}/bin/Release-%{cfg.system}-%{cfg.architecture}"
LibraryDir["KtxSoftware"] = "%{KTX_SOFTWARE}/lib"
IncludeDir["PythonSDK"] = "%{PYTHON_SDK}/libs"
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/lib"

Library = {}
Library["GameInput"] = "%{GAME_DK}/230603/GRDK/GameKit/Lib/amd64/GameInput.lib"
Library["imgui"] = "%{wks.location}/bin/Release-%{cfg.system}-%{cfg.architecture}/imgui.lib"
Library["KtxSoftware"] = "%{KTX_SOFTWARE}/lib/ktx.lib"
IncludeDir["Python"] = "%{PYTHON_SDK}/libs/python312.lib"
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["XGameRuntime"] = "%{GAME_DK}/230603/GRDK/GameKit/Lib/amd64/xgameruntime.lib"
