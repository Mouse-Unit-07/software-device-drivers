/*================================ FILE INFO =================================*/
/* Filename           : test_power_enabler.cpp                                */
/*                                                                            */
/* Test implementation for power_enabler.c                                    */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                               Include Files                                */
/*============================================================================*/
extern "C" {
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
        mock().actualCall("get_gpio_hal_handler")
        .returnConstPointerValue()
    );
}

const struct gpio_handle *get_regulators_enable_handle(void)
{
    return static_cast<const struct gpio_handle *>(
        mock().actualCall("get_regulators_enable_handle")
        .returnConstPointerValue()
    );
}

/*============================================================================*/
/*                             Private Definitions                            */
/*============================================================================*/
/* none */

/*============================================================================*/
/*                                 Test Group                                 */
/*============================================================================*/
TEST_GROUP(PowerEnablerTests)
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
TEST(PowerEnablerTests, InitCallsFunctions)
{
    mock().expectOneCall("get_gpio_hal_handler")
        .andReturnValue(static_cast<const struct gpio_hal_handler *>(nullptr));
    mock().expectOneCall("get_regulators_enable_handle")
        .andReturnValue(static_cast<const struct gpio_handle *>(nullptr));
    init_power_enabler();
}
