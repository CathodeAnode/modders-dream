set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    PARENT_SCOPE
)

set(MODULES
    ${MODULES}
    ${CMAKE_CURRENT_SOURCE_DIR}/math.cppm
    ${CMAKE_CURRENT_SOURCE_DIR}/logger.cppm
    ${CMAKE_CURRENT_SOURCE_DIR}/error.cppm
    ${CMAKE_CURRENT_SOURCE_DIR}/glfw.cppm
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer.cppm
    ${CMAKE_CURRENT_SOURCE_DIR}/color.cppm
    ${CMAKE_CURRENT_SOURCE_DIR}/zstring_view.cppm
    PARENT_SCOPE
)
