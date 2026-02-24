#ifndef S21_DECIMAL_EXTENDED_H
#define S21_DECIMAL_EXTENDED_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "s21_decimal.h"

#define S21_SUCCESS_RESULT 0
#define S21_FAILURE_RESULT 1

typedef enum { S21_POS_SIGN = 0, S21_NEG_SIGN = 1 } s21_sign;

typedef uint8_t s21_bit;
typedef uint8_t s21_size;

bool s21_test_bit(const s21_decimal* value, s21_size nth);
void s21_set_bit(s21_decimal* value, s21_size nth);
void s21_unset_bit(s21_decimal* value, s21_size nth);

s21_sign s21_get_sign(const s21_decimal* value);
void s21_set_sign(s21_decimal* value, s21_sign sign);

s21_size s21_get_scale(const s21_decimal* value);
void s21_set_scale(s21_decimal* value, s21_size scale);
bool s21_is_zero(const s21_decimal* value);
    
uint32_t s21_divide_by_10(s21_decimal* value);
void s21_reduce_scale(s21_decimal* value, s21_size scale, bool* has_fraction,
                      uint32_t* last_digit);
void s21_add_one_to_mantissa(s21_decimal* value);

#endif  // S21_DECIMAL_EXTENDED_H