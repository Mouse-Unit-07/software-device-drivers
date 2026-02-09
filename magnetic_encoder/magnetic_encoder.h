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
void init_magnetic_encoders(void);
void deinit_magnetic_encoders(void);
int32_t get_wheel_motor_1_encoder_ticks(void);
int32_t get_wheel_motor_2_encoder_ticks(void);
void clear_wheel_motor_1_encoder_ticks(void);
void clear_wheel_motor_2_encoder_ticks(void);

/* exposed for testing */
void wheel_motor_1_encoder_channel_a_isr(void);
void wheel_motor_2_encoder_channel_a_isr(void);

#endif /* MAGNETIC_ENCODER_H_ */
