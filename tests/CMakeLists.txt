set(PROJECT_NAME tests)

set(Sources
    "src/Test.cpp"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Sources}
)

add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE tests)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG       "tests"
    TARGET_NAME_DEVELOPMENT "tests"
    TARGET_NAME_RELEASE     "tests"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG       "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Debug-windows-x86_64/"
    OUTPUT_DIRECTORY_DEVELOPMENT "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Development-windows-x86_64/"
    OUTPUT_DIRECTORY_RELEASE     "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Release-windows-x86_64/"
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
    "${CMAKE_CURRENT_SOURCE_DIR}/../RkBase/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../Documenti/Visual Studio 2022/Libraries/googletest/googletest/include"
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
        /w;
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
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
        /SUBSYSTEM:CONSOLE
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    RkPlayer
)
