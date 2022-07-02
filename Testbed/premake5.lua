project "Testbed"
kind "WindowedApp"
language "C++"
cppdialect "C++20"
staticruntime "Off"
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
    "../RkSTL/include",
    "../Testbed",
    "../Testbed/src",
    "../Engine/RkPlayer/src",
    "../Engine/RkPlayer/include",
    "%{IncludeDir.SDL2}",
    "%{IncludeDir.spdlog}",
    "%{IncludeDir.json}",
}

links {
    "RkPlayer"
}