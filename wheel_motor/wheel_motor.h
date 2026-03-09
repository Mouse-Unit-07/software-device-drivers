/*-------------------------------- FILE INFO ---------------------------------*/
/* Filename           : wheel_motor.h                                         */
/*                                                                            */
/* Interface for a wheel_motor device                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef WHEEL_MOTOR_H_
#define WHEEL_MOTOR_H_

/*----------------------------------------------------------------------------*/
/*                             Public Definitions                             */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                         Public Function Prototypes                         */
/*----------------------------------------------------------------------------*/
void init_wheel_motors(void);
void deinit_wheel_motors(void);
bool is_current_limit_detection_asserted(void);
void set_wheel_motor_1_speed(uint8_t speed);
void set_wheel_motor_2_speed(uint8_t speed);
void set_wheel_motor_1_direction_forward(void);
void set_wheel_motor_1_direction_backward(void);
void set_wheel_motor_2_direction_forward(void);
void set_wheel_motor_2_direction_backward(void);

#endif /* WHEEL_MOTOR_H_ */
