/*
 * traffic.c
 *  Hien thuc den giao thong 4 huong bang 1 bien dem thoi gian (0..9 giay).
 */
#include "traffic.h"

#define LED_ON   GPIO_PIN_RESET   /* active-low */
#define LED_OFF  GPIO_PIN_SET

typedef struct {
    GPIO_TypeDef *port;
    uint16_t red, yellow, green;
} Direction;

/* 4 huong: 2 huong dau thuoc tuyen A, 2 huong sau thuoc tuyen B */
static const Direction DIRS[4] = {
    { GPIOA, N_RED_Pin, N_YELLOW_Pin, N_GREEN_Pin },   /* Bac  - tuyen A */
    { GPIOA, S_RED_Pin, S_YELLOW_Pin, S_GREEN_Pin },   /* Nam  - tuyen A */
    { GPIOA, E_RED_Pin, E_YELLOW_Pin, E_GREEN_Pin },   /* Dong - tuyen B */
    { GPIOA, W_RED_Pin, W_YELLOW_Pin, W_GREEN_Pin },   /* Tay  - tuyen B */
};

static uint8_t timeInCycle = 0;   /* 0 .. CYCLE_TIME-1 */

void traffic_init(void)
{
    timeInCycle = 0;
    traffic_update();
}

void traffic_tick_1s(void)
{
    timeInCycle++;
    if (timeInCycle >= CYCLE_TIME) timeInCycle = 0;
}

Light traffic_get_light(Road road)
{
    uint8_t t = timeInCycle;
    if (road == ROAD_A) {
        if (t < RED_TIME)                return LIGHT_RED;     /* 0..4 */
        if (t < RED_TIME + GREEN_TIME)   return LIGHT_GREEN;   /* 5..7 */
        return LIGHT_YELLOW;                                   /* 8..9 */
    } else {
        if (t < GREEN_TIME)              return LIGHT_GREEN;   /* 0..2 */
        if (t < GREEN_TIME + YELLOW_TIME)return LIGHT_YELLOW;  /* 3..4 */
        return LIGHT_RED;                                      /* 5..9 */
    }
}

uint8_t traffic_get_countdown(Road road)
{
    uint8_t t = timeInCycle;
    if (road == ROAD_A) {
        if (t < RED_TIME)                return RED_TIME - t;
        if (t < RED_TIME + GREEN_TIME)   return RED_TIME + GREEN_TIME - t;
        return CYCLE_TIME - t;
    } else {
        if (t < GREEN_TIME)              return GREEN_TIME - t;
        if (t < GREEN_TIME + YELLOW_TIME)return GREEN_TIME + YELLOW_TIME - t;
        return CYCLE_TIME - t;
    }
}

static void setDirection(const Direction *d, Light light)
{
    HAL_GPIO_WritePin(d->port, d->red,    (light == LIGHT_RED)    ? LED_ON : LED_OFF);
    HAL_GPIO_WritePin(d->port, d->yellow, (light == LIGHT_YELLOW) ? LED_ON : LED_OFF);
    HAL_GPIO_WritePin(d->port, d->green,  (light == LIGHT_GREEN)  ? LED_ON : LED_OFF);
}

void traffic_update(void)
{
    Light a = traffic_get_light(ROAD_A);
    Light b = traffic_get_light(ROAD_B);
    setDirection(&DIRS[0], a);
    setDirection(&DIRS[1], a);
    setDirection(&DIRS[2], b);
    setDirection(&DIRS[3], b);
}
