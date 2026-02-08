/*================================ FILE INFO =================================*/
/* Filename           : test_led.cpp                                          */
/*                                                                            */
/* Test implementation for led.c                                              */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                               Include Files                                */
/*============================================================================*/
extern "C" {
#include <stdint.h>
#include "gpio_hal.h"
#include "gpio_hal_config.h"
#include "led.h"
}

#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

/*============================================================================*/
/*                            Mock Implementations                            */
/*============================================================================*/
extern "C"
{

const struct gpio_hal_handler *get_gpio_hal_handler(void)
{
    return static_cast<const struct gpio_hal_handler *>(
        mock().actualCall("get_gpio_hal_handler")
        .returnConstPointerValue()
    );
}

const struct gpio_handle *get_led_d1_handle(void)
{
    return static_cast<const struct gpio_handle *>(
        mock().actualCall("get_led_d1_handle")
        .returnConstPointerValue()
    );
}

const struct gpio_handle *get_led_d2_handle(void)
{
    return static_cast<const struct gpio_handle *>(
        mock().actualCall("get_led_d2_handle")
        .returnConstPointerValue()
    );
}

const struct gpio_handle *get_led_d3_handle(void)
{
    return static_cast<const struct gpio_handle *>(
        mock().actualCall("get_led_d3_handle")
        .returnConstPointerValue()
    );
}

const struct gpio_handle *get_led_d4_handle(void)
{
    return static_cast<const struct gpio_handle *>(
        mock().actualCall("get_led_d4_handle")
        .returnConstPointerValue()
    );
}

}

/*============================================================================*/
/*                             Public Definitions                             */
/*============================================================================*/
/* none */

/*============================================================================*/
/*                                 Test Group                                 */
/*============================================================================*/
TEST_GROUP(LedTests)
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
TEST(LedTests, InitCallsFunctions)
{
    mock().expectOneCall("get_gpio_hal_handler")
        .andReturnValue(static_cast<const struct gpio_hal_handler *>(nullptr));
    mock().expectOneCall("get_led_d1_handle")
        .andReturnValue(static_cast<const struct gpio_handle *>(nullptr));
    mock().expectOneCall("get_led_d2_handle")
        .andReturnValue(static_cast<const struct gpio_handle *>(nullptr));
    mock().expectOneCall("get_led_d3_handle")
        .andReturnValue(static_cast<const struct gpio_handle *>(nullptr));
    mock().expectOneCall("get_led_d4_handle")
        .andReturnValue(static_cast<const struct gpio_handle *>(nullptr));
    init_leds();
}
