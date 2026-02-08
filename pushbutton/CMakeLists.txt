#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for pushbutton device source files                       #
#                                                                              #
#------------------------------------------------------------------------------#
add_library(pushbutton_lib STATIC
    ${CMAKE_CURRENT_LIST_DIR}/pushbutton.c
)

target_include_directories(pushbutton_lib PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(pushbutton_lib PUBLIC
    hal_at32uc3l0256_config_lib
)
