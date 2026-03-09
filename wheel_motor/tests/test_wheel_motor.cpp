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
#include "pwm_hal.h"
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
/* PWM mocks */
/* the definition of "struct pwm_handle" is hardware specific, so we mock */
struct pwm_handle {
    uint32_t mock_value;
};

const struct pwm_handle mock_pwm_handles[] = {{0}, {0}};

uint8_t mock_output_duty_cycles[] = {0u, 0u};

enum wheel_motor_index
{
    WHEEL_MOTOR_1_INDEX = 0,
    WHEEL_MOTOR_2_INDEX,
    WHEEL_MOTOR_COUNT
};

void dummy_init_pwm(void) {}
void dummy_deinit_pwm(void) {}
void mock_set_pwm_duty_cycle_byte(const struct pwm_handle *handle, uint8_t duty_cycle)
{
    for (uint32_t i = 0u; i < WHEEL_MOTOR_COUNT; i++) {
        if (handle == &(mock_pwm_handles[i])) {
            mock_output_duty_cycles[i] = duty_cycle;
        }
    }
}

const struct pwm_hal_handler mock_pwm_handler = {
    dummy_init_pwm,
    dummy_deinit_pwm,
    mock_set_pwm_duty_cycle_byte
};

/* -------------------------------------------------------------------------- */
/* test helpers */
void reset_mock_values(void)
{
    memset(mock_output_duty_cycles, 0u, sizeof(mock_output_duty_cycles));
}

void init_wheel_motors_with_cpputest_checks(void)
{
    mock().expectOneCall("get_pwm_hal_handler")
        .andReturnValue(&mock_pwm_handler);
    mock().expectOneCall("get_wheel_motor_1_handle")
        .andReturnValue(&(mock_pwm_handles[WHEEL_MOTOR_1_INDEX]));
    mock().expectOneCall("get_wheel_motor_2_handle")
        .andReturnValue(&(mock_pwm_handles[WHEEL_MOTOR_2_INDEX]));
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

/*============================================================================*/
/*                                 Test Group                                 */
/*============================================================================*/
TEST_GROUP(WheelMotorTests)
{
    void setup() override
    {
        reset_mock_values();
        mock().clear();
    }

    void teardown() override
    {
        mock().checkExpectations();
        mock().clear();
        reset_mock_values();
    }
};

/*============================================================================*/
/*                                    Tests                                   */
/*============================================================================*/
TEST(WheelMotorTests, InitCallsFunctions)
{
    init_wheel_motors_with_cpputest_checks();
}

TEST(WheelMotorTests, SetSpeedFunctionsSetDutyCycle)
{
    init_wheel_motors_with_cpputest_checks();
    set_wheel_motor_1_speed(100u);
    CHECK(mock_output_duty_cycles[WHEEL_MOTOR_1_INDEX] == 100u);
    set_wheel_motor_2_speed(200u);
    CHECK(mock_output_duty_cycles[WHEEL_MOTOR_2_INDEX] == 200u);
}
