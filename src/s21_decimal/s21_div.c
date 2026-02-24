#include <stdbool.h>
#include <stdint.h>

#include "s21_decimal.h"
#include "s21_decimal/s21_helper/s21_helper.h"
#include "s21_decimal/s21_utility/s21_decimal_extended.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_result code = S21_ARITHMETIC_OK;

  if (!result) return S21_ARITHMETIC_ERROR;

  *result = (s21_decimal){0};

  if (!s21_is_correct_decimal(value_1) || !s21_is_correct_decimal(value_2))
    return S21_ARITHMETIC_ERROR;

  if (s21_is_zero(&value_2)) return S21_ARITHMETIC_ZERO_DIV;

  if (s21_is_zero(&value_1)) return S21_ARITHMETIC_OK;

  int result_sign = s21_get_sign(&value_1) ^ s21_get_sign(&value_2);

  if (value_2.bits[0] == 1 && value_2.bits[1] == 0 && value_2.bits[2] == 0 &&
      s21_get_scale(&value_2) == 0) {
    *result = value_1;
    s21_set_sign(result, result_sign);
    return S21_ARITHMETIC_OK;
  }

  s21_set_sign(&value_1, S21_POS_SIGN);
  s21_set_sign(&value_2, S21_POS_SIGN);

  int scale1 = s21_get_scale(&value_1);
  int scale2 = s21_get_scale(&value_2);

  s21_big_decimal big_dividend = s21_decimal_to_big_decimal(value_1);
  s21_big_decimal big_divisor = s21_decimal_to_big_decimal(value_2);

  int result_scale = scale1 - scale2;

  if (result_scale < 0) {
    int neg_scale = -result_scale;
    for (int i = 0; i < neg_scale; i++) {
      if (s21_big_mul_10(&big_dividend) != 0) {
        code = S21_ARITHMETIC_SMALL;
        break;
      }
    }
    result_scale = 0;
  }

  int alignment_scale = 0;
  while (s21_big_is_less(big_dividend, big_divisor) && result_scale < 28 &&
         code == S21_ARITHMETIC_OK) {
    if (s21_big_mul_10(&big_dividend) != 0) {
      code = S21_ARITHMETIC_SMALL;
      break;
    }
    result_scale++;
    alignment_scale++;
  }

  s21_big_decimal div_result = {0};
  s21_big_decimal remainder = {0};

  while (s21_big_greater_or_equal(big_dividend, big_divisor) &&
         code == S21_ARITHMETIC_OK) {
    s21_big_sub(big_dividend, big_divisor, &big_dividend);
    s21_big_add_one(&div_result);
  }

  remainder = big_dividend;

  while (!s21_big_is_zero(remainder) && result_scale < 28 &&
         code == S21_ARITHMETIC_OK) {
    if (s21_big_mul_10(&remainder) != 0) {
      code = S21_ARITHMETIC_SMALL;
      break;
    }

    if (s21_big_mul_10(&div_result) != 0) {
      code = S21_ARITHMETIC_SMALL;
      break;
    }

    while (s21_big_greater_or_equal(remainder, big_divisor)) {
      s21_big_sub(remainder, big_divisor, &remainder);
      s21_big_add_one(&div_result);
    }

    result_scale++;
  }

  if (alignment_scale >= 28 && result_scale >= 28 &&
      code == S21_ARITHMETIC_OK) {
    div_result.bits[0] = 0;
    div_result.bits[1] = 0;
    div_result.bits[2] = 0;
    result_scale = 0;
    code = S21_ARITHMETIC_SMALL;
  }

  if (code == S21_ARITHMETIC_OK)
    code = s21_normalize_result(&div_result, result_scale, result_sign, result);

  return code;
}
