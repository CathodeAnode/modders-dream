cmake_minimum_required(VERSION 4.4...4.4)

# This experimental API has a version-specific activation key.
if(CMAKE_VERSION VERSION_GREATER_EQUAL 4.5)
    message(FATAL_ERROR "Use CMake 4.4.x; review the import-std gate before upgrading.")
endif()
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

project(modders-dream VERSION 0.1.0 LANGUAGES CXX)

if(NOT 23 IN_LIST CMAKE_CXX_COMPILER_IMPORT_STD)
    message(FATAL_ERROR "The toolchain cannot import std. Install the standard library's module sources..")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/Shaders.cmake)
add_subdirectory(shaders)

add_subdirectory(external)

add_subdirectory(src)

add_executable(modders-dream
    ${SOURCES}
)

add_dependencies(modders-dream shaders)

target_sources(modders-dream
    PRIVATE
    FILE_SET modules TYPE CXX_MODULES
    FILES
    ${MODULES}
)

target_link_libraries(modders-dream PRIVATE
    Diligent-Common
    Diligent-GraphicsEngineVk-static
    glfw
)

target_include_directories(modders-dream PRIVATE
    ${CMAKE_SOURCE_DIR}/external/eigen
    ${CMAKE_SOURCE_DIR}/external/DiligentCore
)

set_target_properties(modders-dream PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    CXX_MODULE_STD YES
)

# For DiligentCore
if(WIN32)
    target_compile_definitions(modders-dream PRIVATE PLATFORM_WIN32=1)
elseif(APPLE)
    target_compile_definitions(modders-dream PRIVATE PLATFORM_MACOS=1)
elseif(UNIX)
    target_compile_definitions(modders-dream PRIVATE PLATFORM_LINUX=1)
endif()
