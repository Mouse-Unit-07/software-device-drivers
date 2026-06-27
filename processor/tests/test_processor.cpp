/*================================ FILE INFO =================================*/
/* Filename           : test_processor.cpp                                    */
/*                                                                            */
/* Test implementation for processor.c                                        */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                               Include Files                                */
/*============================================================================*/
extern "C"
{

#include <stdbool.h>
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
            mock().actualCall("get_adc_hal_handler").returnConstPointerValue());
}

const struct clock_hal_handler *get_clock_hal_handler(void)
{
    return static_cast<const struct clock_hal_handler *>(
            mock().actualCall("get_clock_hal_handler").returnConstPointerValue());
}

const struct eic_hal_handler *get_eic_hal_handler(void)
{
    return static_cast<const struct eic_hal_handler *>(
            mock().actualCall("get_eic_hal_handler").returnConstPointerValue());
}

const struct gpio_hal_handler *get_gpio_hal_handler(void)
{
    return static_cast<const struct gpio_hal_handler *>(
            mock().actualCall("get_gpio_hal_handler").returnConstPointerValue());
}

const struct iic_hal_handler *get_iic_hal_handler(void)
{
    return static_cast<const struct iic_hal_handler *>(
            mock().actualCall("get_iic_hal_handler").returnConstPointerValue());
}

const struct pwm_hal_handler *get_pwm_hal_handler(void)
{
    return static_cast<const struct pwm_hal_handler *>(
            mock().actualCall("get_pwm_hal_handler").returnConstPointerValue());
}

const struct tc_hal_handler *get_tc_hal_handler(void)
{
    return static_cast<const struct tc_hal_handler *>(
            mock().actualCall("get_tc_hal_handler").returnConstPointerValue());
}

const struct usart_hal_handler *get_usart_hal_handler(void)
{
    return static_cast<const struct usart_hal_handler *>(
            mock().actualCall("get_usart_hal_handler").returnConstPointerValue());
}

/*============================================================================*/
/*                             Public Definitions                             */
/*============================================================================*/
/* test flags */
bool adc_initialized{false};
bool clock_initialized{false};
bool eic_initialized{false};
bool gpio_initialized{false};
bool iic_initialized{false};
bool pwm_initialized{false};
bool tc_initialized{false};
bool usart_initialized{false};

bool delay_ms_called{false};
bool delay_us_called{false};
bool restart_timer_called{false};
bool get_timer_count_called{false};
bool enable_global_interrupts_called{false};
bool disable_global_interrupts_called{false};
bool is_rx_buffer_empty_called{false};
bool is_rx_buffer_full_called{false};
bool pop_rx_buffer_called{false};
bool clear_rx_buffer_called{false};

void reset_test_flags(void)
{
    adc_initialized = false;
    clock_initialized = false;
    eic_initialized = false;
    gpio_initialized = false;
    iic_initialized = false;
    pwm_initialized = false;
    tc_initialized = false;
    usart_initialized = false;

    delay_ms_called = false;
    delay_us_called = false;
    restart_timer_called = false;
    get_timer_count_called = false;
    enable_global_interrupts_called = false;
    disable_global_interrupts_called = false;
    is_rx_buffer_empty_called = false;
    is_rx_buffer_full_called = false;
    pop_rx_buffer_called = false;
    clear_rx_buffer_called = false;
}

/* -------------------------------------------------------------------------- */
/* ADC mocks */
void mock_init_adc(void)
{
    adc_initialized = true;
}
void mock_deinit_adc(void)
{
    adc_initialized = false;
}
uint32_t dummy_read_adc_channel(const struct adc_handle *handle) { return 0; }

const struct adc_hal_handler mock_adc_handler = {
        mock_init_adc,
        mock_deinit_adc,
        dummy_read_adc_channel};

/* -------------------------------------------------------------------------- */
/* clock mocks */
void mock_init_clock(void)
{
    clock_initialized = true;
}
void mock_deinit_clock(void)
{
    clock_initialized = false;
}
void mock_delay_ms(uint32_t delay_time)
{
    delay_ms_called = true;
}
void mock_delay_us(uint32_t delay_time)
{
    delay_us_called = true;
}

