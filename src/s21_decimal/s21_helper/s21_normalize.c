#include "s21_decimal.h"
#include "s21_decimal/s21_helper/s21_helper.h"
#include "s21_decimal/s21_utility/s21_decimal_extended.h"

int s21_normalize_result(s21_big_decimal *big_val, int result_scale,
                         int result_sign, s21_decimal *result) {
  s21_arithmetic_result code = S21_ARITHMETIC_OK;

  int is_too_large = s21_big_fits_in_decimal(*big_val);

  if (is_too_large || result_scale > 28) {
    code = s21_normalize_by_scaling(big_val, &result_scale, &is_too_large);
  }

  if (code == S21_ARITHMETIC_OK && (is_too_large || result_scale > 28)) {
    code = s21_final_overflow_normalize(big_val, result_scale, result_sign,
                                        result);
  }

  if (code == S21_ARITHMETIC_OK) {
    result->bits[0] = big_val->bits[0];
    result->bits[1] = big_val->bits[1];
    result->bits[2] = big_val->bits[2];
    result->bits[3] = 0;
    s21_set_scale(result, (s21_size)result_scale);
    s21_set_sign(result, result_sign ? S21_NEG_SIGN : S21_POS_SIGN);
  }

  return code;
}

int s21_normalize_by_scaling(s21_big_decimal *big_val, int *result_scale,
                             int *is_too_large) {
  int code = S21_ARITHMETIC_OK;

  while ((*is_too_large || *result_scale > 28) && *result_scale > 0) {
    int last_digit = s21_big_get_last_digit(big_val);
    s21_big_div_10(big_val);
    (*result_scale)--;

    if (last_digit == 5) {
      int current_last_digit = s21_big_get_last_digit(big_val);
      if (current_last_digit % 2 == 1) {
        code = s21_big_add_one(big_val);
      }
    } else if (last_digit > 5) {
      code = s21_big_add_one(big_val);
    }

    *is_too_large = s21_big_fits_in_decimal(*big_val);
  }

  return code;
}

int s21_final_overflow_normalize(s21_big_decimal *big_val, int result_scale,
                                 int result_sign, s21_decimal *result) {
  int code = S21_ARITHMETIC_OK;
  int should_round_up = 0;

  int is_too_large = s21_big_fits_in_decimal(*big_val);
  if (is_too_large) {
    int last_digit = s21_big_get_last_digit(big_val);

    if (last_digit > 5) {
      should_round_up = 1;
    } else if (last_digit == 5) {
      s21_big_decimal temp = *big_val;
      s21_big_div_10(&temp);
      int pre_last_digit = s21_big_get_last_digit(&temp);
      if (pre_last_digit % 2 == 1) {
        should_round_up = 1;
      }
    }

    if (should_round_up) {
      code = s21_big_add_one(big_val);
      if (code == S21_ARITHMETIC_OK) {
        is_too_large = s21_big_fits_in_decimal(*big_val);
      }
    }
  }

  if (is_too_large || result_scale > 28) {
    if (result_sign) {
      result->bits[0] = 0xFFFFFFFF;
      result->bits[1] = 0xFFFFFFFF;
      result->bits[2] = 0xFFFFFFFF;
      result->bits[3] = 0x80000000;
      return S21_ARITHMETIC_SMALL;
    } else {
      result->bits[0] = 0xFFFFFFFF;
      result->bits[1] = 0xFFFFFFFF;
      result->bits[2] = 0xFFFFFFFF;
      result->bits[3] = 0x7FFFFFFF;
      return S21_ARITHMETIC_BIG;
    }
  }

  return code;
}
