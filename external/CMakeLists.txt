# Exclude third-party targets from the compilation database so clangd
# does not scan their implementation files for C++ modules.
set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)

# Disable compiler warnings for external libraries
# because they're very annoying
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")

add_subdirectory(bgfx.cmake)

set(SDL_SHARED OFF)
set(SDL_STATIC ON)
add_subdirectory(SDL)

# Reenable so that this repo's code recieves warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_BEFORE_EXTERNAL}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_BEFORE_EXTERNAL}")
