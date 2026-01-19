#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int status = 0;
    if (dst == NULL) {
        status = 1;
    } else {
        int sign = (src.bits[3] & 0x80000000U) ? -1 : 1;
        int exponent = (src.bits[3] >> 16) & 0xFF;

        if (exponent > 28) {
            *dst = 0;
            status = 0;
        } else {
            unsigned long long value = src.bits[0] +
                                      ((unsigned long long)src.bits[1] << 32) +
                                      ((unsigned long long)src.bits[2] << 64);

            for (int i = 0; i < exponent; ++i) {
                if (value == 0ULL) break;
                value /= 10ULL;
            }

            if (sign == 1) {
                if (value > (unsigned long long)INT_MAX) {
                    status = 2;
                }
            } else {
                if (value > (unsigned long long)INT_MAX + 1ULL) {
                    status = 2;
                }
            }

            if (status == 0) {
                *dst = (int)((long long)value * sign);
            }
        }
    }
    return status;
}