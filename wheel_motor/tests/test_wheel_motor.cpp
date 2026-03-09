/*================================ FILE INFO =================================*/
/* Filename           : test_wheel_motor.cpp                                  */
/*                                                                            */
/* Test implementation for wheel_motor.c                                      */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                               Include Files                                */
/*============================================================================*/
extern "C" {
#include <stdint.h>
#include <stddef.h>
#include "gpio_hal_config.h"
#include "pwm_hal_config.h"
#include "wheel_motor.h"
}

#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

/*============================================================================*/
/*                            Mock Implementations                            */
/*============================================================================*/
const struct pwm_hal_handler *get_pwm_hal_handler(void)
{
    return static_cast<const struct pwm_hal_handler *>(
        mock().actualCall("get_pwm_hal_handler")
        .returnConstPointerValue()
    );
}

const struct pwm_handle *get_wheel_motor_1_handle(void)
{
    return static_cast<const struct pwm_handle *>(
        mock().actualCall("get_wheel_motor_1_handle")
        .returnConstPointerValue()
    );
}

const struct pwm_handle *get_wheel_motor_2_handle(void)
{
    return static_cast<const struct pwm_handle *>(
        mock().actualCall("get_wheel_motor_2_handle")
        .returnConstPointerValue()
    );
}

const struct gpio_hal_handler *get_gpio_hal_handler(void)
{
    return static_cast<const struct gpio_hal_handler *>(
        mock().actualCall("get_gpio_hal_handler")
        .returnConstPointerValue()
    );
}

const struct gpio_handle *get_wheel_driver_standby_handle(void)
{
    return static_cast<const struct gpio_handle *>(
        mock().actualCall("get_wheel_driver_standby_handle")
        .returnConstPointerValue()
    );
}

const struct gpio_handle *get_wheel_driver_cld_handle(void)
{
    return static_cast<const struct gpio_handle *>(
        mock().actualCall("get_wheel_driver_cld_handle")
        .returnConstPointerValue()
    );
}

const struct gpio_handle *get_wheel_driver_motor_1_in1_handle(void)
{
    return static_cast<const struct gpio_handle *>(
        mock().actualCall("get_wheel_driver_motor_1_in1_handle")
        .returnConstPointerValue()
    );
}

const struct gpio_handle *get_wheel_driver_motor_1_in2_handle(void)
{
    return static_cast<const struct gpio_handle *>(
        mock().actualCall("get_wheel_driver_motor_1_in2_handle")
        .returnConstPointerValue()
    );
}

const struct gpio_handle *get_wheel_driver_motor_2_in1_handle(void)
{
    return static_cast<const struct gpio_handle *>(
        mock().actualCall("get_wheel_driver_motor_2_in1_handle")
        .returnConstPointerValue()
    );
}

const struct gpio_handle *get_wheel_driver_motor_2_in2_handle(void)
{
    return static_cast<const struct gpio_handle *>(
        mock().actualCall("get_wheel_driver_motor_2_in2_handle")
        .returnConstPointerValue()
    );
}

/*============================================================================*/
/*                             Public Definitions                             */
/*============================================================================*/
/* none */

/*============================================================================*/
/*                                 Test Group                                 */
/*============================================================================*/
TEST_GROUP(WheelMotorTests)
{
    void setup() override
    {
        mock().clear();
    }

    void teardown() override
    {
        mock().checkExpectations();
        mock().clear();
    }
};

/*============================================================================*/
/*                                    Tests                                   */
/*============================================================================*/
TEST(WheelMotorTests, InitCallsFunctions)
{
    mock().expectOneCall("get_pwm_hal_handler")
        .andReturnValue(static_cast<const struct pwm_hal_handler *>(nullptr));
    mock().expectOneCall("get_wheel_motor_1_handle")
        .andReturnValue(static_cast<const struct pwm_handle *>(nullptr));
    mock().expectOneCall("get_wheel_motor_2_handle")
        .andReturnValue(static_cast<const struct pwm_handle *>(nullptr));
    mock().expectOneCall("get_gpio_hal_handler")
        .andReturnValue(static_cast<const struct gpio_hal_handler *>(nullptr));
    mock().expectOneCall("get_wheel_driver_standby_handle")
        .andReturnValue(static_cast<const struct gpio_handle *>(nullptr));
    mock().expectOneCall("get_wheel_driver_cld_handle")
        .andReturnValue(static_cast<const struct gpio_handle *>(nullptr));
    mock().expectOneCall("get_wheel_driver_motor_1_in1_handle")
        .andReturnValue(static_cast<const struct gpio_handle *>(nullptr));
    mock().expectOneCall("get_wheel_driver_motor_1_in2_handle")
        .andReturnValue(static_cast<const struct gpio_handle *>(nullptr));
    mock().expectOneCall("get_wheel_driver_motor_2_in1_handle")
        .andReturnValue(static_cast<const struct gpio_handle *>(nullptr));
    mock().expectOneCall("get_wheel_driver_motor_2_in2_handle")
        .andReturnValue(static_cast<const struct gpio_handle *>(nullptr));
    init_wheel_motors();
}
