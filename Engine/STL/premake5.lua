project "STL"
kind "StaticLib"
language "C++"
cppdialect "C++20"
staticruntime "Off"
warnings "High"

targetdir(OutDir)
objdir(IntDir)

files {
    "./**.h",
    "./**.hpp",
    "./**.c",
    "./**.cpp",
    "./**.inl"
}

includedirs {
    "./include"
}
