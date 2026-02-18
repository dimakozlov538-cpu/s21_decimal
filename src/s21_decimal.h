#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H
#include <stdint.h>

#define DECIMAL_SIGN_MASK 0x80000000
#define DECIMAL_SCALE_MASK 0x00FF0000
#define DECIMAL_SCALE_POS 16

#define S21_SIGN_POSITIVE 0
#define S21_SIGN_NEGATIVE (1 << 31)
#define S21_CONVERSION_OK 0
#define S21_CONVERSION_ERROR 1
#define S21_MAX_FLOAT 7.9228162514264337593543950335e28

typedef struct {
    int bits[4];
} s21_decimal;

typedef struct {
    unsigned int bits[8];
    unsigned int scale;
    unsigned int sign;
} big_decimal;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);

int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);

int s21_from_int_to_decimal(int src, s21_decimal* dst);
int s21_from_float_to_decimal(float src, s21_decimal* dst);
int s21_from_decimal_to_int(s21_decimal src, int* dst);
int s21_from_decimal_to_float(s21_decimal src, float* dst);

int s21_floor(s21_decimal value, s21_decimal* result);
int s21_round(s21_decimal value, s21_decimal* result);
int s21_truncate(s21_decimal value, s21_decimal* result);
int s21_negate(s21_decimal value, s21_decimal* result);

int get_sign(s21_decimal value);
void set_sign(s21_decimal* value, int sign);
int get_scale(s21_decimal value);
void set_scale(s21_decimal* value, int scale);
int is_zero(s21_decimal value);

#endif // S21_DECIMAL_H