#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for power_enabler test files                             #
#                                                                              #
#------------------------------------------------------------------------------#
set_property(GLOBAL APPEND PROPERTY
    ALL_TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_power_enabler.cpp
    ${CMAKE_SOURCE_DIR}/src/power_enabler/power_enabler.c
    ${CMAKE_SOURCE_DIR}/src/power_enabler/power_enabler.h
)

add_executable(test_power_enabler
    ${CMAKE_CURRENT_SOURCE_DIR}/test_power_enabler.cpp
    ${CMAKE_SOURCE_DIR}/platforms/windows/test_main.cpp
)

target_link_libraries(test_power_enabler PRIVATE
    power_enabler_lib
    CppUTest::CppUTest
    CppUTestExt
)

add_test(NAME test_power_enabler COMMAND test_power_enabler)
