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

/*----------------------------------------------------------------------------*/
/*                         Public Function Definitions                        */
/*----------------------------------------------------------------------------*/
void init_pushbutton(void)
{
    eic_handler = get_eic_hal_handler();
    config_pushbutton_eic = get_config_pushbutton_eic_handle();
    gpio_handler = get_gpio_hal_handler();
    config_pushbutton_gpio = get_config_pushbutton_gpio_handle();

    eic_handler->set_external_callback(config_pushbutton_eic, pushbutton_isr);
}

void deinit_pushbutton(void)
{

}

uint32_t get_pushbutton_count(void)
{
    return 0;
}

void clear_pushbutton_count(void)
{

}

/*----------------------------------------------------------------------------*/
/*                        Private Function Definitions                        */
/*----------------------------------------------------------------------------*/
void pushbutton_isr(void)
{

}
