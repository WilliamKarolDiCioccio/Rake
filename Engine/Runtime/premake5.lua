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
    "%{IncludeDir.imgui}",
    "%{IncludeDir.json}",
    "%{IncludeDir.KtxSoftware}",
    "%{IncludeDir.libsodium}",
    "%{IncludeDir.PythonSDK}",
    "%{IncludeDir.stb}",
    "%{IncludeDir.tinygltf}",
    "%{IncludeDir.tinyobjloader}",
    "%{IncludeDir.VulkanSDK}"
}

libdirs {
    "%{LibraryDir.GameDK}",
    "%{LibraryDir.imgui}",
    "%{LibraryDir.KtxSoftware}",
    "%{LibraryDir.PythonSDK}"
}

links {
    "STL",
    "%{Library.GameInput}",
    "%{Library.imgui}",
    "%{Library.KtxSoftware}",
    "%{Library.libsodium}",
    "%{Library.Python}",
    "%{Library.XGameRuntime}"
}

filter "system:windows"
pic "On"

filter "configurations:Release"
flags {
    "NoIncrementalLink"
}
