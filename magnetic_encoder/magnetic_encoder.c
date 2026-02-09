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
static const struct eic_handle *encoder_1_channel_a = NULL;
static const struct eic_handle *encoder_2_channel_a = NULL;
static const struct gpio_hal_handler *gpio_handler = NULL;
static const struct gpio_handle *encoder_1_channel_b = NULL;
static const struct gpio_handle *encoder_2_channel_b = NULL;

static volatile int32_t encoder_1_ticks = 0;
static volatile int32_t encoder_2_ticks = 0;

/*----------------------------------------------------------------------------*/
/*                         Public Function Definitions                        */
/*----------------------------------------------------------------------------*/
void init_magnetic_encoders(void)
{
    eic_handler = get_eic_hal_handler();
    encoder_1_channel_a = get_encoder_1_channel_a_handle();
    encoder_2_channel_a = get_encoder_2_channel_a_handle();
    gpio_handler = get_gpio_hal_handler();
    encoder_1_channel_b = get_encoder_1_channel_b_handle();
    encoder_2_channel_b = get_encoder_2_channel_b_handle();

    eic_handler->set_external_callback(encoder_1_channel_a, encoder_1_isr);
    eic_handler->set_external_callback(encoder_2_channel_a, encoder_2_isr);

    encoder_1_ticks = 0u;
    encoder_2_ticks = 0u;
}

void deinit_magnetic_encoders(void)
{

}

int32_t get_encoder_1_ticks(void)
{
    return encoder_1_ticks;
}

int32_t get_encoder_2_ticks(void)
{
    return encoder_2_ticks;
}

void clear_1_encoder_ticks(void)
{
    encoder_1_ticks = 0;
}

void clear_2_encoder_ticks(void)
{
    encoder_2_ticks = 0;
}

/*----------------------------------------------------------------------------*/
/*                        Private Function Definitions                        */
/*----------------------------------------------------------------------------*/
void encoder_1_isr(void)
{
    if (gpio_handler->read_gpio_pin(encoder_1_channel_b) == 0) {
        encoder_1_ticks++;
    } else {
        encoder_1_ticks--;
    }
}

void encoder_2_isr(void)
{
    if (gpio_handler->read_gpio_pin(encoder_2_channel_b) == 0) {
        encoder_2_ticks--;
    } else {
        encoder_2_ticks++;
    }
}
