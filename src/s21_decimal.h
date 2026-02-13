#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

typedef struct {
    unsigned int bits[4];
} s21_decimal;

int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_int(s21_decimal value, int *result);

#endif