const struct clock_hal_handler mock_clock_handler = {
        mock_init_clock,
        mock_deinit_clock,
        mock_delay_ms,
        mock_delay_us};

/* -------------------------------------------------------------------------- */
/* EIC mocks */
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
void mock_deinit_eic(void)
{
    eic_initialized = false;
}
void dummy_set_external_callback(const struct eic_handle *handle, void (*callback)(void)) {}

const struct eic_hal_handler mock_eic_handler = {
        mock_init_eic,
        mock_deinit_eic,
        dummy_set_external_callback};

/* -------------------------------------------------------------------------- */
/* GPIO mocks */
void mock_init_gpio(void)
{
    gpio_initialized = true;
}
void mock_deinit_gpio(void)
{
    gpio_initialized = false;
}
bool dummy_read_gpio_pin(const struct gpio_handle *handle) { return true; }
void dummy_write_gpio_pin(const struct gpio_handle *handle, bool value) {}
void dummy_toggle_gpio_pin(const struct gpio_handle *handle) {}

const struct gpio_hal_handler mock_gpio_handler = {
        mock_init_gpio,
        mock_deinit_gpio,
        dummy_read_gpio_pin,
        dummy_write_gpio_pin,
        dummy_toggle_gpio_pin};

/* -------------------------------------------------------------------------- */
/* IIC mocks */
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
void mock_deinit_iic(void)
{
    iic_initialized = false;
}
void mock_enable_global_interrupts(void)
{
    enable_global_interrupts_called = true;
}

void mock_disable_global_interrupts(void)
{
    disable_global_interrupts_called = true;
}

const struct iic_hal_handler mock_iic_handler = {
        mock_init_iic,
        mock_deinit_iic,
        mock_enable_global_interrupts,
        mock_disable_global_interrupts};

/* -------------------------------------------------------------------------- */
/* PWM mocks */
void mock_init_pwm(void)
{
    pwm_initialized = true;
}
void mock_deinit_pwm(void)
{
    pwm_initialized = false;
}
void dummy_set_pwm_duty_cycle_byte(const struct pwm_handle *handle, uint8_t duty_cycle) {}

const struct pwm_hal_handler mock_pwm_handler = {
        mock_init_pwm,
        mock_deinit_pwm,
        dummy_set_pwm_duty_cycle_byte};

/* -------------------------------------------------------------------------- */
/* timer counter mocks */
void mock_init_tc(void)
{
    tc_initialized = true;
}
void mock_deinit_timer_counter(void)
{
    tc_initialized = false;
}
uint32_t mock_get_timer_count(void)
{
    get_timer_count_called = true;
    return 0;
}
void mock_restart_timer(void)
{
    restart_timer_called = true;
}

const struct tc_hal_handler mock_tc_handler = {
        mock_init_tc,
        mock_deinit_timer_counter,
        mock_get_timer_count,
        mock_restart_timer};

/* -------------------------------------------------------------------------- */
/* USART mocks */
void mock_init_usart(void)
{
    usart_initialized = true;
}
void mock_deinit_usart(void)
{
    usart_initialized = false;
}
bool mock_is_rx_buffer_empty(void)
{
    is_rx_buffer_empty_called = true;
    return false;
}
bool mock_is_rx_buffer_full(void)
{
    is_rx_buffer_full_called = true;
    return false;
}
char mock_pop_rx_buffer(void)
{
    pop_rx_buffer_called = true;
    return '\0';
}
void mock_clear_rx_buffer(void)
{
    clear_rx_buffer_called = true;
}

const struct usart_hal_handler mock_usart_handler = {
        mock_init_usart,
        mock_deinit_usart,
        mock_is_rx_buffer_empty,
        mock_is_rx_buffer_full,
        mock_pop_rx_buffer,
        mock_clear_rx_buffer};

