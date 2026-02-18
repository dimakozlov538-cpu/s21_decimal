#include "s21_decimal.h"

int get_scale(s21_decimal value) {
    return (value.bits[3] & DECIMAL_SCALE_MASK) >> DECIMAL_SCALE_POS;
}