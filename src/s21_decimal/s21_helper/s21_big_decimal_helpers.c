#include <stdint.h>

#include "s21_decimal.h"
#include "s21_decimal/s21_helper/s21_helper.h"
#include "s21_decimal/s21_utility/s21_decimal_extended.h"

int s21_big_mul_10(s21_big_decimal *big) {
  if (!big) return 1;

  unsigned long long carry = 0;

  for (int i = 0; i < 6; i++) {
    unsigned long long product =
        (unsigned long long)(unsigned int)big->bits[i] * 10ULL + carry;
    big->bits[i] = (int)(unsigned int)product;
    carry = product >> 32;
  }

  if (carry != 0) {
    return 1;
  }

  return 0;
}

void s21_big_div_10(s21_big_decimal *big) {
  unsigned long long current = 0;
  unsigned int remainder = 0;

  for (int i = 5; i >= 0; i--) {
    current = ((unsigned long long)remainder << 32) |
              (unsigned long long)big->bits[i];
    big->bits[i] = (unsigned int)(current / 10);
    remainder = (unsigned int)(current % 10);
  }
}

int s21_big_add_one(s21_big_decimal *big_val) {
  for (int i = 0; i < 6; i++) {
    big_val->bits[i]++;

    if (big_val->bits[i] != 0) {
      return S21_ARITHMETIC_OK;
    }
  }

  return S21_ARITHMETIC_BIG;
}

void s21_big_add(s21_big_decimal value1, s21_big_decimal value2,
                 s21_big_decimal *result) {
  unsigned long long int carry = 0;
  for (int i = 0; i < 6; i++) {
    unsigned long long int sum =
        (unsigned long long int)value1.bits[i] + value2.bits[i] + carry;
    result->bits[i] = (unsigned int)sum;
    carry = sum >> 32;
  }
  result->scale = value1.scale;
  result->sign = value1.sign;
}

void s21_big_sub(s21_big_decimal value1, s21_big_decimal value2,
                 s21_big_decimal *result) {
  unsigned long long int borrow = 0;
  for (int i = 0; i < 6; i++) {
    unsigned long long int diff =
        (unsigned long long int)value1.bits[i] - value2.bits[i] - borrow;
    result->bits[i] = (unsigned int)diff;

    if (diff > value1.bits[i]) {
      borrow = 1;
    } else {
      borrow = 0;
    }
  }
  result->scale = value1.scale;
  result->sign = value1.sign;
}

int s21_big_get_last_digit(s21_big_decimal *big) {
  unsigned long long remainder = 0;

  for (int i = 5; i >= 0; i--) {
    unsigned long long current = (remainder << 32) | big->bits[i];
    remainder = current % 10;
  }

  return (int)remainder;
}

int s21_big_fits_in_decimal(s21_big_decimal big_val) {
  int code = 0;
  for (int i = 5; i >= 3; i--) {
    if (big_val.bits[i] != 0) {
      code = 1;
    }
  }
  return code;
}

s21_big_decimal s21_decimal_to_big_decimal(s21_decimal dec) {
  s21_big_decimal big = {0};
  big.bits[0] = dec.bits[0];
  big.bits[1] = dec.bits[1];
  big.bits[2] = dec.bits[2];
  return big;
}

int s21_big_is_less(s21_big_decimal a, s21_big_decimal b) {
  for (int i = 5; i >= 0; i--) {
    if (a.bits[i] < b.bits[i]) {
      return 1;
    } else if (a.bits[i] > b.bits[i]) {
      return 0;
    }
  }
  return 0;
}

int s21_big_greater_or_equal(s21_big_decimal a, s21_big_decimal b) {
  for (int i = 5; i >= 0; i--) {
    if (a.bits[i] != b.bits[i]) {
      return a.bits[i] > b.bits[i];
    }
  }

  return 1;
}

int s21_big_is_zero(s21_big_decimal a) {
  for (int i = 0; i < 6; i++) {
    if (a.bits[i] != 0) {
      return 0;
    }
  }

  return 1;
}