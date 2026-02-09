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
int32_t get_encoder_1_ticks(void);
int32_t get_encoder_2_ticks(void);
void clear_1_encoder_ticks(void);
void clear_2_encoder_ticks(void);

/* exposed for testing */
void encoder_1_isr(void);
void encoder_2_isr(void);

#endif /* MAGNETIC_ENCODER_H_ */
