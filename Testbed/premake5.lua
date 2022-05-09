project "Testbed"
kind "WindowedApp"
language "C++"
cppdialect "C++20"
staticruntime "Off"
links "RkCore"
warnings "Default"

targetdir("%{wks.location}/bin/" .. OutDir .. "")
objdir("%{wks.location}/obj/" .. IntDir .. "")

files {
    "./**.h",
    "./**.hpp",
    "./**.c",
    "./**.cpp"
}

includedirs {
    "../Testbed",
    "../Testbed/src",
    "../Engine/RkCore/src",
    "../RkBase/include",
    "%{IncludeDir.GLEW}",
    "%{IncludeDir.SDL2}",
    "%{IncludeDir.spdlog}",
    "%{IncludeDir.json}"
}
