set(PROJECT_NAME RkPlayer)

set(no_group_source_files
    "RkPch.cpp"
    "RkPch.hpp"
)
source_group("" FILES ${no_group_source_files})

set(src
    "src/Common.h"
    "src/Version.h"
)
source_group("src" FILES ${src})

set(src__Containers
    "src/Containers/BinaryTree.hpp"
    "src/Containers/LinkedList.hpp"
)
source_group("src\\Containers" FILES ${src__Containers})

set(src__Core
    "src/Core/EngineConfig.h"
    "src/Core/EntryPoint.h"
)
source_group("src\\Core" FILES ${src__Core})

set(src__Core__Error
    "src/Core/Error/RkException.cpp"
    "src/Core/Error/RkException.hpp"
    "src/Core/Error/RkSignal.hpp"
)
source_group("src\\Core\\Error" FILES ${src__Core__Error})

set(src__Core__Event
    "src/Core/Event/AppEvent.inl.hpp"
    "src/Core/Event/EventBus.hpp"
    "src/Core/Event/RkEvent.inl.hpp"
)
source_group("src\\Core\\Event" FILES ${src__Core__Event})

set(src__Core__Pools
    "src/Core/Pools/MemoryPool.hpp"
    "src/Core/Pools/ThreadPool.hpp"
)
source_group("src\\Core\\Pools" FILES ${src__Core__Pools})

set(src__Core__RkApplication
    "src/Core/RkApplication/AppFramework.cpp"
    "src/Core/RkApplication/AppFramework.hpp"
)
source_group("src\\Core\\RkApplication" FILES ${src__Core__RkApplication})

set(src__Core__RkApplication__Layer__Load
    "src/Core/RkApplication/Layer/Load/ConfigLoader.cpp"
    "src/Core/RkApplication/Layer/Load/ConfigLoader.hpp"
)
source_group("src\\Core\\RkApplication\\Layer\\Load" FILES ${src__Core__RkApplication__Layer__Load})

set(src__Core__Time
    "src/Core/Time/AsyncTimer.cpp"
    "src/Core/Time/AsyncTimer.hpp"
    "src/Core/Time/SyncTimer.cpp"
    "src/Core/Time/SyncTimer.hpp"
)
source_group("src\\Core\\Time" FILES ${src__Core__Time})

set(src__Core__Tools
    "src/Core/Tools/Assert.inl.hpp"
    "src/Core/Tools/Console.inl.hpp"
    "src/Core/Tools/Log.inl.hpp"
)
source_group("src\\Core\\Tools" FILES ${src__Core__Tools})

set(src__Core__Utils
    "src/Core/Utils/RkString.hpp"
)
source_group("src\\Core\\Utils" FILES ${src__Core__Utils})

set(src__GUI__Desktop
    "src/GUI/Desktop/Window.cpp"
    "src/GUI/Desktop/Window.hpp"
)
source_group("src\\GUI\\Desktop" FILES ${src__GUI__Desktop})

set(src__Platform__Windows
    "src/Platform/Windows/Win32Window.cpp"
    "src/Platform/Windows/Win32Window.hpp"
)
source_group("src\\Platform\\Windows" FILES ${src__Platform__Windows})

set(src__Renderer
    "src/Renderer/Buffer.cpp"
    "src/Renderer/Buffer.hpp"
    "src/Renderer/ComputeContext.cpp"
    "src/Renderer/ComputeContext.hpp"
    "src/Renderer/Device.cpp"
    "src/Renderer/Device.hpp"
    "src/Renderer/GraphicsContext.cpp"
    "src/Renderer/GraphicsContext.hpp"
    "src/Renderer/Renderer.cpp"
    "src/Renderer/Renderer.hpp"
)
source_group("src\\Renderer" FILES ${src__Renderer})

set(ALL_FILES
    ${no_group_source_files}
    ${src}
    ${src__Containers}
    ${src__Core}
    ${src__Core__Error}
    ${src__Core__Event}
    ${src__Core__Pools}
    ${src__Core__RkApplication}
    ${src__Core__RkApplication__Layer__Load}
    ${src__Core__Time}
    ${src__Core__Tools}
    ${src__Core__Utils}
    ${src__GUI__Desktop}
    ${src__Platform__Windows}
    ${src__Renderer}
)

add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/RkPch.hpp>"
)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE RkPlayer)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG       "RkPlayer"
    TARGET_NAME_DEVELOPMENT "RkPlayer"
    TARGET_NAME_RELEASE     "RkPlayer"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG       "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/Debug-windows-x86_64/"
    OUTPUT_DIRECTORY_DEVELOPMENT "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/Development-windows-x86_64/"
    OUTPUT_DIRECTORY_RELEASE     "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/Release-windows-x86_64/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG       "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/Debug-windows-x86_64"
    ARCHIVE_OUTPUT_DIRECTORY_DEVELOPMENT "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/Development-windows-x86_64"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE     "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/Release-windows-x86_64"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_NAME_DEBUG       "RkPlayer"
    ARCHIVE_OUTPUT_NAME_DEVELOPMENT "RkPlayer"
    ARCHIVE_OUTPUT_NAME_RELEASE     "RkPlayer"
)

get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    $<$<CONFIG:Debug>:
        MultiThreadedDebugDLL
    >
    $<$<CONFIG:Development>:
        MultiThreadedDebugDLL
    >
    $<$<CONFIG:Release>:
        MultiThreadedDLL
    >
    $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Development>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/.;"
    "${CMAKE_CURRENT_SOURCE_DIR}/src;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../RkBase/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../thirdparties/GLEW/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../thirdparties/spdlog/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparties/json/single_include"
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "RK_DEBUG"
    ">"
    "$<$<CONFIG:Development>:"
        "RK_DEV"
    ">"
    "$<$<CONFIG:Release>:"
        "RK_RELEASE"
    ">"
    "_CRT_SECURE_NO_WARNINGS;"
    "PLAYER_EXPORT;"
    "UNICODE;"
    "_UNICODE"
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od;
            /ZI
        >
        $<$<CONFIG:Development>:
            /Od;
            /ZI
        >
        $<$<CONFIG:Release>:
            /O2;
            /Oi;
            /GF;
            /Gy;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        /MP;
        /std:c++latest;
        /Gm-;
        /W3;
        /fp:fast;
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /DEBUG;
            /INCREMENTAL
        >
        $<$<CONFIG:Development>:
            /DEBUG;
            /INCREMENTAL
        >
        $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        /SUBSYSTEM:WINDOWS
    )
endif()

set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "..\thirdparties\GLEW\lib\Release\x64\glew32"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../thirdparties/GLEW/lib/Release/x64"
)

