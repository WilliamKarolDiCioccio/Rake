set(PROJECT_NAME premake)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "premake5.lua"
)
source_group("" FILES ${no_group_source_files})

set(..
    "../../premake5.lua"
)
source_group(".." FILES ${..})

set(..__Engine__RkPlayer
    "../../Engine/RkPlayer/premake5.lua"
)
source_group("..\\Engine\\RkPlayer" FILES ${..__Engine__RkPlayer})

set(..__Testbed
    "../../Testbed/premake5.lua"
)
source_group("..\\Testbed" FILES ${..__Testbed})

set(..__tests
    "../../tests/premake5.lua"
)
source_group("..\\tests" FILES ${..__tests})

set(ALL_FILES
    ${no_group_source_files}
    ${..}
    ${..__Engine__RkPlayer}
    ${..__Testbed}
    ${..__tests}
)

add_custom_target(${PROJECT_NAME} SOURCES ${ALL_FILES})

