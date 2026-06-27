/*================================ FILE INFO =================================*/
/* Filename           : test_vacuum.cpp                                       */
/*                                                                            */
/* Test implementation for vacuum.c                                           */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                               Include Files                                */
/*============================================================================*/
extern "C"
{

#include <stddef.h>
#include <stdint.h>
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
            mock().actualCall("get_pwm_hal_handler").returnConstPointerValue());
}

const struct pwm_handle *get_vacuum_motor_handle(void)
{
    return static_cast<const struct pwm_handle *>(
            mock().actualCall("get_vacuum_motor_handle").returnConstPointerValue());
}

/*============================================================================*/
/*                             Public Definitions                             */
/*============================================================================*/
/* PWM mocks */
/* the definition of "struct pwm_handle" is hardware specific, so we mock */
struct pwm_handle {
    uint32_t mock_value;
};

const struct pwm_handle mock_vacuum_motor_handle = {0};

uint8_t mock_duty_cycle_byte = 0u;

void dummy_init_pwm(void) {}
void dummy_deinit_pwm(void) {}
void mock_set_pwm_duty_cycle_byte(const struct pwm_handle *handle, uint8_t duty_cycle)
{
    if (handle == &mock_vacuum_motor_handle) {
        mock_duty_cycle_byte = duty_cycle;
    }
}

const struct pwm_hal_handler mock_pwm_handler = {
        dummy_init_pwm,
        dummy_deinit_pwm,
        mock_set_pwm_duty_cycle_byte};

/* -------------------------------------------------------------------------- */
/* test helpers */
void reset_mock_values(void)
{
    mock_duty_cycle_byte = 0u;
}

void init_vacuum_with_cpputest_checks(void)
{
    mock().expectOneCall("get_pwm_hal_handler").andReturnValue(&mock_pwm_handler);
    mock().expectOneCall("get_vacuum_motor_handle").andReturnValue(&mock_vacuum_motor_handle);
    init_vacuum();
}

/*============================================================================*/
/*                                 Test Group                                 */
/*============================================================================*/
TEST_GROUP(VacuumTests)
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
TEST(VacuumTests, InitCallsFunctions)
{
    init_vacuum_with_cpputest_checks();
}

TEST(VacuumTests, DeinitTurnsOffVacuum)
{
    init_vacuum_with_cpputest_checks();
    set_vacuum_speed(255u);
    deinit_vacuum();
    LONGS_EQUAL(0u, mock_duty_cycle_byte);
}

TEST(VacuumTests, SetSpeedSetsDutyCycle)
{
    init_vacuum_with_cpputest_checks();
    set_vacuum_speed(255u);
    LONGS_EQUAL(255u, mock_duty_cycle_byte);
}
