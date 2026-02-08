#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# Top level CMakeLists.txt file (for this software repo)                       #
#                                                                              #
#------------------------------------------------------------------------------#
cmake_minimum_required(VERSION 4.0.2)
project(device_drivers_project LANGUAGES C)

include(FetchContent)

FetchContent_Declare(
    hal_drivers
    GIT_REPOSITORY https://github.com/Mouse-Unit-07/software-at32uc3l0256-drivers
    GIT_TAG main
)
FetchContent_MakeAvailable(hal_drivers)

add_subdirectory(battery_comparator)
add_subdirectory(infrared_sensor)
add_subdirectory(led)
add_subdirectory(magnetic_encoder)
add_subdirectory(power_enabler)
add_subdirectory(processor)
add_subdirectory(pushbutton)
add_subdirectory(vacuum)
add_subdirectory(wheel_motor)
