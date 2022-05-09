IncludeDir = {}

IncludeDir["GLEW"] = "%{wks.location}/Engine/thirdparties/GLEW/include"
IncludeDir["mathfu"] = "%{wks.location}/Engine/thirdparties/mathfu"
IncludeDir["json"] = "%{wks.location}/thirdparties/json/single_include"
IncludeDir["spdlog"] = "%{wks.location}/Engine/thirdparties/spdlog/include"
IncludeDir["googletests"] = "C:/Users/theyo/OneDrive/Documenti/Visual Studio 2022/Libraries/googletest/googletest/include"

LibraryDir = {}

LibraryDir["GLEW"] = "%{wks.location}/Engine/thirdparties/GLEW/lib/Release/x64"
LibraryDir["SDL2"] = "%{wks.location}/Engine/thirdparties/SDL2/lib/x64"

Library = {}

Library["GLEW"] = "%{wks.location}/Engine/thirdparties/GLEW/lib/Release/x64/glew32.lib"
