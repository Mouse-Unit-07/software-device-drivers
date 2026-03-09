/*-------------------------------- FILE INFO ---------------------------------*/
/* Filename           : pushbutton.c                                          */
/*                                                                            */
/* Implementation for a pushbutton device                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                               Include Files                                */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/*                         Private Function Prototypes                        */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                               Private Globals                              */
/*----------------------------------------------------------------------------*/
static const struct eic_hal_handler *eic_handler = NULL;
static const struct eic_handle *config_pushbutton_eic = NULL;
static const struct gpio_hal_handler *gpio_handler = NULL;
static const struct gpio_handle *config_pushbutton_gpio = NULL;
static const struct clock_hal_handler *clock_handler = NULL;

static volatile uint32_t pressed_count = 0u;

/*----------------------------------------------------------------------------*/
/*                         Public Function Definitions                        */
/*----------------------------------------------------------------------------*/
void init_pushbutton(void)
{
    eic_handler = get_eic_hal_handler();
    config_pushbutton_eic = get_config_pushbutton_eic_handle();
    gpio_handler = get_gpio_hal_handler();
    config_pushbutton_gpio = get_config_pushbutton_gpio_handle();
    clock_handler = get_clock_hal_handler();

    eic_handler->set_external_callback(config_pushbutton_eic, pushbutton_isr);
}

void deinit_pushbutton(void)
{
    pressed_count = 0u;
}

uint32_t get_pushbutton_count(void)
{
    return pressed_count;
}

void clear_pushbutton_count(void)
{
    pressed_count = 0u;
}

/*----------------------------------------------------------------------------*/
/*                        Private Function Definitions                        */
/*----------------------------------------------------------------------------*/
void pushbutton_isr(void)
{
    /* ...provided no OS, and no timer counter or main loop dedicated to */
    /* polling the pushbutton, debouncing w/ hardware is the best choice. */
    /* for now, we have the below horrible loop and delays: */
    const uint32_t BOUNCE_TIME_MS = 10u;

    clock_handler->delay_ms(BOUNCE_TIME_MS);

    while (gpio_handler->read_gpio_pin(config_pushbutton_gpio) == false) {
        /* given default HIGH from pull-up, wait for release back to HIGH */
    }

    clock_handler->delay_ms(BOUNCE_TIME_MS);

    pressed_count++;
}
