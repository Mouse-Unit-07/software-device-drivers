/*-------------------------------- FILE INFO ---------------------------------*/
/* Filename           : battery_comparator.c                                  */
/*                                                                            */
/* Implementation for a battery_comparator device                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                               Include Files                                */
/*----------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stddef.h>
#include "gpio_hal.h"
#include "gpio_hal_config.h"
#include "battery_comparator.h"

/*----------------------------------------------------------------------------*/
/*                         Private Function Prototypes                        */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                               Private Globals                              */
/*----------------------------------------------------------------------------*/
static const struct gpio_hal_handler *gpio_handler = NULL;
static const struct gpio_handle *battery_comparator = NULL;

/*----------------------------------------------------------------------------*/
/*                         Public Function Definitions                        */
/*----------------------------------------------------------------------------*/
void init_battery_comparator(void)
{
    gpio_handler = get_gpio_hal_handler();
    battery_comparator = get_battery_comparator_handle();
}

void deinit_battery_comparator(void)
{
    /* nothing to reset/clear */
}

bool is_battery_low(void)
{
    return (gpio_handler->read_gpio_pin(battery_comparator) == 0);
}

/*----------------------------------------------------------------------------*/
/*                        Private Function Definitions                        */
/*----------------------------------------------------------------------------*/
/* none */
