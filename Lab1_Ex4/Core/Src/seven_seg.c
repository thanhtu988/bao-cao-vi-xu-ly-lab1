/*
 * seven_seg.c
 *  Ham display7SEG cho Exercise 4, dung lai o Exercise 5.
 */
#include "seven_seg.h"

/* Chan cua tung doan, theo thu tu bit: bit0 = a, bit1 = b, ..., bit6 = g */
static const uint16_t SEG_PINS[7] = {
    SEG_A_Pin, SEG_B_Pin, SEG_C_Pin, SEG_D_Pin, SEG_E_Pin, SEG_F_Pin, SEG_G_Pin
};

/* Bang ma cho so 0..9, bit = 1 nghia la doan do SANG (logic duong, dang gfedcba) */
static const uint8_t DIGIT_CODE[10] = {
    0x3F, /* 0: a b c d e f   */
    0x06, /* 1:   b c         */
    0x5B, /* 2: a b   d e   g */
    0x4F, /* 3: a b c d     g */
    0x66, /* 4:   b c     f g */
    0x6D, /* 5: a   c d   f g */
    0x7D, /* 6: a   c d e f g */
    0x07, /* 7: a b c         */
    0x7F, /* 8: a b c d e f g */
    0x6F  /* 9: a b c d   f g */
};

void display7SEG(int num)
{
    uint8_t code = 0x00;                 /* mac dinh: tat het */
    if (num >= 0 && num <= 9) {
        code = DIGIT_CODE[num];
    }

    uint16_t onPins  = 0;                /* cac doan can sang -> muc 0 */
    uint16_t offPins = 0;                /* cac doan can tat  -> muc 1 */
    for (int i = 0; i < 7; i++) {
        if (code & (1u << i)) onPins  |= SEG_PINS[i];
        else                  offPins |= SEG_PINS[i];
    }

    /* Chung anode => active-low */
    if (offPins) HAL_GPIO_WritePin(SEG_A_GPIO_Port, offPins, GPIO_PIN_SET);
    if (onPins)  HAL_GPIO_WritePin(SEG_A_GPIO_Port, onPins,  GPIO_PIN_RESET);
}
