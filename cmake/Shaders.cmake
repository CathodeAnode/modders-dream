include_guard(GLOBAL)

# This directory is reserved for generated shader binaries and depfiles.
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "Shader compilation requires an out-of-source build.")
endif()

add_custom_target(shaders
    COMMAND "${CMAKE_COMMAND}"
        "-DOUTPUT_ROOT=${PROJECT_BINARY_DIR}/shaders"
        "-DMANIFEST=${PROJECT_BINARY_DIR}/CMakeFiles/shader-outputs.txt"
        -P "${CMAKE_CURRENT_LIST_DIR}/PruneShaders.cmake"
    COMMENT "Removing stale compiled shaders"
    VERBATIM
)
set_property(TARGET shaders PROPERTY SHADER_MANIFEST
    "${PROJECT_BINARY_DIR}/CMakeFiles/shader-outputs.txt")

function(_write_shader_manifest)
    get_property(EXPECTED TARGET shaders PROPERTY SHADER_OUTPUTS)
    get_property(MANIFEST TARGET shaders PROPERTY SHADER_MANIFEST)
    string(REPLACE ";" "\n" CONTENT "${EXPECTED}")
    file(CONFIGURE OUTPUT "${MANIFEST}" CONTENT "${CONTENT}" @ONLY)
endfunction()

# Include all registrations, even when there are no shaders left.
cmake_language(DEFER DIRECTORY "${PROJECT_SOURCE_DIR}" CALL _write_shader_manifest)

