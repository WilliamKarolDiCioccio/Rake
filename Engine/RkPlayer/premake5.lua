project "RkPlayer"
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
    "./**.c",
    "./**.cpp"
}

defines {
    "PLAYER_EXPORT"
}

includedirs {
    "../RkCore",
    "../RkCore/src",
    "../../RkBase/include",
    "%{IncludeDir.GLEW}",
    "%{IncludeDir.spdlog}",
    "%{IncludeDir.json}"
}

libdirs {
    "%{LibraryDir.GLEW}"
}

links {
    "%{Library.GLEW}"
}
