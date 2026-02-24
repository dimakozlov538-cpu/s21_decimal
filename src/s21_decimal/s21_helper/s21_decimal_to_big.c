#include "s21_decimal.h"
#include "s21_decimal/s21_helper/s21_helper.h"
#include "s21_decimal/s21_utility/s21_decimal_extended.h"

void s21_decimal_to_big(s21_big_decimal* big, s21_decimal value) {
  for (int i = 0; i < 6; i++) {
    big->bits[i] = 0;
  }
  big->bits[0] = value.bits[0];
  big->bits[1] = value.bits[1];
  big->bits[2] = value.bits[2];
  big->scale = s21_get_scale(&value);
  big->sign = s21_get_sign(&value);
}