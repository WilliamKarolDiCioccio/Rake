GAME_DK = os.getenv("GameDK")
PYTHON_SDK = os.getenv("PYTHON_SDK")
VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["entt"] = "%{wks.location}/thirdparties/entt/single_include"
IncludeDir["GameDK"] = "%{GAME_DK}\\240602\\GRDK\\GameKit\\Include"
IncludeDir["GameDKExtensions"] =
    "%{GAME_DK}\\240602\\GRDK\\ExtensionLibraries\\Xbox.Services.API.C\\DesignTime\\CommonConfiguration\\Neutral\\Include"
IncludeDir["json"] = "%{wks.location}/thirdparties/json/single_include"
IncludeDir["PythonSDK"] = "%{PYTHON_SDK}/include"
IncludeDir["stb"] = "%{wks.location}/thirdparties/stb"
IncludeDir["tinygltf"] = "%{wks.location}/thirdparties/tinygltf"
IncludeDir["tinyobjloader"] = "%{wks.location}/thirdparties/tinyobjloader"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}
LibraryDir["GameDK"] = "%{GAME_DK}\\240602\\GRDK\\GameKit\\Lib\\amd64"
LibraryDir["GameDKExtensions"] =
    "%{GAME_DK}\\240602\\GRDK\\ExtensionLibraries\\Xbox.Services.API.C\\DesignTime\\CommonConfiguration\\Neutral\\Lib\\Release"
IncludeDir["PythonSDK"] = "%{PYTHON_SDK}/libs"
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/lib"

Library = {}
Library["GameDK"] = "%{GAME_DK}\\240602\\GRDK\\GameKit\\Lib\\amd64\\xgameruntime.lib"
Library["GameDKInput"] = "%{GAME_DK}\\240602\\GRDK\\GameKit\\Lib\\amd64\\GameInput.lib"
Library["GameDKExtensions"] =
    "%{GAME_DK}\\240602\\GRDK\\ExtensionLibraries\\Xbox.Services.API.C\\DesignTime\\CommonConfiguration\\Neutral\\Lib\\Release\\Microsoft.Xbox.Services.GDK.C.Thunks.lib"
IncludeDir["Python"] = "%{PYTHON_SDK}/libs/python312.lib"
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
