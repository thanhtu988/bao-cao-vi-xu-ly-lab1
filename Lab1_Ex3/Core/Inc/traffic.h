/*
 * traffic.h
 *  Den giao thong nga tu (4 huong x 3 den = 12 LED), Exercise 3 & 5.
 *
 *  Tuyen A = Bac (NORTH) + Nam (SOUTH)   -> 2 huong nay luon cung trang thai
 *  Tuyen B = Dong (EAST) + Tay (WEST)
 *
 *  Thoi gian (theo de): DO 5s, VANG 2s, XANH 3s  => chu ky 10s
 *
 *   t (s)   : 0 1 2 | 3 4 | 5 6 7 | 8 9
 *   Tuyen A : DO  DO  DO  | DO DO | XANH  | VANG
 *   Tuyen B : XANH......  | VANG  | DO .........
 *
 *  LED noi kieu cathode vao chan MCU (anode len +3.3V) => muc 0 = SANG.
 */
#ifndef INC_TRAFFIC_H_
#define INC_TRAFFIC_H_

#include "main.h"

#define RED_TIME      5
#define YELLOW_TIME   2
#define GREEN_TIME    3
#define CYCLE_TIME    (RED_TIME + YELLOW_TIME + GREEN_TIME)   /* = 10 s */

typedef enum { ROAD_A = 0, ROAD_B = 1 } Road;
typedef enum { LIGHT_RED = 0, LIGHT_YELLOW, LIGHT_GREEN } Light;

void    traffic_init(void);              /* ve thoi diem t = 0 */
void    traffic_update(void);            /* xuat trang thai hien tai ra 12 LED */
void    traffic_tick_1s(void);           /* tang thoi gian them 1 giay */
Light   traffic_get_light(Road road);    /* den dang sang cua tuyen */
uint8_t traffic_get_countdown(Road road);/* so giay con lai cua den hien tai */

#endif /* INC_TRAFFIC_H_ */
