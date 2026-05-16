#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for vacuum test files                                    #
#                                                                              #
#------------------------------------------------------------------------------#
set_property(GLOBAL APPEND PROPERTY
    ALL_TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_vacuum.cpp
    ${CMAKE_SOURCE_DIR}/src/vacuum/vacuum.c
    ${CMAKE_SOURCE_DIR}/src/vacuum/vacuum.h
)

add_executable(test_vacuum
    ${CMAKE_CURRENT_SOURCE_DIR}/test_vacuum.cpp
    ${CMAKE_SOURCE_DIR}/platforms/windows/test_main.cpp
)

target_link_libraries(test_vacuum PRIVATE
    vacuum_lib
    CppUTest::CppUTest
    CppUTestExt
)

add_test(NAME test_vacuum COMMAND test_vacuum)
