project "premake"
kind "Utility"

targetdir("%{wks.location}/bin/" .. OutDir .. "")
objdir("%{wks.location}/obj/" .. IntDir .. "")

files {
	"%{wks.location}/**premake5.lua"
}