#include "s21_decimal.h"
#include "s21_decimal/s21_helper/s21_helper.h"

void s21_add_big_decimals(s21_big_decimal value1, s21_big_decimal value2,
                          s21_big_decimal* result) {
  unsigned long long int carry = 0;
  for (int i = 0; i < 6; i++) {
    unsigned long long int sum =
        (unsigned long long int)(unsigned int)value1.bits[i] +
        (unsigned long long int)(unsigned int)value2.bits[i] + carry;
    result->bits[i] = (unsigned int)sum;
    carry = sum >> 32;
  }
  result->scale = value1.scale;
  result->sign = value1.sign;
}
