project "Testbed"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"
    warnings "High"
    dpiawareness "HighPerMonitor"

targetdir("%{wks.location}/bin/" .. OutDir .. "")
objdir("%{wks.location}/obj/" .. IntDir .. "")

files {
    "./**.h",
    "./**.hpp",
    "./**.c",
    "./**.cpp",
    ".natvis"
}

includedirs {
    "./src",
    "../Engine/RkPlayer/src",
    "%{IncludeDir.RkSTL}",
    "%{IncludeDir.Boost}",
    "%{IncludeDir.VulkanSDK}",
    "%{IncludeDir.imgui}",
    "%{IncludeDir.json}"
}

links {
    "RkPlayer"
}