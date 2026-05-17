#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for pushbutton test files                                #
#                                                                              #
#------------------------------------------------------------------------------#

if(NOT DEFINED MOUSE_TARGET)
    message(FATAL_ERROR "MOUSE_TARGET not specified")
endif()

if(MOUSE_TARGET STREQUAL "rev_a")
    set(PUSHBUTTON_TEST_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/test_pushbutton_sw_debounce.cpp
    )
    set(PUSHBUTTON_IMPLEMENTATION_SOURCE
        ${CMAKE_SOURCE_DIR}/src/pushbutton/pushbutton_sw_debounce.c
    )
elseif(MOUSE_TARGET STREQUAL "rev_b")
    set(PUSHBUTTON_TEST_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/test_pushbutton_hw_debounce.cpp
    )
    set(PUSHBUTTON_IMPLEMENTATION_SOURCE
        ${CMAKE_SOURCE_DIR}/src/pushbutton/pushbutton_hw_debounce.c
    )
else()
    message(FATAL_ERROR "Unsupported MOUSE_TARGET: ${MOUSE_TARGET}")
endif()

set_property(GLOBAL APPEND PROPERTY
    ALL_TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_pushbutton_sw_debounce.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_pushbutton_hw_debounce.cpp
    ${CMAKE_SOURCE_DIR}/src/pushbutton/pushbutton_sw_debounce.c
    ${CMAKE_SOURCE_DIR}/src/pushbutton/pushbutton_hw_debounce.c
    ${CMAKE_SOURCE_DIR}/src/pushbutton/pushbutton.h
)

add_executable(test_pushbutton
    ${PUSHBUTTON_TEST_SOURCE}
    ${CMAKE_SOURCE_DIR}/platforms/windows/test_main.cpp
)

target_link_libraries(test_pushbutton PRIVATE
    pushbutton_lib
    CppUTest::CppUTest
    CppUTestExt
)

add_test(NAME test_pushbutton COMMAND test_pushbutton)
