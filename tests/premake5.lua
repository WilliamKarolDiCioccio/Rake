project "tests"
kind "ConsoleApp"
language "C++"
cppdialect "C++17"
staticruntime "Off"
links "RkPlayer"
warnings "Off"

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
    "../tests",
    "../tests/src",
    "../Engine/RkPlayer/src",
    "../Engine/RkPlayer/include"
}

filter "system:Windows"
nuget "gtest:1.7.0"
