/*================================ FILE INFO =================================*/
/* Filename           : test_led.cpp                                          */
/*                                                                            */
/* Test implementation for led.c                                              */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                               Include Files                                */
/*============================================================================*/
extern "C"
{

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
const struct gpio_hal_handler *get_gpio_hal_handler(void)
{
    return static_cast<const struct gpio_hal_handler *>(
            mock().actualCall("get_gpio_hal_handler").returnConstPointerValue());
}

const struct gpio_handle *get_led_d1_handle(void)
{
    return static_cast<const struct gpio_handle *>(
            mock().actualCall("get_led_d1_handle").returnConstPointerValue());
}

const struct gpio_handle *get_led_d2_handle(void)
{
    return static_cast<const struct gpio_handle *>(
            mock().actualCall("get_led_d2_handle").returnConstPointerValue());
}

const struct gpio_handle *get_led_d3_handle(void)
{
    return static_cast<const struct gpio_handle *>(
            mock().actualCall("get_led_d3_handle").returnConstPointerValue());
}

const struct gpio_handle *get_led_d4_handle(void)
{
    return static_cast<const struct gpio_handle *>(
            mock().actualCall("get_led_d4_handle").returnConstPointerValue());
}

/*============================================================================*/
/*                             Public Definitions                             */
/*============================================================================*/
/* GPIO mocks */
/* the definition of "struct gpio_handle" is hardware specific, so we mock */
struct gpio_handle {
    uint32_t mock_value;
};

const struct gpio_handle mock_handles[] = {{0}, {0}, {0}, {0}};

bool mock_led_outputs[] = {false, false, false, false};

enum led_index
{
    LED_1_INDEX = 0,
    LED_2_INDEX,
    LED_3_INDEX,
    LED_4_INDEX,
    LED_COUNT
};

void set_mock_output(enum led_index index, bool value)
{
    mock_led_outputs[index] = value;
}

void dummy_init_gpio(void) {}
void dummy_deinit_gpio(void) {}
bool dummy_read_gpio_pin(const struct gpio_handle *handle) { return true; }
void mock_write_gpio_pin(const struct gpio_handle *handle, bool value)
{
    for (uint32_t i = 0u; i < LED_COUNT; i++) {
        if (handle == &(mock_handles[i])) {
            mock_led_outputs[i] = value;
        }
    }
}
void dummy_toggle_gpio_pin(const struct gpio_handle *handle) {}

const struct gpio_hal_handler mock_handler = {
        dummy_init_gpio,
        dummy_deinit_gpio,
        dummy_read_gpio_pin,
        mock_write_gpio_pin,
        dummy_toggle_gpio_pin};

/* -------------------------------------------------------------------------- */
/* test helpers */
void reset_mock_outputs(void)
{
    memset(mock_led_outputs, false, sizeof(mock_led_outputs));
}

void init_leds_with_cpputest_checks(void)
{
    mock().expectOneCall("get_gpio_hal_handler").andReturnValue(&mock_handler);
    mock().expectOneCall("get_led_d1_handle").andReturnValue(&(mock_handles[LED_1_INDEX]));
    mock().expectOneCall("get_led_d2_handle").andReturnValue(&(mock_handles[LED_2_INDEX]));
    mock().expectOneCall("get_led_d3_handle").andReturnValue(&(mock_handles[LED_3_INDEX]));
    mock().expectOneCall("get_led_d4_handle").andReturnValue(&(mock_handles[LED_4_INDEX]));
    init_leds();
}

/*============================================================================*/
/*                                 Test Group                                 */
/*============================================================================*/
TEST_GROUP(LedTests)
{
    void setup() override
    {
        reset_mock_outputs();
        mock().clear();
    }

    void teardown() override
    {
        mock().checkExpectations();
        mock().clear();
        reset_mock_outputs();
    }
};

/*============================================================================*/
/*                                    Tests                                   */
/*============================================================================*/
TEST(LedTests, InitCallsFunctions)
{
    init_leds_with_cpputest_checks();
}

TEST(LedTests, DeinitTurnsOffLeds)
{
    init_leds_with_cpputest_checks();
    set_led_d1_enabled(true);
    set_led_d2_enabled(true);
    set_led_d3_enabled(true);
    set_led_d4_enabled(true);
    deinit_leds();
    CHECK(mock_led_outputs[LED_1_INDEX] == false);
    CHECK(mock_led_outputs[LED_2_INDEX] == false);
    CHECK(mock_led_outputs[LED_3_INDEX] == false);
    CHECK(mock_led_outputs[LED_4_INDEX] == false);
}

TEST(LedTests, SetEnabledSetsLeds)
{
    init_leds_with_cpputest_checks();
    set_led_d1_enabled(true);
    set_led_d2_enabled(true);
    set_led_d3_enabled(true);
    set_led_d4_enabled(true);
    CHECK(mock_led_outputs[LED_1_INDEX] == true);
    CHECK(mock_led_outputs[LED_2_INDEX] == true);
    CHECK(mock_led_outputs[LED_3_INDEX] == true);
    CHECK(mock_led_outputs[LED_4_INDEX] == true);
}
