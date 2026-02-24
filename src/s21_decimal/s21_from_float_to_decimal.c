#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"
#include "s21_decimal/s21_helper/s21_helper.h"

s21_decimal s21_str_to_decimal(char* str) {
  s21_decimal result = {0};

  int len = strlen(str);

  for (int i = 0; i < len; i++) {
    int digit = str[i] - '0';

    unsigned long long temp_low =
        (unsigned long long)(unsigned int)result.bits[0] * 10 + digit;
    unsigned long long temp_mid =
        (unsigned long long)(unsigned int)result.bits[1] * 10 +
        (temp_low >> 32);
    unsigned long long temp_high =
        (unsigned long long)(unsigned int)result.bits[2] * 10 +
        (temp_mid >> 32);

    // сохранение результата (младшие 32 бит)
    result.bits[0] = (int)(temp_low & 0xFFFFFFFF);
    result.bits[1] = (int)(temp_mid & 0xFFFFFFFF);
    result.bits[2] = (int)(temp_high & 0xFFFFFFFF);
  }

  return result;
}

int s21_from_float_to_decimal(float src, s21_decimal* dst) {
  if (isnan(src) || isinf(src) || fabsf(src) > S21_MAX_FLOAT) {
    return S21_CONVERSION_ERROR;
  }
  if (fabsf(src) < 1e-28 && src != 0.0f) {
    *dst = (s21_decimal){0};
    return S21_CONVERSION_ERROR;
  }
  if (src == 0.0f) {
    *dst = (s21_decimal){0};
    if (signbit(src)) {
      dst->bits[3] = S21_SIGN_NEGATIVE;
    }
  } else {
    int scale = 0;
    int sign = signbit(src);
    char buffer[64];
    sprintf(buffer, "%.7g", fabsf(src));
    char* dot_pos = strchr(buffer, '.');
    char* e_pos = strchr(buffer, 'e');
    if (!e_pos) e_pos = strchr(buffer, 'E');
    if (e_pos) {
      int exponent = atoi(e_pos + 1);
      scale -= exponent;
      *e_pos = '\0';  // убираем экспоненту из строки
    }
    if (dot_pos) {
      int frac_len = strlen(dot_pos + 1);
      scale += frac_len;
      memmove(dot_pos, dot_pos + 1, frac_len + 1);  // убираем точку из строки
    }
    // дописываем нули в число при отрицательном scale
    if (scale < 0) {
      int zeros_to_add = -scale;
      int current_len = strlen(buffer);
      memset(buffer + current_len, '0', zeros_to_add);
      buffer[current_len + zeros_to_add] = '\0';
      scale = 0;
    }
    s21_decimal result = s21_str_to_decimal(buffer);
    result.bits[3] =
        (scale << 16) | (sign ? S21_SIGN_NEGATIVE : S21_SIGN_POSITIVE);
    *dst = result;
  }
  return S21_CONVERSION_OK;
}