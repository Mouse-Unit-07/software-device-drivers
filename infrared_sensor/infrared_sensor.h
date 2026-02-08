/*-------------------------------- FILE INFO ---------------------------------*/
/* Filename           : infrared_sensor.h                                     */
/*                                                                            */
/* Interface for a infrared_sensor device                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef INFRARED_SENSOR_H_
#define INFRARED_SENSOR_H_

/*----------------------------------------------------------------------------*/
/*                             Public Definitions                             */
/*----------------------------------------------------------------------------*/
void init_infrared_sensors(void);
void deinit_infrared_sensors(void);
uint32_t read_ir_1_sensor(void);
uint32_t read_ir_2_sensor(void);
uint32_t read_ir_3_sensor(void);
uint32_t read_ir_4_sensor(void);

/*----------------------------------------------------------------------------*/
/*                         Public Function Prototypes                         */
/*----------------------------------------------------------------------------*/

#endif /* INFRARED_SENSOR_H_ */
