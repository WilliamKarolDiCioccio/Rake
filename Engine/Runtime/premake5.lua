project "Runtime"
kind "SharedLib"
language "C++"
cppdialect "C++20"
staticruntime "Off"
warnings "High"

targetdir(OutDir)
objdir(IntDir)

pchheader "pch.hpp"
pchsource "pch.cpp"

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
    "_SILENCE_CXX_17_CODECVT_HEADER_DEPRECATION_WARNING"
}

includedirs {
    "./include",
    "../STL/include",
    "%{IncludeDir.entt}",
    "%{IncludeDir.GameDK}",
    "%{IncludeDir.json}",
    "%{IncludeDir.PythonSDK}",
    "%{IncludeDir.stb}",
    "%{IncludeDir.tinygltf}",
    "%{IncludeDir.tinyobjloader}",
    "%{IncludeDir.VulkanSDK}"
}

libdirs {
    "%{LibraryDir.GameDK}",
    "%{LibraryDir.PythonSDK}"
}

links {
    "STL",
    "%{Library.GameInput}",
    "%{Library.Python}",
    "%{Library.XGameRuntime}"
}

pic "On"

prebuildcommands {
    "python ../../scripts/generate_metadata.py"
}

filter "system:windows"
filter {"action:vs*", "configurations:Debug or Release"}
buildmessage "Generating metadata.hpp"
buildcommands {""}

filter "configurations:Release"
flags {
    "NoIncrementalLink"
}
