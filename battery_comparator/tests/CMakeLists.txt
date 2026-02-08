#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for battery_comparator test files                        #
#                                                                              #
#------------------------------------------------------------------------------#
set(ALL_TEST_SOURCES
    ${ALL_TEST_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/test_battery_comparator.cpp
    ${CMAKE_SOURCE_DIR}/src/battery_comparator/battery_comparator.c
    ${CMAKE_SOURCE_DIR}/src/battery_comparator/battery_comparator.h
    PARENT_SCOPE
)

add_executable(test_battery_comparator
    ${CMAKE_CURRENT_SOURCE_DIR}/test_battery_comparator.cpp
    ${CMAKE_SOURCE_DIR}/cmake/tests/test_main.cpp
)

target_link_libraries(test_battery_comparator PRIVATE
    battery_comparator_lib
    CppUTest::CppUTest
    CppUTestExt
)

add_test(NAME test_battery_comparator COMMAND test_battery_comparator)
