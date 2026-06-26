#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for pushbutton device source files                       #
#                                                                              #
#------------------------------------------------------------------------------#

if(NOT DEFINED MOUSE_TARGET)
    message(FATAL_ERROR "MOUSE_TARGET not specified")
endif()

if(MOUSE_TARGET STREQUAL "rev_a")
    set(PUSHBUTTON_SOURCE
        ${CMAKE_CURRENT_LIST_DIR}/pushbutton_sw_debounce.c
    )
elseif(MOUSE_TARGET STREQUAL "rev_b")
    set(PUSHBUTTON_SOURCE
        ${CMAKE_CURRENT_LIST_DIR}/pushbutton_hw_debounce.c
    )
else()
    message(FATAL_ERROR "Unsupported MOUSE_TARGET: ${MOUSE_TARGET}")
endif()

add_library(pushbutton_lib STATIC
    ${PUSHBUTTON_SOURCE}
)

target_include_directories(pushbutton_lib PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    $<TARGET_PROPERTY:hal_config_lib,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(pushbutton_lib PRIVATE
    hal_config_lib
)
