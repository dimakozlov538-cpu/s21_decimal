#include "s21_decimal.h"
#include "s21_decimal/s21_utility/s21_decimal_extended.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (!result) return S21_FAILURE_RESULT;

  *result = value;
  const s21_size scale = s21_get_scale(result);
  if (scale > 0) {
    s21_reduce_scale(result, scale, NULL, NULL);
    s21_set_scale(result, 0);
  }
  return S21_SUCCESS_RESULT;
}