/*================================ FILE INFO =================================*/
/* Filename           : test_vacuum.cpp                                       */
/*                                                                            */
/* Test implementation for vacuum.c                                           */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                               Include Files                                */
/*============================================================================*/
extern "C" {
#include <stdint.h>
#include <stddef.h>
#include "pwm_hal.h"
#include "pwm_hal_config.h"
#include "vacuum.h"
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

const struct pwm_handle *get_vacuum_motor_handle(void)
{
    return static_cast<const struct pwm_handle *>(
        mock().actualCall("get_vacuum_motor_handle")
        .returnConstPointerValue()
    );
}

/*============================================================================*/
/*                             Public Definitions                             */
/*============================================================================*/
/* the definition of "struct pwm_handle" is hardware specific, so we mock */
struct pwm_handle {
    uint32_t mock_value;
};

const struct pwm_handle mock_vacuum_motor_handle = {0u};

bool set_duty_cycle_byte_called = false;

void dummy_init_pwm(void) {}
void dummy_deinit_pwm(void) {}
void mock_set_pwm_duty_cycle_byte(const struct pwm_handle *handle, uint8_t duty_cycle)
{
    if (handle == &mock_vacuum_motor_handle) {
        set_duty_cycle_byte_called = true;
    }
}

const struct pwm_hal_handler mock_pwm_handler = {
    dummy_init_pwm,
    dummy_deinit_pwm,
    mock_set_pwm_duty_cycle_byte
};

void reset_test_flags(void)
{
    set_duty_cycle_byte_called = false;
}

void init_vacuum_with_cpputest_checks(void)
{
    mock().expectOneCall("get_pwm_hal_handler")
        .andReturnValue(&mock_pwm_handler);
    mock().expectOneCall("get_vacuum_motor_handle")
        .andReturnValue(&mock_vacuum_motor_handle);
    init_vacuum();
}

/*============================================================================*/
/*                                 Test Group                                 */
/*============================================================================*/
TEST_GROUP(VacuumTests)
{
    void setup() override
    {
        reset_test_flags();
        mock().clear();
    }

    void teardown() override
    {
        mock().checkExpectations();
        mock().clear();
        reset_test_flags();
    }
};

/*============================================================================*/
/*                                    Tests                                   */
/*============================================================================*/
TEST(VacuumTests, InitCallsFunctions)
{
    init_vacuum_with_cpputest_checks();
}

TEST(VacuumTests, Deinit)
{
    deinit_vacuum();
}

TEST(VacuumTests, SetSpeedSetsDutyCycle)
{
    init_vacuum_with_cpputest_checks();
    set_vacuum_speed(255);
    CHECK(set_duty_cycle_byte_called);
}
