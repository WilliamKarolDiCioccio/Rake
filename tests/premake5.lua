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
    "../tests",
    "../tests/src",
    "../RkBase/include",
    "../Engine/RkPlayer/src"
}

filter "system:Windows"
nuget "Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn:1.8.1.6"
