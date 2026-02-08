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
)

target_link_libraries(wheel_motor_lib PUBLIC
    hal_at32uc3l0256_config_lib
)
