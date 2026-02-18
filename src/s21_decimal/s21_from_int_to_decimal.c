#include "s21_decimal.h"
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int s21_from_int_to_decimal(int src, s21_decimal* dst) {
    if (dst == NULL) {
        return 1;
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
    dst->bits[3] = (src < 0) ? 1u << 31 : 0;
    return 0;
}