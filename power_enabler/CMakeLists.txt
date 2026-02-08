#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for power_enabler device source files                    #
#                                                                              #
#------------------------------------------------------------------------------#
add_library(power_enabler_lib STATIC
    ${CMAKE_CURRENT_LIST_DIR}/power_enabler.c
)

target_include_directories(power_enabler_lib PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(power_enabler_lib PUBLIC
    hal_at32uc3l0256_config_lib
)
