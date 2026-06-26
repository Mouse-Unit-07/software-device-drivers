#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for led device source files                              #
#                                                                              #
#------------------------------------------------------------------------------#
add_library(led_lib STATIC
    ${CMAKE_CURRENT_LIST_DIR}/led.c
)

target_include_directories(led_lib PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    $<TARGET_PROPERTY:hal_config_lib,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(led_lib PRIVATE
    hal_config_lib
)
