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
    $<TARGET_PROPERTY:hal_config_lib,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(infrared_sensor_lib PRIVATE
    hal_config_lib
)
