set(PROJECT_NAME Testbed)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "CMakeLists.txt"
    "premake5.lua"
)
source_group("" FILES ${no_group_source_files})

set(src
    "src/Testbed.cpp"
)
source_group("src" FILES ${src})

set(ALL_FILES
    ${no_group_source_files}
    ${src}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Testbed)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG       "Testbed"
        TARGET_NAME_DEVELOPMENT "Testbed"
        TARGET_NAME_RELEASE     "Testbed"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG       "Testbed"
        TARGET_NAME_DEVELOPMENT "Testbed"
        TARGET_NAME_RELEASE     "Testbed"
    )
endif()
################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG       "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Debug-windows-x86_64/"
        OUTPUT_DIRECTORY_DEVELOPMENT "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Development-windows-x86_64/"
        OUTPUT_DIRECTORY_RELEASE     "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Release-windows-x86_64/"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG       "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Debug-windows-x86_64/"
        OUTPUT_DIRECTORY_DEVELOPMENT "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Development-windows-x86_64/"
        OUTPUT_DIRECTORY_RELEASE     "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Release-windows-x86_64/"
    )
endif()
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
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
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
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
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../Engine/RakePlayer/src;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../RkBase/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../Engine/thirdparties/GLEW/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../Engine/thirdparties/SDL2/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../Engine/thirdparties/spdlog/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../thirdparties/json/single_include"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../Engine/RakePlayer/src;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../RkBase/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../Engine/thirdparties/GLEW/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../Engine/thirdparties/SDL2/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../Engine/thirdparties/spdlog/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../thirdparties/json/single_include"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
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
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
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
        "UNICODE;"
        "_UNICODE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
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
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
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
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
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
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
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
endif()

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PRIVATE
    RakePlayer
)

