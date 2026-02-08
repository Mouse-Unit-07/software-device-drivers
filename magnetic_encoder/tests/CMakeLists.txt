#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for magnetic_encoder test files                          #
#                                                                              #
#------------------------------------------------------------------------------#
set(ALL_TEST_SOURCES
    ${ALL_TEST_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/test_magnetic_encoder.cpp
    ${CMAKE_SOURCE_DIR}/src/magnetic_encoder/magnetic_encoder.c
    ${CMAKE_SOURCE_DIR}/src/magnetic_encoder/magnetic_encoder.h
    PARENT_SCOPE
)

add_executable(test_magnetic_encoder
    ${CMAKE_CURRENT_SOURCE_DIR}/test_magnetic_encoder.cpp
    ${CMAKE_SOURCE_DIR}/cmake/tests/test_main.cpp
)

target_link_libraries(test_magnetic_encoder PRIVATE
    magnetic_encoder_lib
    CppUTest::CppUTest
    CppUTestExt
)

add_test(NAME test_magnetic_encoder COMMAND test_magnetic_encoder)
