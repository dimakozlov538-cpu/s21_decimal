#include "s21_decimal.h"
#include "s21_decimal/s21_helper/s21_helper.h"

int s21_compare_big_decimals(s21_big_decimal value1, s21_big_decimal value2) {
  s21_align_scales(&value1, &value2);

  for (int i = 5; i >= 0; i--) {
    if (value1.bits[i] > value2.bits[i]) {
      return 1;
    } else if (value1.bits[i] < value2.bits[i]) {
      return -1;
    }
  }
  return 0;
}
