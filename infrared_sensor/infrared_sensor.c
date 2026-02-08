/*-------------------------------- FILE INFO ---------------------------------*/
/* Filename           : infrared_sensor.c                                     */
/*                                                                            */
/* Implementation for a infrared_sensor device                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                               Include Files                                */
/*----------------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "adc_hal.h"
#include "adc_hal_config.h"
#include "infrared_sensor.h"
/*----------------------------------------------------------------------------*/
/*                         Private Function Prototypes                        */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                               Private Globals                              */
/*----------------------------------------------------------------------------*/
static const struct adc_hal_handler *adc_handler = NULL;
static const struct adc_handle *ir_sensor_1 = NULL;
static const struct adc_handle *ir_sensor_2 = NULL;
static const struct adc_handle *ir_sensor_3 = NULL;
static const struct adc_handle *ir_sensor_4 = NULL;

/*----------------------------------------------------------------------------*/
/*                         Public Function Definitions                        */
/*----------------------------------------------------------------------------*/
void init_infrared_sensors(void)
{
    adc_handler = get_adc_hal_handler();
    ir_sensor_1 = get_ir_sensor_1_handle();
    ir_sensor_2 = get_ir_sensor_2_handle();
    ir_sensor_3 = get_ir_sensor_3_handle();
    ir_sensor_4 = get_ir_sensor_4_handle();
}

void deinit_infrared_sensors(void)
{

}

uint32_t read_ir_1_sensor(void)
{
    return adc_handler->read_adc_channel(ir_sensor_1);
}

uint32_t read_ir_2_sensor(void)
{
    return adc_handler->read_adc_channel(ir_sensor_2);
}

uint32_t read_ir_3_sensor(void)
{
    return adc_handler->read_adc_channel(ir_sensor_3);
}

uint32_t read_ir_4_sensor(void)
{
    return adc_handler->read_adc_channel(ir_sensor_4);
}

/*----------------------------------------------------------------------------*/
/*                        Private Function Definitions                        */
/*----------------------------------------------------------------------------*/
/* none */
