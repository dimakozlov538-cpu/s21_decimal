#include "s21_decimal.h"

int s21_sub(s21_decimal a, s21_decimal b, s21_decimal *result) {
  b.bits[3] ^= (1u << 31);
  return s21_add(a, b, result);
}