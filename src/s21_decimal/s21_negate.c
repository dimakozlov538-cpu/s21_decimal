#include "s21_decimal.h"
#include "s21_decimal/s21_utility/s21_decimal_extended.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (!result) return S21_FAILURE_RESULT;

  *result = value;
  if (s21_get_sign(result) == S21_POS_SIGN) {
    s21_set_sign(result, S21_NEG_SIGN);
  } else {
    s21_set_sign(result, S21_POS_SIGN);
  }
  return S21_SUCCESS_RESULT;
}