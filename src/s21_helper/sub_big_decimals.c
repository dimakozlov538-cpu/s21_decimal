#include "s21_decimal.h"

void sub_big_decimals(big_decimal value1, big_decimal value2, big_decimal* result) {
    unsigned long long int borrow = 0;
    for (int i = 0; i < 8; i++) {
        unsigned long long int diff = (unsigned long long int)(unsigned int)value1.bits[i] - (unsigned long long int)(unsigned int)value2.bits[i] - borrow;
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