#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for wheel_motor test files                               #
#                                                                              #
#------------------------------------------------------------------------------#
set_property(GLOBAL APPEND PROPERTY
    ALL_TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_wheel_motor.cpp
    ${CMAKE_SOURCE_DIR}/src/wheel_motor/wheel_motor.c
    ${CMAKE_SOURCE_DIR}/src/wheel_motor/wheel_motor.h
)

add_executable(test_wheel_motor
    ${CMAKE_CURRENT_SOURCE_DIR}/test_wheel_motor.cpp
    ${CMAKE_SOURCE_DIR}/platforms/windows/test_main.cpp
)

target_link_libraries(test_wheel_motor PRIVATE
    wheel_motor_lib
    CppUTest::CppUTest
    CppUTestExt
)

add_test(NAME test_wheel_motor COMMAND test_wheel_motor)
