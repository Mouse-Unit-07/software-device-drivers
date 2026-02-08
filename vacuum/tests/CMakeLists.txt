#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for vacuum test files                                    #
#                                                                              #
#------------------------------------------------------------------------------#
set(ALL_TEST_SOURCES
    ${ALL_TEST_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/test_vacuum.cpp
    ${CMAKE_SOURCE_DIR}/src/vacuum/vacuum.c
    ${CMAKE_SOURCE_DIR}/src/vacuum/vacuum.h
    PARENT_SCOPE
)

add_executable(test_vacuum
    ${CMAKE_CURRENT_SOURCE_DIR}/test_vacuum.cpp
    ${CMAKE_SOURCE_DIR}/cmake/tests/test_main.cpp
)

target_link_libraries(test_vacuum PRIVATE
    vacuum_lib
    CppUTest::CppUTest
    CppUTestExt
)

add_test(NAME test_vacuum COMMAND test_vacuum)