/* -------------------------------------------------------------------------- */
/* test helpers */
void init_processor_with_cpputest_checks(void)
{
    mock().expectOneCall("get_adc_hal_handler").andReturnValue(&mock_adc_handler);
    mock().expectOneCall("get_clock_hal_handler").andReturnValue(&mock_clock_handler);
    mock().expectOneCall("get_eic_hal_handler").andReturnValue(&mock_eic_handler);
    mock().expectOneCall("get_gpio_hal_handler").andReturnValue(&mock_gpio_handler);
    mock().expectOneCall("get_iic_hal_handler").andReturnValue(&mock_iic_handler);
    mock().expectOneCall("get_pwm_hal_handler").andReturnValue(&mock_pwm_handler);
    mock().expectOneCall("get_tc_hal_handler").andReturnValue(&mock_tc_handler);
    mock().expectOneCall("get_usart_hal_handler").andReturnValue(&mock_usart_handler);

    init_processor();

    CHECK(adc_initialized);
    CHECK(clock_initialized);
    CHECK(eic_initialized);
    CHECK(gpio_initialized);
    CHECK(iic_initialized);
    CHECK(pwm_initialized);
    CHECK(tc_initialized);
    CHECK(usart_initialized);

    CHECK(disable_global_interrupts_called);
    CHECK(enable_global_interrupts_called);
}

/*============================================================================*/
/*                                 Test Group                                 */
/*============================================================================*/
TEST_GROUP(ProcessorTests)
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
TEST(ProcessorTests, InitCallsFunctions)
{
    init_processor_with_cpputest_checks();
}

TEST(ProcessorTests, DeinitCallsFunctions)
{
    init_processor_with_cpputest_checks();
    deinit_processor();
    CHECK_FALSE(adc_initialized);
    CHECK_FALSE(clock_initialized);
    CHECK_FALSE(eic_initialized);
    CHECK_FALSE(gpio_initialized);
    CHECK_FALSE(iic_initialized);
    CHECK_FALSE(pwm_initialized);
    CHECK_FALSE(tc_initialized);
    CHECK_FALSE(usart_initialized);
}

TEST(ProcessorTests, DelayMsCallsFunction)
{
    init_processor_with_cpputest_checks();
    delay_ms(2000);
    CHECK(delay_ms_called);
}

TEST(ProcessorTests, DelayUsCallsFunction)
{
    init_processor_with_cpputest_checks();
    delay_us(2000);
    CHECK(delay_us_called);
}

TEST(ProcessorTests, StartTimerCallsFunctions)
{
    init_processor_with_cpputest_checks();
    start_timer();
    CHECK(restart_timer_called);
}

TEST(ProcessorTests, ResetTimerCallsFunctions)
{
    init_processor_with_cpputest_checks();
    reset_timer();
    CHECK(restart_timer_called);
}

TEST(ProcessorTests, GetCurrentTimeCallsFunctions)
{
    init_processor_with_cpputest_checks();
    get_current_time_ms();
    CHECK(get_timer_count_called);
}

TEST(ProcessorTests, GetElapsedTimeCallsFunctions)
{
    init_processor_with_cpputest_checks();
    get_elapsed_time_ms(2000);
    CHECK(get_timer_count_called);
}

TEST(ProcessorTests, IsUsartRxBufferEmptyCallsFunctions)
{
    init_processor_with_cpputest_checks();
    is_usart_rx_buffer_empty();
    CHECK(is_rx_buffer_empty_called);
}

TEST(ProcessorTests, IsUsartRxBufferFullCallsFunctions)
{
    init_processor_with_cpputest_checks();
    is_usart_rx_buffer_full();
    CHECK(is_rx_buffer_full_called);
}

TEST(ProcessorTests, PopUsartRxBufferCallsFunctions)
{
    init_processor_with_cpputest_checks();
    pop_usart_rx_buffer();
    CHECK(pop_rx_buffer_called);
}

TEST(ProcessorTests, ClearUsartRxBufferCallsFunctions)
{
    init_processor_with_cpputest_checks();
    clear_usart_rx_buffer();
    CHECK(clear_rx_buffer_called);
}
