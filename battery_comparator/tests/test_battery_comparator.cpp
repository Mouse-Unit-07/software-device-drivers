/*================================ FILE INFO =================================*/
/* Filename           : test_battery_comparator.cpp                           */
/*                                                                            */
/* Test implementation for battery_comparator.c                               */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                               Include Files                                */
/*============================================================================*/
extern "C" {
#include "gpio_hal.h"
#include "gpio_hal_config.h"
#include "battery_comparator.h"
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

const struct gpio_handle *get_battery_comparator_handle(void)
{
    return static_cast<const struct gpio_handle *>(
        mock().actualCall("get_battery_comparator_handle")
        .returnConstPointerValue()
    );
}

}

/*============================================================================*/
/*                             Public Definitions                             */
/*============================================================================*/
extern "C"
{

static bool mock_pin_value = false;

void set_mock_pin_value(bool value)
{
    mock_pin_value = value;
}

void dummy_init_gpio(void) {}
void dummy_deinit_gpio(void) {}
void dummy_write_gpio_pin(const struct gpio_handle *handle, bool value) {}
void dummy_toggle_gpio_pin(const struct gpio_handle *handle) {}
bool mock_read_gpio_pin(const struct gpio_handle *handle)
{
    return mock_pin_value;
}

const gpio_hal_handler mock_handler = {
    dummy_init_gpio,
    dummy_deinit_gpio,
    mock_read_gpio_pin,
    dummy_write_gpio_pin,
    dummy_toggle_gpio_pin
};

}

/*============================================================================*/
/*                                 Test Group                                 */
/*============================================================================*/
TEST_GROUP(BatteryComparatorTests)
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
TEST(BatteryComparatorTests, InitCallsFunctions)
{
    mock().expectOneCall("get_gpio_hal_handler")
        .andReturnValue(&mock_handler);
    mock().expectOneCall("get_battery_comparator_handle")
        .andReturnValue(static_cast<const struct gpio_handle *>(nullptr));

    init_battery_comparator();
}


