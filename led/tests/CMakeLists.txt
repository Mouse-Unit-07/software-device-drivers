#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for led test files                                       #
#                                                                              #
#------------------------------------------------------------------------------#
set_property(GLOBAL APPEND PROPERTY
    ALL_TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_led.cpp
    ${CMAKE_SOURCE_DIR}/src/led/led.c
    ${CMAKE_SOURCE_DIR}/src/led/led.h
)

add_executable(test_led
    ${CMAKE_CURRENT_SOURCE_DIR}/test_led.cpp
    ${CMAKE_SOURCE_DIR}/platforms/windows/test_main.cpp
)

target_link_libraries(test_led PRIVATE
    led_lib
    CppUTest::CppUTest
    CppUTestExt
)

add_test(NAME test_led COMMAND test_led)
