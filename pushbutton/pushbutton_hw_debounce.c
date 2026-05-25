/*-------------------------------- FILE INFO ---------------------------------*/
/* Filename           : pushbutton_hw_debounce.c                              */
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

static volatile uint32_t pressed_count = 0u;

/*----------------------------------------------------------------------------*/
/*                         Public Function Definitions                        */
/*----------------------------------------------------------------------------*/
void init_pushbutton(void)
{
    eic_handler = get_eic_hal_handler();
    config_pushbutton_eic = get_config_pushbutton_eic_handle();

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
    pressed_count++;
}
