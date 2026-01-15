#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <stdio.h>

typedef struct {
    unsigned int bits[4];
} s21_decimal;

int s21_from_decimal_to_int(s21_decimal src, int *dst);

#endif