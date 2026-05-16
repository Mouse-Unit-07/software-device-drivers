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
    GIT_REPOSITORY git@github.com:Mouse-Unit-07/software-at32uc3l0256-drivers.git
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

if(TARGET_WINDOWS)
    if(SUPPORTS_WINDOWS)
        add_subdirectory(battery_comparator/tests)
        add_subdirectory(infrared_sensor/tests)
        add_subdirectory(led/tests)
        add_subdirectory(magnetic_encoder/tests)
        add_subdirectory(power_enabler/tests)
        add_subdirectory(processor/tests)
        add_subdirectory(pushbutton/tests)
        add_subdirectory(vacuum/tests)
        add_subdirectory(wheel_motor/tests)
    endif()
endif()

add_library(device_drivers_lib INTERFACE)

target_link_libraries(device_drivers_lib INTERFACE
    battery_comparator_lib
    infrared_sensor_lib
    led_lib
    magnetic_encoder_lib
    power_enabler_lib
    processor_lib
    pushbutton_lib
    vacuum_lib
    wheel_motor_lib
)
