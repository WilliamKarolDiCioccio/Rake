project "tests"
kind "ConsoleApp"
language "C++"
cppdialect "C++20"
staticruntime "Off"

targetdir(OutDir)
objdir(IntDir)

files {
    "./**.hpp",
    "./**.cpp"
}

includedirs {
    "./include",
    "../STL/include",
    "../Runtime/include",
    "%{IncludeDir.ImGui}",
    "%{IncludeDir.json}",
    "%{IncludeDir.VulkanSDK}"
}

links {
    "STL",
    "Runtime"
}

filter "system:Windows"
nuget {
    "Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn:1.8.1.7"
}
