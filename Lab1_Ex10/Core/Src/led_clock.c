/*
 * led_clock.c
 */
#include "led_clock.h"

#define LED_ON   GPIO_PIN_RESET   /* active-low */
#define LED_OFF  GPIO_PIN_SET

/* Bang tra: vi tri tren dong ho -> chan GPIO */
static const uint16_t CLOCK_PINS[CLOCK_LED_NUM] = {
    LED_0_Pin, LED_1_Pin, LED_2_Pin,  LED_3_Pin,
    LED_4_Pin, LED_5_Pin, LED_6_Pin,  LED_7_Pin,
    LED_8_Pin, LED_9_Pin, LED_10_Pin, LED_11_Pin
};

/* Mat na cua ca 12 chan (PA4..PA15) */
#define ALL_CLOCK_PINS  (LED_0_Pin | LED_1_Pin | LED_2_Pin  | LED_3_Pin |  \
                         LED_4_Pin | LED_5_Pin | LED_6_Pin  | LED_7_Pin |  \
                         LED_8_Pin | LED_9_Pin | LED_10_Pin | LED_11_Pin)

/* Exercise 7: tat ca 12 LED (1 lenh ghi BSRR cho ca 12 chan) */
void clearAllClock(void)
{
    HAL_GPIO_WritePin(LED_0_GPIO_Port, ALL_CLOCK_PINS, LED_OFF);
}

/* Exercise 8: bat LED o vi tri num (0..11); num sai -> bo qua */
void setNumberOnClock(int num)
{
    if (num < 0 || num >= CLOCK_LED_NUM) return;
    HAL_GPIO_WritePin(LED_0_GPIO_Port, CLOCK_PINS[num], LED_ON);
}

/* Exercise 9: tat LED o vi tri num (0..11); num sai -> bo qua */
void clearNumberOnClock(int num)
{
    if (num < 0 || num >= CLOCK_LED_NUM) return;
    HAL_GPIO_WritePin(LED_0_GPIO_Port, CLOCK_PINS[num], LED_OFF);
}
