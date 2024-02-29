include "dependencies.lua"

solution "Rake"
architecture "x86_64"
startproject "Testbed"
characterset "Unicode"

OutDir = "%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IntDir = "%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/int"

solutionPath = "./"

configurations {
    "Debug",
    "Development",
    "Release"
}

flags "MultiProcessorCompile"

filter "system:Windows"
toolset "msc"

filter "configurations:Debug"
symbols "on"
defines "RK_DEBUG"

filter "configurations:Development"
symbols "On"
optimize "Speed"
defines "RK_DEV"

filter "configurations:Release"
symbols "Off"
optimize "Speed"
defines "RK_RELEASE"

include "./Engine/STL"
include "./Engine/Runtime"
include "./Engine/tests"
include "./Testbed"
include "./thirdparties/imgui"
