project "tests"
kind "ConsoleApp"
language "C++"
cppdialect "C++20"
staticruntime "Off"
warnings "Off"

targetdir("%{wks.location}/bin/" .. OutDir .. "")
objdir("%{wks.location}/obj/" .. IntDir .. "")

nuget { "Microsoft.googletest.v140.windesktop.msvcstl.dyn.rt-dyn" }