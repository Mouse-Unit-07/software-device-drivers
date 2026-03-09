/*================================ FILE INFO =================================*/
/* Filename           : test_pushbutton.cpp                                   */
/*                                                                            */
/* Test implementation for pushbutton.c                                       */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                               Include Files                                */
/*============================================================================*/
extern "C" {
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "eic_hal.h"
#include "eic_hal_config.h"
#include "gpio_hal.h"
#include "gpio_hal_config.h"
#include "clock_hal.h"
#include "clock_hal_config.h"
#include "pushbutton.h"
}

#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

/*============================================================================*/
/*                            Mock Implementations                            */
/*============================================================================*/
const struct eic_hal_handler *get_eic_hal_handler(void)
{
    return static_cast<const struct eic_hal_handler *>(
        mock().actualCall("get_eic_hal_handler")
        .returnConstPointerValue()
    );
}

const struct eic_handle *get_config_pushbutton_eic_handle(void)
{
    return static_cast<const struct eic_handle *>(
        mock().actualCall("get_config_pushbutton_eic_handle")
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

const struct gpio_handle *get_config_pushbutton_gpio_handle(void)
{
    return static_cast<const struct gpio_handle *>(
        mock().actualCall("get_config_pushbutton_gpio_handle")
        .returnConstPointerValue()
    );
}

const struct clock_hal_handler *get_clock_hal_handler(void)
{
    return static_cast<const struct clock_hal_handler *>(
        mock().actualCall("get_clock_hal_handler")
        .returnConstPointerValue()
    );
}

/*============================================================================*/
/*                             Public Definitions                             */
/*============================================================================*/
/* -------------------------------------------------------------------------- */
/* eic mock */
/* the definition of "struct eic_handle" is hardware specific, so we mock */
struct eic_handle {
    uint32_t mock_value;
};

const struct eic_handle mock_config_pushbutton_eic_handle = {0};

bool external_callback_set = false;

void dummy_init_eic(void) {}
void dummy_deinit_eic(void) {}
void mock_set_external_callback(const struct eic_handle *handle, 
                                     void (*callback)(void))
{
    CHECK(callback != nullptr);
    if (handle == &mock_config_pushbutton_eic_handle) {
        external_callback_set = true;
    }
}

const struct eic_hal_handler mock_eic_handler = {
    dummy_init_eic,
    dummy_deinit_eic,
    mock_set_external_callback
};

/* -------------------------------------------------------------------------- */
/* gpio mock */
/* the definition of "struct gpio_handle" is hardware specific, so we mock */
struct gpio_handle {
    uint32_t mock_value;
};

const struct gpio_handle mock_config_pushbutton_gpio_handle = {0};

bool mock_pushbutton_input = false;

void dummy_init_gpio(void) {}
void dummy_deinit_gpio(void) {}
bool mock_read_gpio_pin(const struct gpio_handle *handle)
{
    bool pin_reading = false;
    if (handle == &mock_config_pushbutton_gpio_handle) {
        pin_reading = mock_pushbutton_input;
    }
    return pin_reading;
}
void dummy_write_gpio_pin(const struct gpio_handle *handle, bool value){}
void dummy_toggle_gpio_pin(const struct gpio_handle *handle) {}

const struct gpio_hal_handler mock_gpio_handler = {
    dummy_init_gpio,
    dummy_deinit_gpio,
    mock_read_gpio_pin,
    dummy_write_gpio_pin,
    dummy_toggle_gpio_pin
};

void set_pushbutton_released(void)
{
    mock_pushbutton_input = true; /* HIGH for release */
}

/* -------------------------------------------------------------------------- */
/* clock mock */
uint32_t delay_ms_called_count = 0u;

void dummy_init_clock(void){}
void dummy_deinit_clock(void) {}
void mock_delay_ms(uint32_t delay_time)
{
    delay_ms_called_count++;
}
void dummy_delay_us(uint32_t delay_time){}

const struct clock_hal_handler mock_clock_handler = {
    dummy_init_clock,
    dummy_deinit_clock,
    mock_delay_ms,
    dummy_delay_us
};

/* -------------------------------------------------------------------------- */
/* test helpers */
void reset_test_flags(void)
{
    external_callback_set = false;
    delay_ms_called_count = 0u;
}

void reset_mock_input(void)
{
    mock_pushbutton_input = false;
}

void init_config_pushbutton_with_cpputest_checks(void)
{
    mock().expectOneCall("get_eic_hal_handler")
        .andReturnValue(&mock_eic_handler);
    mock().expectOneCall("get_config_pushbutton_eic_handle")
        .andReturnValue(&mock_config_pushbutton_eic_handle);
    mock().expectOneCall("get_gpio_hal_handler")
        .andReturnValue(&mock_gpio_handler);
    mock().expectOneCall("get_config_pushbutton_gpio_handle")
        .andReturnValue(&mock_config_pushbutton_gpio_handle);
    mock().expectOneCall("get_clock_hal_handler")
        .andReturnValue(&mock_clock_handler);
    init_pushbutton();
}

/*============================================================================*/
/*                                 Test Group                                 */
/*============================================================================*/
TEST_GROUP(PushbuttonTests)
{
    void setup() override
    {
        reset_test_flags();
        reset_mock_input();
        mock().clear();
    }

    void teardown() override
    {
        mock().checkExpectations();
        mock().clear();
        reset_mock_input();
        reset_test_flags();
    }
};

/*============================================================================*/
/*                                    Tests                                   */
/*============================================================================*/
TEST(PushbuttonTests, InitCallsFunctions)
{
    init_config_pushbutton_with_cpputest_checks();
}

TEST(PushbuttonTests, InitSetsExternalCallback)
{
    init_config_pushbutton_with_cpputest_checks();
    CHECK(external_callback_set);
}

TEST(PushbuttonTests, IsrIncrementsCountWithDebounce)
{
    init_config_pushbutton_with_cpputest_checks();
    set_pushbutton_released();
    pushbutton_isr();
    CHECK(delay_ms_called_count == 2);
    CHECK(get_pushbutton_count() == 1);
}
