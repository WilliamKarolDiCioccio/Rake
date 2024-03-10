project "Testbed"
kind "ConsoleApp"
language "C++"
cppdialect "C++20"
staticruntime "Off"
warnings "High"
dpiawareness "HighPerMonitor"

targetdir(OutDir)
objdir(IntDir)

files {
    "./**.h",
    "./**.hpp",
    "./**.c",
    "./**.cpp"
}

includedirs {
    "./include",
    "../Engine/STL/include",
    "../Engine/Runtime/include",
    "%{IncludeDir.entt}",
    "%{IncludeDir.imgui}",
    "%{IncludeDir.json}"
}

libdirs {
    "%{LibraryDir.imgui}"
}

links {
    "Runtime",
    "%{Library.imgui}"
}
