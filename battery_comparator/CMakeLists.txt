#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for battery_comparator device source files               #
#                                                                              #
#------------------------------------------------------------------------------#
add_library(battery_comparator_lib STATIC
    ${CMAKE_CURRENT_LIST_DIR}/battery_comparator.c
)

target_include_directories(battery_comparator_lib PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    $<TARGET_PROPERTY:hal_config_lib,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(battery_comparator_lib PRIVATE
    hal_config_lib
)
