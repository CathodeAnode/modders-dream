# Exclude third-party targets from the compilation database so clangd
# does not scan their implementation files for C++ modules.
set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)

add_subdirectory(bgfx.cmake)
