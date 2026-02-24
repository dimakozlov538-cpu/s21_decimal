#include "s21_decimal.h"
#include "s21_decimal/s21_helper/s21_helper.h"
#include "s21_decimal/s21_utility/s21_decimal_extended.h"

int s21_big_to_decimal(s21_big_decimal big, s21_decimal* result) {
  int error = 0;

  int can_normalize = 1;
  while (big.scale > 0 && can_normalize) {
    s21_big_decimal temp = big;
    unsigned long long int remainder = 0;

    for (int i = 5; i >= 0; i--) {
      unsigned long long int value =
          ((unsigned long long int)(unsigned int)remainder << 32) |
          temp.bits[i];
      temp.bits[i] = (unsigned int)(value / 10);
      remainder = value % 10;
    }

    if (remainder == 0) {
      big = temp;
      big.scale--;
    } else {
      can_normalize = 0;
    }
  }

  int overflow = 0;
  for (int i = 3; i < 6 && !overflow; i++) {
    if (big.bits[i] != 0) {
      overflow = 1;
    }
  }

  if (overflow) {
    while (overflow && big.scale > 0) {
      unsigned long long int remainder = 0;
      for (int i = 5; i >= 0; i--) {
        unsigned long long int value =
            ((unsigned long long int)(unsigned int)remainder << 32) |
            big.bits[i];
        big.bits[i] = (unsigned int)(value / 10);
        remainder = value % 10;
      }
      big.scale--;

      overflow = 0;
      for (int i = 3; i < 6 && !overflow; i++) {
        if (big.bits[i] != 0) {
          overflow = 1;
        }
      }
    }

    if (overflow) {
      error = 1;
    }
  }

  if (!error) {
    result->bits[0] = big.bits[0];
    result->bits[1] = big.bits[1];
    result->bits[2] = big.bits[2];
    result->bits[3] = 0;
    s21_set_scale(result, big.scale);
    s21_set_sign(result, big.sign);
  }

  return error;
}