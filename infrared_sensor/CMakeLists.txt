#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for infrared_sensor device source files                  #
#                                                                              #
#------------------------------------------------------------------------------#
add_library(infrared_sensor_lib STATIC
    ${CMAKE_CURRENT_LIST_DIR}/infrared_sensor.c
)

target_include_directories(infrared_sensor_lib PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(infrared_sensor_lib PUBLIC
    hal_at32uc3l0256_config_lib
)
