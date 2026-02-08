/*-------------------------------- FILE INFO ---------------------------------*/
/* Filename           : led.h                                                 */
/*                                                                            */
/* Interface for a led device                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef LED_H_
#define LED_H_

/*----------------------------------------------------------------------------*/
/*                             Public Definitions                             */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                         Public Function Prototypes                         */
/*----------------------------------------------------------------------------*/
void init_leds(void);
void deinit_leds(void);
void set_led_d1_enabled(bool enabled);
void set_led_d2_enabled(bool enabled);
void set_led_d3_enabled(bool enabled);
void set_led_d4_enabled(bool enabled);

#endif /* LED_H_ */
