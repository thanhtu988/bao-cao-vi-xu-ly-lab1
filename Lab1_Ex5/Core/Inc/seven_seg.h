/*
 * seven_seg.h
 *  Driver LED 7 doan loai CHUNG ANODE (7SEG-COM-ANODE).
 *  - Chan chung (COM) noi nguon +3.3V
 *  - Doan a..g noi PB0..PB6  => muon SANG 1 doan thi xuat muc 0 (RESET)
 */
#ifndef INC_SEVEN_SEG_H_
#define INC_SEVEN_SEG_H_

#include "main.h"

/* Hien thi so num (0..9) len LED 7 doan. num ngoai khoang -> tat het. */
void display7SEG(int num);

#endif /* INC_SEVEN_SEG_H_ */
