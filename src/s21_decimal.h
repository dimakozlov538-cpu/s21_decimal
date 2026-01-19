#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

#include <limits.h>
#include <stddef.h>
#include <math.h>
#include <stdint.h>
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int bits[4];
} s21_decimal;

int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_int(s21_decimal value, int *result);

#endif