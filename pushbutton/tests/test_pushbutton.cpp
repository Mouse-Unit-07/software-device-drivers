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

/*============================================================================*/
/*                             Public Definitions                             */
/*============================================================================*/
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

void reset_test_flags(void)
{
    external_callback_set = false;
}

/* -------------------------------------------------------------------------- */
/* test helpers */
void init_config_pushbutton_with_cpputest_checks(void)
{
    mock().expectOneCall("get_eic_hal_handler")
        .andReturnValue(&mock_eic_handler);
    mock().expectOneCall("get_config_pushbutton_eic_handle")
        .andReturnValue(&mock_config_pushbutton_eic_handle);
    mock().expectOneCall("get_gpio_hal_handler")
        .andReturnValue(static_cast<const struct gpio_hal_handler *>(nullptr));
    mock().expectOneCall("get_config_pushbutton_gpio_handle")
        .andReturnValue(static_cast<const struct gpio_handle *>(nullptr));
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
        mock().clear();
    }

    void teardown() override
    {
        mock().checkExpectations();
        mock().clear();
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
