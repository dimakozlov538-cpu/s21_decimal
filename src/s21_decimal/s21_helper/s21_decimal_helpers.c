#include "s21_decimal/s21_helper/s21_helper.h"

int s21_is_correct_decimal(s21_decimal value) {
  int code = 1;

  int bits3 = value.bits[3];
  if (code && (bits3 & 0x0000FFFF) != 0) {
    code = 0;
  }

  int exponent = (bits3 >> 16) & 0xFF;
  if (code && (exponent > 28)) {
    code = 0;
  }

  if (code && (bits3 & 0x7F000000) != 0) {
    code = 0;
  }

  return code;
}