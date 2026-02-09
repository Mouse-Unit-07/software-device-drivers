/*-------------------------------- FILE INFO ---------------------------------*/
/* Filename           : magnetic_encoder.h                                    */
/*                                                                            */
/* Interface for a magnetic_encoder device                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef MAGNETIC_ENCODER_H_
#define MAGNETIC_ENCODER_H_

/*----------------------------------------------------------------------------*/
/*                             Public Definitions                             */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                         Public Function Prototypes                         */
/*----------------------------------------------------------------------------*/
void init_magnetic_encoder(void);
void deinit_magnetic_encoder(void);
int32_t get_wheel_motor_1_encoder_ticks(void);
int32_t get_wheel_motor_2_encoder_ticks(void);
void clear_wheel_motor_1_encoder_ticks(void);
void clear_wheel_motor_2_encoder_ticks(void);

#endif /* MAGNETIC_ENCODER_H_ */
