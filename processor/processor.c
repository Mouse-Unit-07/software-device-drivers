/*-------------------------------- FILE INFO ---------------------------------*/
/* Filename           : processor.c                                           */
/*                                                                            */
/* Implementation for a processor device                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                               Include Files                                */
/*----------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stddef.h>
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

/*----------------------------------------------------------------------------*/
/*                         Private Function Prototypes                        */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                               Private Globals                              */
/*----------------------------------------------------------------------------*/
static const struct adc_hal_handler *adc_handler = NULL;
static const struct clock_hal_handler *clock_handler = NULL;
static const struct eic_hal_handler *eic_handler = NULL;
static const struct gpio_hal_handler *gpio_handler = NULL;
static const struct iic_hal_handler *iic_handler = NULL;
static const struct pwm_hal_handler *pwm_handler = NULL;
static const struct tc_hal_handler *tc_handler = NULL;
static const struct usart_hal_handler *usart_handler = NULL;

/*----------------------------------------------------------------------------*/
/*                         Public Function Definitions                        */
/*----------------------------------------------------------------------------*/
void init_processor(void)
{
    adc_handler = get_adc_hal_handler();
    clock_handler = get_clock_hal_handler();
    eic_handler = get_eic_hal_handler();
    gpio_handler = get_gpio_hal_handler();
    iic_handler = get_iic_hal_handler();
    pwm_handler = get_pwm_hal_handler();
    tc_handler = get_tc_hal_handler();
    usart_handler = get_usart_hal_handler();

    /* order of peripheral initialization is AT32UC3L0256 specific */
    iic_handler->disable_global_interrupts();

    iic_handler->init_iic();
    eic_handler->init_eic();
    clock_handler->init_clock();
    tc_handler->init_timer_counter();
    usart_handler->init_usart();
    gpio_handler->init_gpio();
    adc_handler->init_adc();
    pwm_handler->init_pwm();

    iic_handler->enable_global_interrupts();
}

void deinit_processor(void)
{
    pwm_handler->deinit_pwm();
    adc_handler->deinit_adc();
    gpio_handler->deinit_gpio();
    usart_handler->deinit_usart();
    tc_handler->deinit_timer_counter();
    clock_handler->deinit_clock();
    eic_handler->deinit_eic();
    iic_handler->deinit_iic();
}

void delay_ms(uint32_t delay_time)
{
    clock_handler->delay_ms(delay_time);
}

void delay_us(uint32_t delay_time)
{
    clock_handler->delay_us(delay_time);
}

void start_timer(void)
{
    tc_handler->restart_timer();
}

void reset_timer(void)
{
    tc_handler->restart_timer();
}

uint32_t get_current_time_ms(void)
{
    return tc_handler->get_timer_count();
}

uint32_t get_elapsed_time_ms(uint32_t start_time)
{
    uint32_t current_time = tc_handler->get_timer_count();

    if (start_time > current_time) {
        return 0;
    } else {
        return current_time - start_time;
    }
}

bool is_usart_rx_buffer_empty(void)
{
    return usart_handler->is_rx_buffer_empty();
}

bool is_usart_rx_buffer_full(void)
{
    return usart_handler->is_rx_buffer_full();
}

char pop_usart_rx_buffer(void)
{
    return usart_handler->pop_rx_buffer();
}

void clear_usart_rx_buffer(void)
{
    usart_handler->clear_rx_buffer();
}

/*----------------------------------------------------------------------------*/
/*                        Private Function Definitions                        */
/*----------------------------------------------------------------------------*/
/* none */
