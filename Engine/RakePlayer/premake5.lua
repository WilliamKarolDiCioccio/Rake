project "RakePlayer"
kind "SharedLib"
language "C++"
cppdialect "C++20"
staticruntime "Off"
floatingpoint "Fast"
warnings "Default"

targetdir("%{wks.location}/bin/" .. OutDir .. "")
objdir("%{wks.location}/obj/" .. IntDir .. "")

pchheader "RkPch.hpp"
pchsource "RkPch.cpp"

files {
    "./**.h",
    "./**.hpp",
    "./**.cpp",
    "./**.txt",
    "./**.lua",
    "./**.hint"
}

defines {
    "PLAYER_EXPORT"
}

includedirs {
    "../RakePlayer",
    "../RakePlayer/src",
    "../../RkBase/include",
    "%{IncludeDir.GLEW}",
    "%{IncludeDir.SDL2}",
    "%{IncludeDir.spdlog}",
    "%{IncludeDir.json}"
}

libdirs {
    "%{LibraryDir.GLEW}",
    "%{LibraryDir.SDL2}"
}

links {
    "%{Library.GLEW}",
    "%{Library.SDL2}"
}
