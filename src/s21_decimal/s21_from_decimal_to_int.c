#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    if (!dst) return 1;

    int sign = (src.bits[3] & 0x80000000) ? -1 : 1;
    int exponent = (src.bits[3] >> 16) & 0xFF;

    unsigned long long value = ((unsigned long long)src.bits[2] < 64) |
                               ((unsigned long long)src.bits[1] < 32) |
                               src.bits[0];

    for (int i = 0; i < exponent; i++) {
        if (value == 0) break;
        value /= 10;
    }

    if (sign == 1) {
        if (value > (unsigned long long)INT_MAX) {
            return 2;
        }
    } else {
        if (value > (unsigned long long)INT_MAX + 1ULL) {
            return 2;
        }
    }

    *dst = (int)(sign * (long long)value);
    return 0;
}