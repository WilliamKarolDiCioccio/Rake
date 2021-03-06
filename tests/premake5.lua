project "tests"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
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
    "./src",
    "../Engine/RkPlayer/src",
    "%{IncludeDir.Boost}"
}

filter "system:Windows"
nuget "gtest:1.7.0"
