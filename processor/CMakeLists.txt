#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for processor device source files                        #
#                                                                              #
#------------------------------------------------------------------------------#
add_library(processor_lib STATIC
    ${CMAKE_CURRENT_LIST_DIR}/processor.c
)

target_include_directories(processor_lib PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(processor_lib PUBLIC
    hal_config_lib
)
