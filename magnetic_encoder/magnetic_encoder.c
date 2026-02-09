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
void wheel_motor_1_encoder_channel_a_isr(void);
void wheel_motor_2_encoder_channel_a_isr(void);

/*----------------------------------------------------------------------------*/
/*                               Private Globals                              */
/*----------------------------------------------------------------------------*/
static const struct eic_hal_handler *eic_handler = NULL;
static const struct eic_handle *wheel_motor_1_encoder_channel_a = NULL;
static const struct eic_handle *wheel_motor_2_encoder_channel_a = NULL;
static const struct gpio_hal_handler *gpio_handler = NULL;
static const struct gpio_handle *wheel_motor_1_encoder_channel_b = NULL;
static const struct gpio_handle *wheel_motor_2_encoder_channel_b = NULL;

/*----------------------------------------------------------------------------*/
/*                         Public Function Definitions                        */
/*----------------------------------------------------------------------------*/
void init_magnetic_encoders(void)
{
    eic_handler = get_eic_hal_handler();
    wheel_motor_1_encoder_channel_a = get_motor_1_encoder_handle();
    wheel_motor_2_encoder_channel_a = get_motor_2_encoder_handle();
    gpio_handler = get_gpio_hal_handler();
    wheel_motor_1_encoder_channel_b = get_wheel_encoder_motor_1_b_channel_handle();
    wheel_motor_2_encoder_channel_b = get_wheel_encoder_motor_2_b_channel_handle();

    eic_handler->set_external_callback(wheel_motor_1_encoder_channel_a, wheel_motor_1_encoder_channel_a_isr);
    eic_handler->set_external_callback(wheel_motor_2_encoder_channel_a, wheel_motor_2_encoder_channel_a_isr);
}

void deinit_magnetic_encoders(void)
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
void wheel_motor_1_encoder_channel_a_isr(void)
{

}

void wheel_motor_2_encoder_channel_a_isr(void)
{

}
