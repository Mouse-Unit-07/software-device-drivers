/*================================ FILE INFO =================================*/
/* Filename           : test_infrared_sensor.cpp                              */
/*                                                                            */
/* Test implementation for infrared_sensor.c                                  */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                               Include Files                                */
/*============================================================================*/
extern "C" {
#include <stdint.h>
#include "adc_hal.h"
#include "adc_hal_config.h"
#include "infrared_sensor.h"
}

#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

/*============================================================================*/
/*                            Mock Implementations                            */
/*============================================================================*/
extern "C"
{

const struct adc_hal_handler *get_adc_hal_handler(void)
{
    return static_cast<const struct adc_hal_handler *>(
        mock().actualCall("get_adc_hal_handler")
        .returnConstPointerValue()
    );
}

const struct adc_handle *get_ir_sensor_1_handle(void)
{
    return static_cast<const struct adc_handle *>(
        mock().actualCall("get_ir_sensor_1_handle")
        .returnConstPointerValue()
    );
}

const struct adc_handle *get_ir_sensor_2_handle(void)
{
    return static_cast<const struct adc_handle *>(
        mock().actualCall("get_ir_sensor_2_handle")
        .returnConstPointerValue()
    );
}

const struct adc_handle *get_ir_sensor_3_handle(void)
{
    return static_cast<const struct adc_handle *>(
        mock().actualCall("get_ir_sensor_3_handle")
        .returnConstPointerValue()
    );
}

const struct adc_handle *get_ir_sensor_4_handle(void)
{
    return static_cast<const struct adc_handle *>(
        mock().actualCall("get_ir_sensor_4_handle")
        .returnConstPointerValue()
    );
}

}

/*============================================================================*/
/*                             Private Definitions                            */
/*============================================================================*/
/* none */

/*============================================================================*/
/*                                 Test Group                                 */
/*============================================================================*/
TEST_GROUP(InfraredSensorTests)
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
TEST(InfraredSensorTests, InitCallsFunctions)
{
    mock().expectOneCall("get_adc_hal_handler")
        .andReturnValue(static_cast<const struct adc_hal_handler *>(nullptr));
    mock().expectOneCall("get_ir_sensor_1_handle")
        .andReturnValue(static_cast<const struct adc_handle *>(nullptr));
    mock().expectOneCall("get_ir_sensor_2_handle")
        .andReturnValue(static_cast<const struct adc_handle *>(nullptr));
    mock().expectOneCall("get_ir_sensor_3_handle")
        .andReturnValue(static_cast<const struct adc_handle *>(nullptr));
    mock().expectOneCall("get_ir_sensor_4_handle")
        .andReturnValue(static_cast<const struct adc_handle *>(nullptr));
    init_infrared_sensors();
}
