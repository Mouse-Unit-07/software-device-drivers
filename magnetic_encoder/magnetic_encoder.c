/*-------------------------------- FILE INFO ---------------------------------*/
/* Filename           : magnetic_encoder.c                                    */
/*                                                                            */
/* Implementation for a magnetic_encoder device                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                               Include Files                                */
/*----------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "eic_hal.h"
#include "eic_hal_config.h"
#include "gpio_hal.h"
#include "gpio_hal_config.h"
#include "magnetic_encoder.h"

/*----------------------------------------------------------------------------*/
/*                         Private Function Prototypes                        */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                               Private Globals                              */
/*----------------------------------------------------------------------------*/
static const struct eic_hal_handler *eic_handler = NULL;
static const struct gpio_hal_handler *gpio_handler = NULL;
static const struct gpio_handle *wheel_motor_1_encoder = NULL;
static const struct gpio_handle *wheel_motor_2_encoder = NULL;

/*----------------------------------------------------------------------------*/
/*                         Public Function Definitions                        */
/*----------------------------------------------------------------------------*/
void init_magnetic_encoder(void)
{
    eic_handler = get_eic_hal_handler();
    gpio_handler = get_gpio_hal_handler();
    wheel_motor_1_encoder = get_wheel_encoder_motor_1_b_channel_handle();
    wheel_motor_2_encoder = get_wheel_encoder_motor_2_b_channel_handle();
}

void deinit_magnetic_encoder(void)
{

}

int32_t get_motor_1_encoder_ticks(void)
{
    return 0;
}

int32_t get_motor_2_encoder_ticks(void)
{
    return 0;
}

void clear_motor_1_encoder_ticks(void)
{

}

void clear_motor_2_encoder_ticks(void)
{

}

/*----------------------------------------------------------------------------*/
/*                        Private Function Definitions                        */
/*----------------------------------------------------------------------------*/
/* none */
