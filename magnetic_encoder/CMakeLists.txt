#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for magnetic_encoder device source files                 #
#                                                                              #
#------------------------------------------------------------------------------#
add_library(magnetic_encoder_lib STATIC
    ${CMAKE_CURRENT_LIST_DIR}/magnetic_encoder.c
)

target_include_directories(magnetic_encoder_lib PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(magnetic_encoder_lib PUBLIC
    hal_config_lib
)
