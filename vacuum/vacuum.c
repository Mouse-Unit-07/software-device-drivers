/*-------------------------------- FILE INFO ---------------------------------*/
/* Filename           : vacuum.c                                              */
/*                                                                            */
/* Implementation for a vacuum device                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                               Include Files                                */
/*----------------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "pwm_hal.h"
#include "pwm_hal_config.h"
#include "vacuum.h"

/*----------------------------------------------------------------------------*/
/*                         Private Function Prototypes                        */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                               Private Globals                              */
/*----------------------------------------------------------------------------*/
static const struct pwm_hal_handler *pwm_handler = NULL;
static const struct pwm_handle *vacuum_motor = NULL;

/*----------------------------------------------------------------------------*/
/*                         Public Function Definitions                        */
/*----------------------------------------------------------------------------*/
void init_vacuum(void)
{
    pwm_handler = get_pwm_hal_handler();
    vacuum_motor = get_vacuum_motor_handle();
}

void deinit_vacuum(void)
{
    pwm_handler->set_pwm_duty_cycle_byte(vacuum_motor, 0u);
}

void set_vacuum_speed(uint8_t speed)
{
    pwm_handler->set_pwm_duty_cycle_byte(vacuum_motor, speed);
}

/*----------------------------------------------------------------------------*/
/*                        Private Function Definitions                        */
/*----------------------------------------------------------------------------*/
/* none */
