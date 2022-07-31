project "RkPlayer"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"
    warnings "High"
    dpiawareness "HighPerMonitor"

targetdir("%{wks.location}/bin/" .. OutDir .. "")
objdir("%{wks.location}/obj/" .. IntDir .. "")

pchheader "RkPch.h"
pchsource "RkPch.cpp"

files {
    "./**.h",
    "./**.hpp",
    "./**.c",
    "./**.cpp",
    ".natvis"
}

defines {
    "PLAYER_EXPORT"
}

includedirs {
    "./src", 
    "%{IncludeDir.Boost}",
    "%{IncludeDir.VulkanSDK}",
    "%{IncludeDir.imgui}",
    "%{IncludeDir.json}"
}

libdirs {
    "%{LibraryDir.imgui}",
    "%{LibraryDir.VulkanSDK}"
}

links {
    "%{Library.imgui}",
    "%{Library.Vulkan}"
}

filter "system:windows"
	pic "On"
    