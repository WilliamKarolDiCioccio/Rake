cmake_policy(PUSH)
cmake_policy(SET CMP0054 NEW)
macro(prepare_commands)
    unset(TOKEN_ROLE)
    unset(COMMANDS)
    foreach(TOKEN ${ARG_COMMANDS})
        if("${TOKEN}" STREQUAL "COMMAND")
            set(TOKEN_ROLE "KEYWORD")
        elseif("${TOKEN_ROLE}" STREQUAL "KEYWORD")
            set(TOKEN_ROLE "CONDITION")
        elseif("${TOKEN_ROLE}" STREQUAL "CONDITION")
            set(TOKEN_ROLE "COMMAND")
        elseif("${TOKEN_ROLE}" STREQUAL "COMMAND")
            set(TOKEN_ROLE "ARG")
        endif()

        if("${TOKEN_ROLE}" STREQUAL "KEYWORD")
            list(APPEND COMMANDS "${TOKEN}")
        elseif("${TOKEN_ROLE}" STREQUAL "CONDITION")
            set(CONDITION ${TOKEN})
        elseif("${TOKEN_ROLE}" STREQUAL "COMMAND")
            list(APPEND COMMANDS "$<$<NOT:${CONDITION}>:${DUMMY}>$<${CONDITION}:${TOKEN}>")
        elseif("${TOKEN_ROLE}" STREQUAL "ARG")
            list(APPEND COMMANDS "$<${CONDITION}:${TOKEN}>")
        endif()
    endforeach()
endmacro()
cmake_policy(POP)

macro(prepare_output)
    unset(OUTPUT)
    foreach(TOKEN ${ARG_OUTPUT})
        if(IS_ABSOLUTE ${TOKEN})
            list(APPEND OUTPUT "${TOKEN}")
        else()
            list(APPEND OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/${TOKEN}")
        endif()
    endforeach()
endmacro()

function(add_custom_command_if_parse_arguments)
    cmake_parse_arguments("ARG" "PRE_BUILD;PRE_LINK;POST_BUILD" "TARGET;COMMENT" "DEPENDS;OUTPUT;COMMANDS" ${ARGN})

    if(WIN32)
        set(DUMMY "cd.")
    elseif(UNIX)
        set(DUMMY "true")
    endif()

    prepare_commands()
    prepare_output()

    set(DEPENDS "${ARG_DEPENDS}")
    set(COMMENT "${ARG_COMMENT}")
    set(PRE_BUILD "${ARG_PRE_BUILD}")
    set(PRE_LINK "${ARG_PRE_LINK}")
    set(POST_BUILD "${ARG_POST_BUILD}")
    set(TARGET "${ARG_TARGET}")
    if(PRE_BUILD)
        set(STEP "PRE_BUILD")
    elseif(PRE_LINK)
        set(STEP "PRE_LINK")
    elseif(POST_BUILD)
        set(STEP "POST_BUILD")
    endif()
    set(NAME "${TARGET}_${STEP}")

    set(OUTPUT "${OUTPUT}" PARENT_SCOPE)
    set(DEPENDS "${DEPENDS}" PARENT_SCOPE)
    set(COMMENT "${COMMENT}" PARENT_SCOPE)
    set(PRE_BUILD "${PRE_BUILD}" PARENT_SCOPE)
    set(PRE_LINK "${PRE_LINK}" PARENT_SCOPE)
    set(POST_BUILD "${POST_BUILD}" PARENT_SCOPE)
    set(TARGET "${TARGET}" PARENT_SCOPE)
    set(COMMANDS "${COMMANDS}" PARENT_SCOPE)
    set(STEP "${STEP}" PARENT_SCOPE)
    set(NAME "${NAME}" PARENT_SCOPE)
endfunction()

function(add_custom_command_if)
    add_custom_command_if_parse_arguments(${ARGN})

    if(OUTPUT AND TARGET)
        message(FATAL_ERROR  "Wrong syntax. A TARGET and OUTPUT can not both be specified.")
    endif()

    if(OUTPUT)
        add_custom_command(OUTPUT ${OUTPUT}
                           ${COMMANDS}
                           DEPENDS ${DEPENDS}
                           WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                           COMMENT ${COMMENT})
    elseif(TARGET)
        if(PRE_BUILD AND NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio")
            add_custom_target(
                ${NAME}
                ${COMMANDS}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMENT ${COMMENT})
            add_dependencies(${TARGET} ${NAME})
        else()
            add_custom_command(
                TARGET ${TARGET}
                ${STEP}
                ${COMMANDS}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMENT ${COMMENT})
        endif()
    else()
        message(FATAL_ERROR "Wrong syntax. A TARGET or OUTPUT must be specified.")
    endif()
endfunction()

macro(use_props TARGET CONFIGS PROPS_FILE)
    set(PROPS_TARGET "${TARGET}")
    foreach(PROPS_CONFIG ${CONFIGS})
        string(TOUPPER "${PROPS_CONFIG}" PROPS_CONFIG_U)

        get_filename_component(ABSOLUTE_PROPS_FILE "${PROPS_FILE}" ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
        if(EXISTS "${ABSOLUTE_PROPS_FILE}")
            include("${ABSOLUTE_PROPS_FILE}")
        else()
            message(WARNING "Corresponding cmake file from props \"${ABSOLUTE_PROPS_FILE}\" doesn't exist")
        endif()
    endforeach()
endmacro()

function(source_file_compile_options SOURCE_FILE)
    if("${ARGC}" LESS_EQUAL "1")
        return()
    endif()

    get_source_file_property(COMPILE_OPTIONS "${SOURCE_FILE}" COMPILE_OPTIONS)

    if(COMPILE_OPTIONS)
        list(APPEND COMPILE_OPTIONS ${ARGN})
    else()
        set(COMPILE_OPTIONS "${ARGN}")
    endif()

    set_source_files_properties("${SOURCE_FILE}" PROPERTIES COMPILE_OPTIONS "${COMPILE_OPTIONS}")
endfunction()

set(DEFAULT_CXX_PROPS "${CMAKE_CURRENT_LIST_DIR}/DefaultCXX.cmake")
set(DEFAULT_Fortran_PROPS "${CMAKE_CURRENT_LIST_DIR}/DefaultFortran.cmake")
