project "Runtime"
kind "SharedLib"
language "C++"
cppdialect "C++20"
staticruntime "Off"
warnings "High"

postbuildcommands {
    "python ../../scripts/generate_metadata.py"
}

filter {"action:vs*", "configurations:Debug or Release"}
buildmessage "Generating metadata.hpp"
buildcommands {""}

targetdir(OutDir)
objdir(IntDir)

pchheader "pch.hpp"
pchsource "src/pch.cpp"

files {
    "./**.h",
    "./**.hpp",
    "./**.c",
    "./**.cpp",
    "./**.inl"
}

defines {
    "PLAYER_EXPORT",
    "_CRT_SECURE_NO_WARNINGS",
    "_SILENCE_CXX_17_CODECVT_HEADER_DEPRECATION_WARNING",
    "VK_NO_PROTOTYPES"
}

filter "system:Windows"
defines {
    "WIN32_LEAN_AND_MEAN",
    "NOMINMAX",
    "VK_USE_PLATFORM_WIN32_KHR",
    "_GAMING_DESKTOP",
    "WINAPI_FAMILY=WINAPI_FAMILY_DESKTOP_APP"
}

includedirs {
    "./include",
    "./include/RKRuntime",
    "../STL/include",
    "%{IncludeDir.entt}",
    "%{IncludeDir.GameDK}",
    "%{IncludeDir.GameDKExtensions}",
    "%{IncludeDir.json}",
    "%{IncludeDir.PythonSDK}",
    "%{IncludeDir.stb}",
    "%{IncludeDir.tinygltf}",
    "%{IncludeDir.tinyobjloader}",
    "%{IncludeDir.VulkanSDK}"
}

libdirs {
    "%{LibraryDir.GameDK}",
    "%{LibraryDir.GameDKExtensions}",
    "%{LibraryDir.PythonSDK}"
}

links {
    "STL",
    "%{Library.GameDK}",
    "%{Library.GameDKInput}",
    "%{Library.GameDKExtensions}",
    "%{Library.Python}"
}

filter "system:windows"
pic "On"

filter "configurations:Release"
flags {
    "NoIncrementalLink"
}
