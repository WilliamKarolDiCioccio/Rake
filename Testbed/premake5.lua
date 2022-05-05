project "Testbed"
kind "WindowedApp"
language "C++"
cppdialect "C++20"
staticruntime "Off"
links "RakePlayer"
warnings "Default"

targetdir("%{wks.location}/bin/" .. OutDir .. "")
objdir("%{wks.location}/obj/" .. IntDir .. "")

files {
    "./**.h",
    "./**.cpp",
    "./**.txt",
    "./**.lua"
}

includedirs {
    "../Testbed",
    "../Testbed/src",
    "../Engine/RakePlayer/src",
    "../RkBase/include",
    "%{IncludeDir.GLEW}",
    "%{IncludeDir.SDL2}",
    "%{IncludeDir.spdlog}",
    "%{IncludeDir.json}"
}
