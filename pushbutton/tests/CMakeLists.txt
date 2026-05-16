#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for pushbutton test files                                #
#                                                                              #
#------------------------------------------------------------------------------#
set_property(GLOBAL APPEND PROPERTY
    ALL_TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_pushbutton.cpp
    ${CMAKE_SOURCE_DIR}/src/pushbutton/pushbutton.c
    ${CMAKE_SOURCE_DIR}/src/pushbutton/pushbutton.h
)

add_executable(test_pushbutton
    ${CMAKE_CURRENT_SOURCE_DIR}/test_pushbutton.cpp
    ${CMAKE_SOURCE_DIR}/platforms/windows/test_main.cpp
)

target_link_libraries(test_pushbutton PRIVATE
    pushbutton_lib
    CppUTest::CppUTest
    CppUTestExt
)

add_test(NAME test_pushbutton COMMAND test_pushbutton)
