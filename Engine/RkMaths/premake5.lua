project "RkMaths"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
    staticruntime "Off"
    floatingpoint "Fast"
    warnings "High"
    
targetdir("%{wks.location}/bin/" .. OutDir .. "")
objdir("%{wks.location}/obj/" .. IntDir .. "")

files {
    "./**.h",
    "./**.hpp",
    "./**.c",
    "./**.cpp"
}