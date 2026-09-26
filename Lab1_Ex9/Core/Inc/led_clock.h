/*
 * led_clock.h
 *  Dong ho kim 12 LED (Exercise 6 -> 10).
 *  LED so k (0..11) nam o vi tri "k gio" tren mat dong ho, noi vao PA(4+k):
 *     so 0 (12h) -> PA4, so 1 -> PA5, ..., so 11 -> PA15
 *  LED noi cathode vao chan MCU => muc 0 = SANG.
 */
#ifndef INC_LED_CLOCK_H_
#define INC_LED_CLOCK_H_

#include "main.h"

#define CLOCK_LED_NUM   12

void clearAllClock(void);                 /* Exercise 7 */
void setNumberOnClock(int num);           /* Exercise 8 */
void clearNumberOnClock(int num);         /* Exercise 9 */

#endif /* INC_LED_CLOCK_H_ */
