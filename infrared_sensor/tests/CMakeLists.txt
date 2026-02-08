#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for infrared_sensor test files                           #
#                                                                              #
#------------------------------------------------------------------------------#
set(ALL_TEST_SOURCES
    ${ALL_TEST_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/test_infrared_sensor.cpp
    ${CMAKE_SOURCE_DIR}/src/infrared_sensor/infrared_sensor.c
    ${CMAKE_SOURCE_DIR}/src/infrared_sensor/infrared_sensor.h
    PARENT_SCOPE
)

add_executable(test_infrared_sensor
    ${CMAKE_CURRENT_SOURCE_DIR}/test_infrared_sensor.cpp
    ${CMAKE_SOURCE_DIR}/cmake/tests/test_main.cpp
)

target_link_libraries(test_infrared_sensor PRIVATE
    infrared_sensor_lib
    CppUTest::CppUTest
    CppUTestExt
)

add_test(NAME test_infrared_sensor COMMAND test_infrared_sensor)
