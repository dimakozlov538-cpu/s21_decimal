#include "s21_decimal.h"

void set_sign(s21_decimal* value, int sign) {
    if (sign) {
        value->bits[3] |= DECIMAL_SIGN_MASK;
    } else {
        value->bits[3] &= ~DECIMAL_SIGN_MASK;
    }
}