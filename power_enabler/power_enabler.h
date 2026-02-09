/*-------------------------------- FILE INFO ---------------------------------*/
/* Filename           : power_enabler.h                                       */
/*                                                                            */
/* Interface for a power_enabler device                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef POWER_ENABLER_H_
#define POWER_ENABLER_H_

/*----------------------------------------------------------------------------*/
/*                             Public Definitions                             */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                         Public Function Prototypes                         */
/*----------------------------------------------------------------------------*/
void init_power_enabler(void);
void deinit_power_enabler(void);
void enable_power(void);
void disable_power(void);

#endif /* POWER_ENABLER_H_ */
