#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for processor test files                                 #
#                                                                              #
#------------------------------------------------------------------------------#
set_property(GLOBAL APPEND PROPERTY
    ALL_TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_processor.cpp
    ${CMAKE_SOURCE_DIR}/src/processor/processor.c
    ${CMAKE_SOURCE_DIR}/src/processor/processor.h
)

add_executable(test_processor
    ${CMAKE_CURRENT_SOURCE_DIR}/test_processor.cpp
    ${CMAKE_SOURCE_DIR}/platforms/windows/test_main.cpp
)

target_link_libraries(test_processor PRIVATE
    processor_lib
    CppUTest::CppUTest
    CppUTestExt
)

add_test(NAME test_processor COMMAND test_processor)
