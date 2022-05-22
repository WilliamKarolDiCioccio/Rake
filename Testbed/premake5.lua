project "Testbed"
kind "WindowedApp"
language "C++"
cppdialect "C++20"
staticruntime "Off"
links "RkPlayer"
warnings "High"

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
    "../Engine/RkPlayer/src",
    "../RkBase/include",
    -- "%{IncludeDir.GLEW}",
    "%{IncludeDir.SDL2}",
    "%{IncludeDir.spdlog}",
    "%{IncludeDir.json}",
    "%{IncludeDir.imgui}"
}