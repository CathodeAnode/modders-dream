set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    PARENT_SCOPE
)

set(MODULES
    ${MODULES}
    ${CMAKE_CURRENT_SOURCE_DIR}/logger.cppm
    ${CMAKE_CURRENT_SOURCE_DIR}/fixed_string.cppm
    ${CMAKE_CURRENT_SOURCE_DIR}/zstring_view.cppm
    PARENT_SCOPE
)
