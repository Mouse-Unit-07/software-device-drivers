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
/* none */

/*============================================================================*/
/*                                 Test Group                                 */
/*============================================================================*/
TEST_GROUP(VacuumTests)
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
TEST(VacuumTests, InitCallsFunctions)
{
    mock().expectOneCall("get_pwm_hal_handler")
        .andReturnValue(static_cast<const struct pwm_hal_handler *>(nullptr));
    mock().expectOneCall("get_vacuum_motor_handle")
        .andReturnValue(static_cast<const struct pwm_handle *>(nullptr));
    init_vacuum();
}

TEST(VacuumTests, Deinit)
{
    deinit_vacuum();
}
