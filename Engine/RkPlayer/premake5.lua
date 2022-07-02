project "RkPlayer"
kind "SharedLib"
language "C++"
cppdialect "C++20"
staticruntime "Off"
floatingpoint "Fast"
warnings "High"

targetdir("%{wks.location}/bin/" .. OutDir .. "")
objdir("%{wks.location}/obj/" .. IntDir .. "")

pchheader "src/RkPch.h"
pchsource "src/RkPch.cpp"

files {
    "./**.h",
    "./**.hpp",
    "./**.c",
    "./**.cpp",
    "./.natvis"
}

defines {
    "PLAYER_EXPORT"
}

includedirs {
    "../../RkSTL/include",
    "../RkPlayer",
    "../RkPlayer/src",
    "%{IncludeDir.spdlog}",
    "%{IncludeDir.json}",
}

links {
    "d3dcompiler.lib"
}
