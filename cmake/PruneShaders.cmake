cmake_minimum_required(VERSION 3.21)

# Called by shaders after all shader compilation succeeds.
# The output directory is reserved for generated shader binaries and depfiles.
if(NOT DEFINED OUTPUT_ROOT OR NOT IS_ABSOLUTE "${OUTPUT_ROOT}")
    message(FATAL_ERROR "Shader cleanup requires an absolute OUTPUT_ROOT.")
endif()
if(NOT DEFINED MANIFEST OR NOT EXISTS "${MANIFEST}")
    message(FATAL_ERROR "Shader output manifest is missing; reconfigure the project.")
endif()

file(STRINGS "${MANIFEST}" EXPECTED ENCODING UTF-8)
file(GLOB_RECURSE EXISTING LIST_DIRECTORIES false
    "${OUTPUT_ROOT}/*.spv"
    "${OUTPUT_ROOT}/*.dxil"
    "${OUTPUT_ROOT}/*.metallib"
    "${OUTPUT_ROOT}/*.spv.d"
    "${OUTPUT_ROOT}/*.dxil.d"
    "${OUTPUT_ROOT}/*.metallib.d"
)
foreach(FILE IN LISTS EXISTING)
    if(NOT FILE IN_LIST EXPECTED)
        message(STATUS "Removing stale shader file: ${FILE}")
        file(REMOVE "${FILE}")
    endif()
endforeach()
