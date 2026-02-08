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
/*                             Public Definitions                             */
/*============================================================================*/
extern "C"
{

/* the definition of "struct adc_handle" is hardware specific, so we mock */
struct adc_handle {
    uint32_t mock_value;
};

const struct adc_handle mock_handles[] = {
    {0u}, {0u}, {0u}, {0u}
};

uint32_t mock_sensor_readings[] = {
    0u, 0u, 0u, 0u
};

enum sensor_index
{
    IR_SENSOR_1_INDEX = 0,
    IR_SENSOR_2_INDEX,
    IR_SENSOR_3_INDEX,
    IR_SENSOR_4_INDEX,
    SENSOR_COUNT
};

void reset_mock_reading(void)
{
    memset(mock_sensor_readings, 0u, sizeof(mock_sensor_readings));
}

void set_mock_reading(enum sensor_index index, uint32_t value)
{
    mock_sensor_readings[index] = value;
}

void dummy_init_adc(void) {}
void dummy_deinit_adc(void) {}
uint32_t mock_read_adc_channel(const struct adc_handle *handle)
{
    for (uint32_t i = 0u; i < SENSOR_COUNT; i++) {
        if (handle == &(mock_handles[i])) {
            return mock_sensor_readings[i];
        }
    }
    return 0u;
}

const struct adc_hal_handler mock_handler = {
    dummy_init_adc,
    dummy_deinit_adc,
    mock_read_adc_channel
};

}

void init_infrared_sensors_with_cpputest_checks(void)
{
    mock().expectOneCall("get_adc_hal_handler")
        .andReturnValue(&mock_handler);
    mock().expectOneCall("get_ir_sensor_1_handle")
        .andReturnValue(&(mock_handles[0]));
    mock().expectOneCall("get_ir_sensor_2_handle")
        .andReturnValue(&(mock_handles[1]));
    mock().expectOneCall("get_ir_sensor_3_handle")
        .andReturnValue(&(mock_handles[2]));
    mock().expectOneCall("get_ir_sensor_4_handle")
        .andReturnValue(&(mock_handles[3]));
    init_infrared_sensors();
}

/*============================================================================*/
/*                                 Test Group                                 */
/*============================================================================*/
TEST_GROUP(InfraredSensorTests)
{
    void setup() override
    {
        reset_mock_reading();
        mock().clear();
    }

    void teardown() override
    {
        mock().checkExpectations();
        mock().clear();
        reset_mock_reading();
    }
};

/*============================================================================*/
/*                                    Tests                                   */
/*============================================================================*/
TEST(InfraredSensorTests, InitCallsFunctions)
{
    init_infrared_sensors_with_cpputest_checks();
}

TEST(InfraredSensorTests, ReadIrSensorReadsAdcValue)
{
    init_infrared_sensors_with_cpputest_checks();

    set_mock_reading(IR_SENSOR_1_INDEX, 256u);
    CHECK(read_ir_1_sensor() == 256u);
    set_mock_reading(IR_SENSOR_2_INDEX, 512u);
    CHECK(read_ir_2_sensor() == 512u);
    set_mock_reading(IR_SENSOR_3_INDEX, 768u);
    CHECK(read_ir_3_sensor() == 768u);
    set_mock_reading(IR_SENSOR_4_INDEX, 1024u);
    CHECK(read_ir_4_sensor() == 1024u);
}
