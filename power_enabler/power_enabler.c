/*-------------------------------- FILE INFO ---------------------------------*/
/* Filename           : power_enabler.c                                       */
/*                                                                            */
/* Implementation for a power_enabler device                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                               Include Files                                */
/*----------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stddef.h>
#include "gpio_hal.h"
#include "gpio_hal_config.h"
#include "power_enabler.h"

/*----------------------------------------------------------------------------*/
/*                         Private Function Prototypes                        */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                               Private Globals                              */
/*----------------------------------------------------------------------------*/
static const struct gpio_hal_handler *gpio_handler = NULL;
static const struct gpio_handle *regulators_enable = NULL;

/*----------------------------------------------------------------------------*/
/*                         Public Function Definitions                        */
/*----------------------------------------------------------------------------*/
void init_power_enabler(void)
{
    gpio_handler = get_gpio_hal_handler();
    regulators_enable = get_regulators_enable_handle();
}

void deinit_power_enabler(void)
{
    /* nothing to clear/reset */
}

void enable_power(void)
{
    gpio_handler->write_gpio_pin(regulators_enable, true);
}

void disable_power(void)
{
    gpio_handler->write_gpio_pin(regulators_enable, false);
}

/*----------------------------------------------------------------------------*/
/*                        Private Function Definitions                        */
/*----------------------------------------------------------------------------*/
/* none */
