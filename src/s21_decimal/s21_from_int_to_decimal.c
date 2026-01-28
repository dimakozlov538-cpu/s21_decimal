#include <limits.h>
#include <stddef.h>
#include <stdlib.h>

#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal* dst) {
    // Arguments check
    if (dst == NULL) {
        return S21_CONVERSION_ERROR;
    }

    unsigned int value = 0;

    if (src == INT_MIN) {
        value = (unsigned int)INT_MAX + 1;
    } else {
        value = abs(src);
    }
    dst->bits[0] = value;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = (src < 0) ? S21_SIGN_NEGATIVE : S21_SIGN_POSITIVE;

    return S21_CONVERSION_OK;
}