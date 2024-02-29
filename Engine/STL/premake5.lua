project "STL"
kind "SharedItems"
language "C++"
cppdialect "C++20"
staticruntime "Off"

targetdir(OutDir)
objdir(IntDir)

files {
    "./**.hpp"
}
