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
/*                             Private Definitions                            */
/*============================================================================*/
/* none */

/*============================================================================*/
/*                                 Test Group                                 */
/*============================================================================*/
TEST_GROUP(MagneticEncoderTests)
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
TEST(MagneticEncoderTests, InitCallsFunctions)
{
    mock().expectOneCall("get_eic_hal_handler")
        .andReturnValue(static_cast<const struct eic_hal_handler *>(nullptr));
    mock().expectOneCall("get_gpio_hal_handler")
        .andReturnValue(static_cast<const struct gpio_hal_handler *>(nullptr));
    mock().expectOneCall("get_wheel_encoder_motor_1_b_channel_handle")
        .andReturnValue(static_cast<const struct gpio_handle *>(nullptr));
    mock().expectOneCall("get_wheel_encoder_motor_2_b_channel_handle")
        .andReturnValue(static_cast<const struct gpio_handle *>(nullptr));
    init_magnetic_encoder();
}
