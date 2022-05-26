include "dependencies.lua"

solution "Rake"
architecture "x86_64"
startproject "Testbed"

OutDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IntDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

configurations {
    "Debug",
    "Development",
    "Release"
}

flags {
    "MultiProcessorCompile"
}

filter "system:Windows"
    atl "Dynamic"
    toolset "msc"
    defines {
        "_CRT_SECURE_NO_WARNINGS"
    }

filter "configurations:Debug"
    symbols "on"
    defines "RK_DEBUG"

filter "configurations:Development"
    symbols "On"
    defines "RK_DEV"

filter "configurations:Release"
    symbols "Off"
    optimize "Speed"
    defines "RK_RELEASE"

include "./Engine/RkPlayer"
include "./Testbed"
include "./tests"
include "./thirdparties/premake"
include "./Engine/thirdparties/imgui"