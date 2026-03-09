/*-------------------------------- FILE INFO ---------------------------------*/
/* Filename           : pushbutton.h                                          */
/*                                                                            */
/* Interface for a pushbutton device                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

/*----------------------------------------------------------------------------*/
/*                             Public Definitions                             */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                         Public Function Prototypes                         */
/*----------------------------------------------------------------------------*/
void init_pushbutton(void);
void deinit_pushbutton(void);
uint32_t get_pushbutton_count(void);
void clear_pushbutton_count(void);

/* exposed for testing */
void pushbutton_isr(void);

#endif /* PUSHBUTTON_H_ */
