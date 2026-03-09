/*-------------------------------- FILE INFO ---------------------------------*/
/* Filename           : wheel_motor.c                                           */
/*                                                                            */
/* Implementation for a wheel_motor device                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                               Include Files                                */
/*----------------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "gpio_hal_config.h"
#include "pwm_hal_config.h"
#include "wheel_motor.h"

/*----------------------------------------------------------------------------*/
/*                         Private Function Prototypes                        */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                               Private Globals                              */
/*----------------------------------------------------------------------------*/
static const struct pwm_hal_handler *pwm_handler = NULL;
static const struct pwm_handle *wheel_motor_1 = NULL;
static const struct pwm_handle *wheel_motor_2 = NULL;
static const struct gpio_hal_handler *gpio_handler = NULL;
static const struct gpio_handle *wheel_driver_standby = NULL;
static const struct gpio_handle *wheel_driver_cld = NULL;
static const struct gpio_handle *wheel_driver_motor_1_in1 = NULL;
static const struct gpio_handle *wheel_driver_motor_1_in2 = NULL;
static const struct gpio_handle *wheel_driver_motor_2_in1 = NULL;
static const struct gpio_handle *wheel_driver_motor_2_in2 = NULL;

/*----------------------------------------------------------------------------*/
/*                         Public Function Definitions                        */
/*----------------------------------------------------------------------------*/
void init_wheel_motors(void)
{
    pwm_handler = get_pwm_hal_handler();
    wheel_motor_1 = get_wheel_motor_1_handle();
    wheel_motor_2 = get_wheel_motor_2_handle();
    gpio_handler = get_gpio_hal_handler();
    wheel_driver_standby = get_wheel_driver_standby_handle();
    wheel_driver_cld = get_wheel_driver_cld_handle();
    wheel_driver_motor_1_in1 = get_wheel_driver_motor_1_in1_handle();
    wheel_driver_motor_1_in2 = get_wheel_driver_motor_1_in2_handle();
    wheel_driver_motor_2_in1 = get_wheel_driver_motor_2_in1_handle();
    wheel_driver_motor_2_in2 = get_wheel_driver_motor_2_in2_handle();
}

void deinit_wheel_motors(void)
{

}

void set_wheel_motor_1_speed(uint8_t speed)
{

}

void set_wheel_motor_2_speed(uint8_t speed)
{

}

void set_wheel_motor_1_direction_forward(void)
{

}

void set_wheel_motor_1_direction_backward(void)
{

}

void set_wheel_motor_2_direction_forward(void)
{

}

void set_wheel_motor_2_direction_backward(void)
{

}

/*----------------------------------------------------------------------------*/
/*                        Private Function Definitions                        */
/*----------------------------------------------------------------------------*/
/* none */
