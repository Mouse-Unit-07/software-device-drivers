/*-------------------------------- FILE INFO ---------------------------------*/
/* Filename           : led.c                                                 */
/*                                                                            */
/* Implementation for a led device                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                               Include Files                                */
/*----------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stddef.h>
#include "gpio_hal.h"
#include "gpio_hal_config.h"
#include "led.h"

/*----------------------------------------------------------------------------*/
/*                         Private Function Prototypes                        */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                               Private Globals                              */
/*----------------------------------------------------------------------------*/
const struct gpio_hal_handler *gpio_handler = NULL;
const struct gpio_handle *led_d1 = NULL;
const struct gpio_handle *led_d2 = NULL;
const struct gpio_handle *led_d3 = NULL;
const struct gpio_handle *led_d4 = NULL;


/*----------------------------------------------------------------------------*/
/*                         Public Function Definitions                        */
/*----------------------------------------------------------------------------*/
void init_leds(void)
{
    gpio_handler = get_gpio_hal_handler();
    led_d1 = get_led_d1_handle();
    led_d2 = get_led_d2_handle();
    led_d3 = get_led_d3_handle();
    led_d4 = get_led_d4_handle();
}

void deinit_leds(void)
{
    /* nothing to clear/reset */
}

void set_led_d1_enabled(bool enabled)
{
    gpio_handler->write_gpio_pin(led_d1, enabled);
}

void set_led_d2_enabled(bool enabled)
{
    gpio_handler->write_gpio_pin(led_d2, enabled);
}

void set_led_d3_enabled(bool enabled)
{
    gpio_handler->write_gpio_pin(led_d3, enabled);
}

void set_led_d4_enabled(bool enabled)
{
    gpio_handler->write_gpio_pin(led_d4, enabled);
}

/*----------------------------------------------------------------------------*/
/*                        Private Function Definitions                        */
/*----------------------------------------------------------------------------*/
/* none */
