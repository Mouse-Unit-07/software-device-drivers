/*-------------------------------- FILE INFO ---------------------------------*/
/* Filename           : wheel_motor.c                                           */
/*                                                                            */
/* Implementation for a wheel_motor device                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                               Include Files                                */
/*----------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "gpio_hal.h"
#include "gpio_hal_config.h"
#include "pwm_hal.h"
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

    gpio_handler->write_gpio_pin(wheel_driver_standby, true);
}

void deinit_wheel_motors(void)
{
    gpio_handler->write_gpio_pin(wheel_driver_standby, false);
    pwm_handler->set_pwm_duty_cycle_byte(wheel_motor_1, 0u);
    pwm_handler->set_pwm_duty_cycle_byte(wheel_motor_2, 0u);
    gpio_handler->write_gpio_pin(wheel_driver_motor_1_in1, false);
    gpio_handler->write_gpio_pin(wheel_driver_motor_1_in2, false);
    gpio_handler->write_gpio_pin(wheel_driver_motor_2_in1, false);
    gpio_handler->write_gpio_pin(wheel_driver_motor_2_in2, false);
}

bool is_current_limit_detection_asserted(void)
{
    return gpio_handler->read_gpio_pin(wheel_driver_cld);
}

void set_wheel_motor_1_speed(uint8_t speed)
{
    pwm_handler->set_pwm_duty_cycle_byte(wheel_motor_1, speed);
}

void set_wheel_motor_2_speed(uint8_t speed)
{
    pwm_handler->set_pwm_duty_cycle_byte(wheel_motor_2, speed);
}

void set_wheel_motor_1_direction_forward(void)
{
    gpio_handler->write_gpio_pin(wheel_driver_motor_1_in1, true);
    gpio_handler->write_gpio_pin(wheel_driver_motor_1_in2, false);
}

void set_wheel_motor_1_direction_backward(void)
{
    gpio_handler->write_gpio_pin(wheel_driver_motor_1_in1, false);
    gpio_handler->write_gpio_pin(wheel_driver_motor_1_in2, true);
}

void set_wheel_motor_2_direction_forward(void)
{
    gpio_handler->write_gpio_pin(wheel_driver_motor_2_in1, false);
    gpio_handler->write_gpio_pin(wheel_driver_motor_2_in2, true);
}

void set_wheel_motor_2_direction_backward(void)
{
    gpio_handler->write_gpio_pin(wheel_driver_motor_2_in1, true);
    gpio_handler->write_gpio_pin(wheel_driver_motor_2_in2, false);
}

/*----------------------------------------------------------------------------*/
/*                        Private Function Definitions                        */
/*----------------------------------------------------------------------------*/
/* none */
