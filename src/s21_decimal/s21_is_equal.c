#include "s21_decimal.h"
#include "s21_decimal/s21_helper/s21_helper.h"
#include "s21_decimal/s21_utility/s21_decimal_extended.h"

int s21_is_equal(s21_decimal a, s21_decimal b) {
  if (s21_is_zero(&a) && s21_is_zero(&b)) {
    return 1;
  }
  if (s21_get_sign(&a) != s21_get_sign(&b)) {
    return 0;
  }

  int result = 1;

  s21_big_decimal big_a;
  s21_big_decimal big_b;

  s21_decimal_to_big(&big_a, a);
  s21_decimal_to_big(&big_b, b);

  s21_align_scales(&big_a, &big_b);

  int is_less = 0;
  for (int i = 5; i >= 0 && !is_less; --i) {
    if (big_a.bits[i] != big_b.bits[i]) {
      is_less = 1;
      result = 0;
    }
  }

  return result;
}