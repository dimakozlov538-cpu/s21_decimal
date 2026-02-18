#include "s21_decimal.h"

void decimal_to_big(big_decimal* big, s21_decimal value) {
    for (int i = 0; i < 8; i++) {
        big->bits[i] = 0;
    }
    big->bits[0] = value.bits[0];
    big->bits[1] = value.bits[1];
    big->bits[2] = value.bits[2];
    big->scale = get_scale(value);
    big->sign = get_sign(value);
}