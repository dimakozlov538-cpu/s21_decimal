#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int status = 0;

  if (dst == NULL) {
    status = 1;
  } else {
    unsigned int bits3 = src.bits[3];
    int scale = (bits3 >> 16) & 0xFF;
    int sign = (bits3 >> 31) & 1;

    if (scale > 28) {
      status = 1;
      *dst = 0;
    } else {
      double mantissa = (double)src.bits[0] + ldexp((double)src.bits[1], 32) +
                        ldexp((double)src.bits[2], 64);

      static const double pow10[] = {
          1e0,  1e1,  1e2,  1e3,  1e4,  1e5,  1e6,  1e7,  1e8,  1e9,
          1e10, 1e11, 1e12, 1e13, 1e14, 1e15, 1e16, 1e17, 1e18, 1e19,
          1e20, 1e21, 1e22, 1e23, 1e24, 1e25, 1e26, 1e27, 1e28};

      mantissa /= pow10[scale];

      if (sign) {
        mantissa = -mantissa;
      }

      if (mantissa > (double)INT_MAX || mantissa < (double)INT_MIN) {
        status = 1;
      } else {
        *dst = (int)mantissa;
      }
    }
  }

  return status;
}