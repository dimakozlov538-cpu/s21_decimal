#include "s21_decimal.h"

void set_scale(s21_decimal* value, int scale) {
    value->bits[3] &= ~DECIMAL_SCALE_MASK;
    value->bits[3] |= (scale << DECIMAL_SCALE_POS);
}