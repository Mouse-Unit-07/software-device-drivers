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
bool is_usart_rx_buffer_empty(void);
bool is_usart_rx_buffer_full(void);
char pop_usart_rx_buffer(void);
void clear_usart_rx_buffer(void);

#endif /* PROCESSOR_H_ */
