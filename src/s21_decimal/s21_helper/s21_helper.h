#ifndef S21_HELPER_H
#define S21_HELPER_H

#include "s21_decimal.h"

#define DECIMAL_SIGN_MASK 0x80000000
#define DECIMAL_SCALE_MASK 0x00FF0000
#define DECIMAL_SCALE_POS 16

#define S21_SIGN_POSITIVE 0
#define S21_SIGN_NEGATIVE (1 << 31)

#define S21_MAX_FLOAT 7.9228162514264337593543950335e28

typedef struct {
  unsigned int bits[6];
  unsigned int scale;
  unsigned int sign;
} s21_big_decimal;

int s21_is_correct_decimal(s21_decimal decimal);

int s21_normalize_result(s21_big_decimal *big_val, int result_scale,
                         int result_sign, s21_decimal *result);
int s21_normalize_by_scaling(s21_big_decimal *big_val, int *result_scale,
                             int *is_too_large);
int s21_final_overflow_normalize(s21_big_decimal *big_val, int result_scale,
                                 int result_sign, s21_decimal *result);

void s21_decimal_to_big(s21_big_decimal *big, s21_decimal value);
s21_big_decimal s21_decimal_to_big_decimal(s21_decimal dec);
int s21_big_to_decimal(s21_big_decimal big, s21_decimal *result);

void s21_align_scales(s21_big_decimal *value1, s21_big_decimal *value2);
void s21_add_big_decimals(s21_big_decimal value1, s21_big_decimal value2,
                          s21_big_decimal *result);
void s21_sub_big_decimals(s21_big_decimal value1, s21_big_decimal value2,
                          s21_big_decimal *result);
int s21_compare_big_decimals(s21_big_decimal value1, s21_big_decimal value2);

int s21_big_mul_10(s21_big_decimal *big);
void s21_big_div_10(s21_big_decimal *big);
int s21_big_add_one(s21_big_decimal *big_val);
void s21_big_add(s21_big_decimal value1, s21_big_decimal value2,
                 s21_big_decimal *result);
void s21_big_sub(s21_big_decimal value1, s21_big_decimal value2,
                 s21_big_decimal *result);
int s21_big_get_last_digit(s21_big_decimal *big);
int s21_big_fits_in_decimal(s21_big_decimal big_val);
int s21_big_is_less(s21_big_decimal a, s21_big_decimal b);
int s21_big_greater_or_equal(s21_big_decimal a, s21_big_decimal b);
int s21_big_is_zero(s21_big_decimal a);

#endif  // S21_HELPER_H
