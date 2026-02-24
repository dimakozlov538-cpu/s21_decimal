#include "s21_decimal.h"
#include "s21_decimal/s21_helper/s21_helper.h"

void s21_align_scales(s21_big_decimal* value1, s21_big_decimal* value2) {
  while (value1->scale < value2->scale) {
    unsigned long long int carry = 0;
    for (int i = 0; i < 6; i++) {
      unsigned long long int product =
          (unsigned long long int)(unsigned int)value1->bits[i] * 10 + carry;
      value1->bits[i] = (unsigned int)product;
      carry = product >> 32;
    }
    value1->scale++;
  }

  while (value2->scale < value1->scale) {
    unsigned long long int carry = 0;
    for (int i = 0; i < 6; i++) {
      unsigned long long int product =
          (unsigned long long int)(unsigned int)value2->bits[i] * 10 + carry;
      value2->bits[i] = (unsigned int)product;
      carry = product >> 32;
    }
    value2->scale++;
  }
}
