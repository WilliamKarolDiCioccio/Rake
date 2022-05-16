project "RkPlayer"
kind "SharedLib"
language "C++"
cppdialect "C++20"
staticruntime "Off"
floatingpoint "Fast"
warnings "High"

targetdir("%{wks.location}/bin/" .. OutDir .. "")
objdir("%{wks.location}/obj/" .. IntDir .. "")

pchheader "RkPch.hpp"
pchsource "RkPch.cpp"

files {
    "./**.h",
    "./**.hpp",
    "./**.c",
    "./**.cpp"
}

defines {
    "PLAYER_EXPORT"
}

includedirs {
    "../RkPlayer",
    "../RkPlayer/src",
    "../../RkBase/include",
    -- "%{IncludeDir.GLEW}",
    "%{IncludeDir.spdlog}",
    "%{IncludeDir.json}",
    "%{IncludeDir.VulkanSDK}"
}

libdirs {
    -- "%{LibraryDir.GLEW}"
    "%{LibraryDir.VulkanSDK}"
}

links {
    -- "%{Library.GLEW}"
    "%{Library.Vulkan}"
}
