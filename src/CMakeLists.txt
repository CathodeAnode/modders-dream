add_subdirectory(renderer)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
    PARENT_SCOPE
)

set(MODULES
    ${MODULES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Math.cppm
    ${CMAKE_CURRENT_SOURCE_DIR}/FixedString.cppm
    ${CMAKE_CURRENT_SOURCE_DIR}/Mustache.cppm
    ${CMAKE_CURRENT_SOURCE_DIR}/Settings.cppm
    ${CMAKE_CURRENT_SOURCE_DIR}/Logger.cppm
    ${CMAKE_CURRENT_SOURCE_DIR}/Error.cppm
    ${CMAKE_CURRENT_SOURCE_DIR}/Glfw.cppm
    ${CMAKE_CURRENT_SOURCE_DIR}/ZStringView.cppm
    PARENT_SCOPE
)
