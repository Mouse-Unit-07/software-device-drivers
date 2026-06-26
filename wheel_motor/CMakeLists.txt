#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for wheel_motor device source files                      #
#                                                                              #
#------------------------------------------------------------------------------#
add_library(wheel_motor_lib STATIC
    ${CMAKE_CURRENT_LIST_DIR}/wheel_motor.c
)

target_include_directories(wheel_motor_lib PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    $<TARGET_PROPERTY:hal_config_lib,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(wheel_motor_lib PRIVATE
    hal_config_lib
)
