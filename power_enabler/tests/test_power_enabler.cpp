/*================================ FILE INFO =================================*/
/* Filename           : test_power_enabler.cpp                                */
/*                                                                            */
/* Test implementation for power_enabler.c                                    */
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
#include "power_enabler.h"

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

const struct gpio_handle *get_regulators_enable_handle(void)
{
    return static_cast<const struct gpio_handle *>(
            mock().actualCall("get_regulators_enable_handle").returnConstPointerValue());
}

/*============================================================================*/
/*                             Public Definitions                             */
/*============================================================================*/
/* GPIO mocks */
/* the definition of "struct gpio_handle" is hardware specific, so we mock */
struct gpio_handle {
    uint32_t mock_value;
};

const struct gpio_handle mock_handle = {0};

bool mock_output = false;

void dummy_init_gpio(void) {}
void dummy_deinit_gpio(void) {}
bool dummy_read_gpio_pin(const struct gpio_handle *handle) { return true; }
void mock_write_gpio_pin(const struct gpio_handle *handle, bool value)
{
    if (handle == &mock_handle) {
        mock_output = value;
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
void reset_mock_output(void)
{
    mock_output = false;
}

void init_power_enabler_with_cpputest_checks(void)
{
    mock().expectOneCall("get_gpio_hal_handler").andReturnValue(&mock_handler);
    mock().expectOneCall("get_regulators_enable_handle").andReturnValue(&mock_handle);
    init_power_enabler();
}

/*============================================================================*/
/*                                 Test Group                                 */
/*============================================================================*/
TEST_GROUP(PowerEnablerTests)
{
    void setup() override
    {
        reset_mock_output();
        mock().clear();
    }

    void teardown() override
    {
        mock().checkExpectations();
        mock().clear();
        reset_mock_output();
    }
};

/*============================================================================*/
/*                                    Tests                                   */
/*============================================================================*/
TEST(PowerEnablerTests, InitCallsFunctions)
{
    init_power_enabler_with_cpputest_checks();
}

TEST(PowerEnablerTests, DeinitDisablesPower)
{
    init_power_enabler_with_cpputest_checks();
    enable_power();
    deinit_power_enabler();
    CHECK(!mock_output);
}

TEST(PowerEnablerTests, EnablePowerSetsOutput)
{
    init_power_enabler_with_cpputest_checks();
    enable_power();
    CHECK(mock_output);
}

TEST(PowerEnablerTests, DisablePowerClearsOutput)
{
    init_power_enabler_with_cpputest_checks();
    enable_power();
    disable_power();
    CHECK(!mock_output);
}
