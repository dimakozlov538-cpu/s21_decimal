#include "s21_decimal.h"

void add_big_decimals(big_decimal value1, big_decimal value2, big_decimal* result) {
    unsigned long long int carry = 0;
    for (int i = 0; i < 8; i++) {
        unsigned long long int sum = (unsigned long long int)(unsigned int)value1.bits[i] + (unsigned long long int)(unsigned int)value2.bits[i] + carry;
        result->bits[i] = (unsigned int)sum;
        carry = sum >> 32;
    }
    result->scale = value1.scale;
    result->sign = value1.sign;
}
