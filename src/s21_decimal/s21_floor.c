#include "s21_decimal.h"
#include "s21_decimal/s21_utility/s21_decimal_extended.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (!result) return S21_FAILURE_RESULT;

  *result = value;
  const s21_size scale = s21_get_scale(result);
  if (scale > 0) {
    bool has_fraction = false;
    s21_reduce_scale(result, scale, &has_fraction, NULL);
    s21_set_scale(result, 0);
    if (s21_get_sign(result) == S21_NEG_SIGN && has_fraction) {
      s21_add_one_to_mantissa(result);
    }
  }
  return S21_SUCCESS_RESULT;
}