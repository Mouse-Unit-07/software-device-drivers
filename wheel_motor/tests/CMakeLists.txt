#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for wheel_motor test files                               #
#                                                                              #
#------------------------------------------------------------------------------#
set(ALL_TEST_SOURCES
    ${ALL_TEST_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/test_wheel_motor.cpp
    ${CMAKE_SOURCE_DIR}/src/wheel_motor/wheel_motor.c
    ${CMAKE_SOURCE_DIR}/src/wheel_motor/wheel_motor.h
    PARENT_SCOPE
)

add_executable(test_wheel_motor
    ${CMAKE_CURRENT_SOURCE_DIR}/test_wheel_motor.cpp
    ${CMAKE_SOURCE_DIR}/cmake/tests/test_main.cpp
)

target_link_libraries(test_wheel_motor PRIVATE
    wheel_motor_lib
    CppUTest::CppUTest
    CppUTestExt
)

add_test(NAME test_wheel_motor COMMAND test_wheel_motor)
