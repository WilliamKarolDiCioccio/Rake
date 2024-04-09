project "Runtime"
kind "SharedLib"
language "C++"
cppdialect "C++20"
staticruntime "Off"
warnings "High"

prebuildcommands {
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
    "_SILENCE_CXX_17_CODECVT_HEADER_DEPRECATION_WARNING"
}

includedirs {
    "./include",
    "./include/RKRuntime",
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

filter "system:windows"
pic "On"

filter "configurations:Release"
flags {
    "NoIncrementalLink"
}
