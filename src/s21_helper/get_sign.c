#include "s21_decimal.h"

int get_sign(s21_decimal value) {
    return (value.bits[3] & DECIMAL_SIGN_MASK) != 0;
}