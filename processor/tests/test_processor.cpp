/*================================ FILE INFO =================================*/
/* Filename           : test_processor.cpp                                    */
/*                                                                            */
/* Test implementation for processor.c                                        */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                               Include Files                                */
/*============================================================================*/
extern "C" {
#include <stdint.h>
#include "adc_hal.h"
#include "adc_hal_config.h"
#include "clock_hal.h"
#include "clock_hal_config.h"
#include "eic_hal.h"
#include "eic_hal_config.h"
#include "gpio_hal.h"
#include "gpio_hal_config.h"
#include "iic_hal.h"
#include "iic_hal_config.h"
#include "pwm_hal.h"
#include "pwm_hal_config.h"
#include "timer_counter_hal.h"
#include "timer_counter_hal_config.h"
#include "usart_hal.h"
#include "usart_hal_config.h"
#include "processor.h"
}

#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

/*============================================================================*/
/*                            Mock Implementations                            */
/*============================================================================*/
const struct adc_hal_handler *get_adc_hal_handler(void)
{
    return static_cast<const struct adc_hal_handler *>(
        mock().actualCall("get_adc_hal_handler")
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

const struct iic_hal_handler *get_iic_hal_handler(void)
{
    return static_cast<const struct iic_hal_handler *>(
        mock().actualCall("get_iic_hal_handler")
        .returnConstPointerValue()
    );
}

const struct pwm_hal_handler *get_pwm_hal_handler(void)
{
    return static_cast<const struct pwm_hal_handler *>(
        mock().actualCall("get_pwm_hal_handler")
        .returnConstPointerValue()
    );
}

const struct tc_hal_handler *get_tc_hal_handler(void)
{
    return static_cast<const struct tc_hal_handler *>(
        mock().actualCall("get_tc_hal_handler")
        .returnConstPointerValue()
    );
}

const struct usart_hal_handler *get_usart_hal_handler(void)
{
    return static_cast<const struct usart_hal_handler *>(
        mock().actualCall("get_usart_hal_handler")
        .returnConstPointerValue()
    );
}

/*============================================================================*/
/*                             Public Definitions                             */
/*============================================================================*/
/* init flags */
bool adc_initialized{false};
bool clock_initialized{false};
bool eic_initialized{false};
bool gpio_initialized{false};
bool iic_initialized{false};
bool pwm_initialized{false};
bool tc_initialized{false};
bool usart_initialized{false};

/* ---------------------------------------------------------------------------*/
/* ADC mock variables */
void mock_init_adc(void)
{
    adc_initialized = true;
}
void dummy_deinit_adc(void) {}
uint32_t dummy_read_adc_channel(const struct adc_handle *handle) { return 0; }

const struct adc_hal_handler mock_adc_handler = {
    mock_init_adc,
    dummy_deinit_adc,
    dummy_read_adc_channel
};

/* ---------------------------------------------------------------------------*/
/* clock mock variables */
void mock_init_clock(void)
{
    clock_initialized = true;
}
void dummy_deinit_clock(void) {}
void dummy_delay_ms(uint32_t delay_time) {}
void dummy_delay_us(uint32_t delay_time) {}

const struct clock_hal_handler mock_clock_handler = {
    mock_init_clock,
    dummy_deinit_clock,
    dummy_delay_ms,
    dummy_delay_us
};

/* ---------------------------------------------------------------------------*/
/* EIC mock variables */
void mock_init_eic(void)
{
    /* EIC init must come after IIC init */
    CHECK(!adc_initialized);
    CHECK(!clock_initialized);
    CHECK(!gpio_initialized);
    CHECK(iic_initialized);
    CHECK(!pwm_initialized);
    CHECK(!tc_initialized);
    CHECK(!usart_initialized);
    eic_initialized = true;
}
void dummy_deinit_eic(void) {}
void dummy_set_external_callback(const struct eic_handle *handle,
    void (*callback)(void)) {}

const struct eic_hal_handler mock_eic_handler = {
    mock_init_eic,
    dummy_deinit_eic,
    dummy_set_external_callback
};

/* ---------------------------------------------------------------------------*/
/* GPIO mock variables */
void mock_init_gpio(void)
{
    gpio_initialized = true;
}
void dummy_deinit_gpio(void) {}
bool dummy_read_gpio_pin(const struct gpio_handle *handle) { return true; }
void dummy_write_gpio_pin(const struct gpio_handle *handle, bool value) {}
void dummy_toggle_gpio_pin(const struct gpio_handle *handle) {}

const struct gpio_hal_handler mock_gpio_handler = {
    mock_init_gpio,
    dummy_deinit_gpio,
    dummy_read_gpio_pin,
    dummy_write_gpio_pin,
    dummy_toggle_gpio_pin
};

/* ---------------------------------------------------------------------------*/
/* IIC mock variables */
void mock_init_iic(void)
{
    /* IIC init must be called first */
    CHECK(!adc_initialized);
    CHECK(!clock_initialized);
    CHECK(!eic_initialized);
    CHECK(!gpio_initialized);
    CHECK(!pwm_initialized);
    CHECK(!tc_initialized);
    CHECK(!usart_initialized);
    iic_initialized = true;
}
void dummy_deinit_iic(void) {}
void dummy_enable_global_interrupts(void) {}
void dummy_disable_global_interrupts(void) {}

const struct iic_hal_handler mock_iic_handler = {
    mock_init_iic,
    dummy_deinit_iic,
    dummy_enable_global_interrupts,
    dummy_disable_global_interrupts
};

/* ---------------------------------------------------------------------------*/
/* PWM mock variables */
void mock_init_pwm(void)
{
    pwm_initialized = true;
}
void dummy_deinit_pwm(void) {}
void dummy_set_pwm_duty_cycle_percent(const struct pwm_handle *handle,
    uint32_t percent) {}

const struct pwm_hal_handler mock_pwm_handler = {
    mock_init_pwm,
    dummy_deinit_pwm,
    dummy_set_pwm_duty_cycle_percent
};

/* ---------------------------------------------------------------------------*/
/* timer counter mock variables */
void mock_init_tc(void)
{
    tc_initialized = true;
}
void dummy_deinit_timer_counter(void) {}
uint32_t dummy_get_timer_count(void) { return 0; }
void dummy_restart_timer(void) {}

const struct tc_hal_handler mock_tc_handler = {
    mock_init_tc,
    dummy_deinit_timer_counter,
    dummy_get_timer_count,
    dummy_restart_timer
};

/* ---------------------------------------------------------------------------*/
/* USART mock variables */
void mock_init_usart(void)
{
    usart_initialized = true;
}
void dummy_deinit_usart(void) {}

const struct usart_hal_handler mock_usart_handler = {
    mock_init_usart,
    dummy_deinit_usart
};

/*============================================================================*/
/*                                 Test Group                                 */
/*============================================================================*/
TEST_GROUP(ProcessorTests)
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
TEST(ProcessorTests, InitCallsFunctions)
{
    mock().expectOneCall("get_adc_hal_handler")
        .andReturnValue(&mock_adc_handler);
    mock().expectOneCall("get_clock_hal_handler")
        .andReturnValue(&mock_clock_handler);
    mock().expectOneCall("get_eic_hal_handler")
        .andReturnValue(&mock_eic_handler);
    mock().expectOneCall("get_gpio_hal_handler")
        .andReturnValue(&mock_gpio_handler);
    mock().expectOneCall("get_iic_hal_handler")
        .andReturnValue(&mock_iic_handler);
    mock().expectOneCall("get_pwm_hal_handler")
        .andReturnValue(&mock_pwm_handler);
    mock().expectOneCall("get_tc_hal_handler")
        .andReturnValue(&mock_tc_handler);
    mock().expectOneCall("get_usart_hal_handler")
        .andReturnValue(&mock_usart_handler);

    init_processor();

    CHECK(adc_initialized);
    CHECK(clock_initialized);
    CHECK(eic_initialized);
    CHECK(gpio_initialized);
    CHECK(iic_initialized);
    CHECK(pwm_initialized);
    CHECK(tc_initialized);
    CHECK(usart_initialized);
}
