/*================================ FILE INFO =================================*/
/* Filename           : test_magnetic_encoder.cpp                             */
/*                                                                            */
/* Test implementation for magnetic_encoder.c                                 */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                               Include Files                                */
/*============================================================================*/
extern "C" {
#include <stdint.h>
#include "eic_hal.h"
#include "eic_hal_config.h"
#include "gpio_hal.h"
#include "gpio_hal_config.h"
#include "magnetic_encoder.h"
}

#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

/*============================================================================*/
/*                            Mock Implementations                            */
/*============================================================================*/
extern "C"
{

const struct eic_hal_handler *get_eic_hal_handler(void)
{
    return static_cast<const struct eic_hal_handler *>(
        mock().actualCall("get_eic_hal_handler")
        .returnConstPointerValue()
    );
}

const struct eic_handle *get_motor_1_encoder_handle(void)
{
    return static_cast<const struct eic_handle *>(
        mock().actualCall("get_motor_1_encoder_handle")
        .returnConstPointerValue()
    );
}

const struct eic_handle *get_motor_2_encoder_handle(void)
{
    return static_cast<const struct eic_handle *>(
        mock().actualCall("get_motor_2_encoder_handle")
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

const struct gpio_handle *get_wheel_encoder_motor_1_b_channel_handle(void)
{
    return static_cast<const struct gpio_handle *>(
        mock().actualCall("get_wheel_encoder_motor_1_b_channel_handle")
        .returnConstPointerValue()
    );
}

const struct gpio_handle *get_wheel_encoder_motor_2_b_channel_handle(void)
{
    return static_cast<const struct gpio_handle *>(
        mock().actualCall("get_wheel_encoder_motor_2_b_channel_handle")
        .returnConstPointerValue()
    );
}

}

/*============================================================================*/
/*                             Public Definitions                             */
/*============================================================================*/
extern "C"
{

/* the definition of "struct eic_handle" is hardware specific, so we mock */
struct eic_handle {
    uint32_t mock_value;
};

const struct eic_handle mock_eic_handles[] = {
    {0u}, {0u}, {0u}, {0u}
};

bool mock_external_callback_set_flags[] = {
    false, false
};

enum external_callback_index
{
    EXTERNAL_CALLBACK_1_INDEX = 0,
    EXTERNAL_CALLBACK_2_INDEX,
    EXTERNAL_CALLBACK_COUNT
};

void reset_external_callback_set_flags(void)
{
    for (uint32_t i = 0u; i < EXTERNAL_CALLBACK_COUNT; i++) {
        mock_external_callback_set_flags[i] = false;
    }
}

void dummy_init_eic(void) {}
void dummy_deinit_eic(void) {}
void mock_set_external_callback(const struct eic_handle *handle, 
                                     void (*callback)(void))
{
    for (uint32_t i = 0u; i < EXTERNAL_CALLBACK_COUNT; i++) {
        if (handle == &(mock_eic_handles[i])) {
            mock_external_callback_set_flags[i] = true;
        }
    }
}

const struct eic_hal_handler mock_eic_handler = {
    dummy_init_eic,
    dummy_deinit_eic,
    mock_set_external_callback
};

}

void init_magnetic_encoders_with_cpputest_checks(void)
{
    mock().expectOneCall("get_eic_hal_handler")
        .andReturnValue(&mock_eic_handler);
    mock().expectOneCall("get_motor_1_encoder_handle")
        .andReturnValue(&(mock_eic_handles[0]));
    mock().expectOneCall("get_motor_2_encoder_handle")
        .andReturnValue(&(mock_eic_handles[1]));
    mock().expectOneCall("get_gpio_hal_handler")
        .andReturnValue(static_cast<const struct gpio_hal_handler *>(nullptr));
    mock().expectOneCall("get_wheel_encoder_motor_1_b_channel_handle")
        .andReturnValue(static_cast<const struct gpio_handle *>(nullptr));
    mock().expectOneCall("get_wheel_encoder_motor_2_b_channel_handle")
        .andReturnValue(static_cast<const struct gpio_handle *>(nullptr));
    init_magnetic_encoders();
}

/*============================================================================*/
/*                                 Test Group                                 */
/*============================================================================*/
TEST_GROUP(MagneticEncoderTests)
{
    void setup() override
    {
        reset_external_callback_set_flags();
        mock().clear();
    }

    void teardown() override
    {
        mock().checkExpectations();
        mock().clear();
        reset_external_callback_set_flags();
    }
};

/*============================================================================*/
/*                                    Tests                                   */
/*============================================================================*/
TEST(MagneticEncoderTests, InitCallsFunctions)
{
    init_magnetic_encoders_with_cpputest_checks();
}

TEST(MagneticEncoderTests, InitSetsExternalCallbacks)
{
    init_magnetic_encoders_with_cpputest_checks();
    CHECK(mock_external_callback_set_flags[EXTERNAL_CALLBACK_1_INDEX]);
    CHECK(mock_external_callback_set_flags[EXTERNAL_CALLBACK_2_INDEX]);
}
