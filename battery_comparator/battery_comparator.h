/*-------------------------------- FILE INFO ---------------------------------*/
/* Filename           : battery_comparator.h                                  */
/*                                                                            */
/* Interface for a battery_comparator device                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef BATTERY_COMPARATOR_H_
#define BATTERY_COMPARATOR_H_

/*----------------------------------------------------------------------------*/
/*                             Public Definitions                             */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                         Public Function Prototypes                         */
/*----------------------------------------------------------------------------*/
void init_battery_comparator(void);
void deinit_battery_comparator(void);
bool is_battery_low(void);

#endif /* BATTERY_COMPARATOR_H_ */
