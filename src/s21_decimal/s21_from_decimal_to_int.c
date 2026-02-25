#include "s21_decimal.h"
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    if (!dst)
        return 1;

    int error = 0;
    *dst = 0;

    int scale = (src.bits[3] >> 16) & 0xFF;
    int sign = (src.bits[3] >> 31) & 1;

    if (scale > 28)
        error = 1;

    unsigned int lo = src.bits[0];
    unsigned int mid = src.bits[1];
    unsigned int hi = src.bits[2];

    if (!error) {
        for (int i = 0; i < scale; i++) {
            unsigned long long temp;

            temp = hi % 10;
            hi /= 10;

            temp = (temp << 32) | mid;
            mid = temp / 10;
            temp %= 10;

            temp = (temp << 32) | lo;
            lo = temp / 10;
        }

        if (hi != 0)
            error = 1;

        if (!error && lo > (unsigned int)INT_MAX + sign)
            error = 1;

        if (!error)
            *dst = sign ? -(int)lo : (int)lo;
    }

    return error;
}