# Register one source; Slang discovers its [shader(...)] entry points.
function(add_slang_shader SOURCE)
    if(NOT ARGC EQUAL 1)
        message(FATAL_ERROR "Usage: add_slang_shader(path/relative/to/shaders.slang)")
    endif()
    find_program(SLANGC_EXECUTABLE NAMES slangc REQUIRED)

    if(CMAKE_SYSTEM_NAME STREQUAL "Windows") # Use dxil for DirectX12 on Windows
        set(SHADER_TARGET dxil)
        set(SHADER_EXTENSION dxil)
        set(SHADER_FLAGS -profile sm_6_0)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin") # Use metallib for Metal on MacOS
        set(SHADER_TARGET metallib)
        set(SHADER_EXTENSION metallib)
        set(SHADER_FLAGS)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux") # Use spir-v for Vulkan
        set(SHADER_TARGET spirv)
        set(SHADER_EXTENSION spv)
        set(SHADER_FLAGS)
    else()
        message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
    endif()

    set(SOURCE_ROOT "${PROJECT_SOURCE_DIR}/shaders")
    set(OUTPUT_ROOT "${PROJECT_BINARY_DIR}/shaders")
    if(IS_ABSOLUTE "${SOURCE}" OR SOURCE MATCHES "(^|/)\\.\\.(/|$)")
        message(FATAL_ERROR "Shader source must be relative to shaders/: ${SOURCE}")
    endif()
    set(SOURCE_ABSOLUTE "${SOURCE_ROOT}/${SOURCE}")

    get_property(WATCHING TARGET shaders PROPERTY SHADER_WATCHING)
    if(NOT WATCHING)
        file(GLOB_RECURSE SHADER_INPUTS CONFIGURE_DEPENDS LIST_DIRECTORIES false
            "${SOURCE_ROOT}/*"
        )
        set_property(DIRECTORY "${PROJECT_SOURCE_DIR}" APPEND PROPERTY
            CMAKE_CONFIGURE_DEPENDS ${SHADER_INPUTS} "${SLANGC_EXECUTABLE}"
        )
        set_property(TARGET shaders PROPERTY SHADER_WATCHING TRUE)
    endif()

    string(SHA256 SOURCE_ID "${SOURCE_ABSOLUTE}")
    set(REFLECTION_DIRECTORY "${PROJECT_BINARY_DIR}/CMakeFiles/shader-reflection")
    set(REFLECTION_FILE "${REFLECTION_DIRECTORY}/${SOURCE_ID}.json")
    file(MAKE_DIRECTORY "${REFLECTION_DIRECTORY}")
    execute_process(
        COMMAND "${SLANGC_EXECUTABLE}" "${SOURCE_ABSOLUTE}"
        -target "${SHADER_TARGET}" ${SHADER_FLAGS}
        -I "${SOURCE_ROOT}"
        -no-codegen -reflection-json "${REFLECTION_FILE}"
        RESULT_VARIABLE REFLECTION_RESULT
        OUTPUT_VARIABLE REFLECTION_STDOUT
        ERROR_VARIABLE REFLECTION_STDERR
    )
    if(NOT REFLECTION_RESULT STREQUAL "0")
        message(FATAL_ERROR
            "Slang entry-point discovery failed for ${SOURCE}:\n"
            "${REFLECTION_STDOUT}${REFLECTION_STDERR}"
        )
    endif()
    file(READ "${REFLECTION_FILE}" REFLECTION)
    string(JSON ENTRY_COUNT ERROR_VARIABLE REFLECTION_ERROR
        LENGTH "${REFLECTION}" entryPoints)
    # Slang omits the array entirely when the file has no entry points.
    if(REFLECTION_ERROR STREQUAL "member 'entryPoints' not found")
        set(ENTRY_COUNT 0)
    elseif(REFLECTION_ERROR)
        message(FATAL_ERROR "Invalid Slang reflection for ${SOURCE}: ${REFLECTION_ERROR}")
    endif()
    if(ENTRY_COUNT EQUAL 0)
        message(STATUS "No [shader(...)] entry points in ${SOURCE}")
        return()
    endif()

    # Preserve the source folder structure.
    get_filename_component(RELATIVE_DIRECTORY "${SOURCE}" DIRECTORY)
    get_filename_component(SOURCE_NAME "${SOURCE}" NAME_WLE)

    set(OUTPUT_DIRECTORY "${OUTPUT_ROOT}/${RELATIVE_DIRECTORY}")
    math(EXPR LAST_ENTRY "${ENTRY_COUNT} - 1")
    foreach(INDEX RANGE 0 ${LAST_ENTRY})
        string(JSON ENTRY GET "${REFLECTION}" entryPoints ${INDEX} name)
        string(JSON STAGE GET "${REFLECTION}" entryPoints ${INDEX} stage)
        if(NOT ENTRY MATCHES "^[A-Za-z_][A-Za-z0-9_]*$")
            message(FATAL_ERROR "Unsupported shader entry-point name: ${ENTRY}")
        endif()
        set(OUTPUT
            "${OUTPUT_DIRECTORY}/${SOURCE_NAME}.${ENTRY}.${SHADER_EXTENSION}"
        )
        cmake_path(NORMAL_PATH OUTPUT)
        set(DEPFILE "${OUTPUT}.d")
        set_property(TARGET shaders APPEND PROPERTY SHADER_OUTPUTS
            "${OUTPUT}" "${DEPFILE}"
        )

        add_custom_command(
            OUTPUT "${OUTPUT}"

            COMMAND "${CMAKE_COMMAND}" -E make_directory
            "${OUTPUT_DIRECTORY}"

            COMMAND "${SLANGC_EXECUTABLE}"
            "${SOURCE_ABSOLUTE}"
            -entry "${ENTRY}"
            -stage "${STAGE}"
            -target "${SHADER_TARGET}"
            ${SHADER_FLAGS}
            -I "${SOURCE_ROOT}"
            -depfile "${DEPFILE}"
            -o "${OUTPUT}"

            DEPENDS
            "${SOURCE_ABSOLUTE}"
            "${SLANGC_EXECUTABLE}"

            DEPFILE "${DEPFILE}"
            COMMENT "Compiling ${SOURCE} (${ENTRY}) for ${SHADER_TARGET}"
            VERBATIM
        )

        string(SHA256 TARGET_ID "${OUTPUT}")
        add_custom_target("shader_${TARGET_ID}" DEPENDS "${OUTPUT}")
        add_dependencies(shaders "shader_${TARGET_ID}")
    endforeach()
endfunction()
