#include "s21_decimal.h"
#include "s21_decimal/s21_helper/s21_helper.h"
#include "s21_decimal/s21_utility/s21_decimal_extended.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_result code = S21_ARITHMETIC_OK;

  if (!result) {
    return S21_ARITHMETIC_ERROR;
  }
  *result = (s21_decimal){0};

  if (!s21_is_correct_decimal(value_1) || !s21_is_correct_decimal(value_2)) {
    return S21_ARITHMETIC_ERROR;
  }

  if (s21_is_zero(&value_1) || s21_is_zero(&value_2)) {
    return S21_ARITHMETIC_OK;
  }

  int result_sign = s21_get_sign(&value_1) ^ s21_get_sign(&value_2);
  int result_scale = s21_get_scale(&value_1) + s21_get_scale(&value_2);

  s21_big_decimal mul_result = {0};

  for (int i = 0; i < 3; i++) {
    unsigned int word1 = value_1.bits[i];
    if (word1 == 0) continue;

    for (int j = 0; j < 3; j++) {
      unsigned int word2 = value_2.bits[j];
      if (word2 == 0) continue;

      unsigned long long product = (unsigned long long)word1 * word2;

      unsigned long long sum =
          (unsigned long long)mul_result.bits[i + j] + product;
      mul_result.bits[i + j] = (unsigned int)sum;

      unsigned long long carry = sum >> 32;
      for (int carry_position = i + j + 1; carry > 0 && carry_position < 6;
           carry_position++) {
        unsigned long long new_sum =
            (unsigned long long)mul_result.bits[carry_position] + carry;
        mul_result.bits[carry_position] = (unsigned int)new_sum;
        carry = new_sum >> 32;
      }
    }
  }

  code = s21_normalize_result(&mul_result, result_scale, result_sign, result);

  return code;
}
