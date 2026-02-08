#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for vacuum device source files                           #
#                                                                              #
#------------------------------------------------------------------------------#
add_library(vacuum_lib STATIC
    ${CMAKE_CURRENT_LIST_DIR}/vacuum.c
)

target_include_directories(vacuum_lib PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(vacuum_lib PUBLIC
    hal_at32uc3l0256_config_lib
)
