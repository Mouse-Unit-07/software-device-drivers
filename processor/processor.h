/*-------------------------------- FILE INFO ---------------------------------*/
/* Filename           : processor.h                                           */
/*                                                                            */
/* Interface for a processor device                                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef PROCESSOR_H_
#define PROCESSOR_H_

/*----------------------------------------------------------------------------*/
/*                             Public Definitions                             */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                         Public Function Prototypes                         */
/*----------------------------------------------------------------------------*/
void init_processor(void);
void deinit_processor(void);
void delay_ms(uint32_t delay_time);
void delay_us(uint32_t delay_time);
void start_timer(void);
void reset_timer(void);
uint32_t get_current_time_ms(void);
uint32_t get_elapsed_time_ms(uint32_t start_time);

#endif /* PROCESSOR_H_ */
