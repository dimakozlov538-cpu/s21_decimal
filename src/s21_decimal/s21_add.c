#include "s21_decimal.h"
#include "stdlib.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (result == NULL) {
        return 1;
    }
    
    result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;
    
    if (is_zero(value_1)) {
        *result = value_2;
        return 0;
    }
    if (is_zero(value_2)) {
        *result = value_1;
        return 0;
    }
    
    big_decimal big1, big2;
    decimal_to_big(&big1, value_1);
    decimal_to_big(&big2, value_2);
    
    align_scales(&big1, &big2);
    
    big_decimal big_result;
    for (int i = 0; i < 8; i++) {
        big_result.bits[i] = 0;
    }
    
    if (big1.sign == big2.sign) {
        add_big_decimals(big1, big2, &big_result);
        big_result.sign = big1.sign;
    } else {
        int cmp = compare_big_decimals(big1, big2);
        
        if (cmp >= 0) {
            sub_big_decimals(big1, big2, &big_result);
            big_result.sign = big1.sign;
        } else {
            sub_big_decimals(big2, big1, &big_result);
            big_result.sign = big2.sign;
        }
    }
    
    int error = big_to_decimal(big_result, result);
    
    if (error) {
        if (big_result.sign) {
            return 2;
        } else {
            return 1;
        }
    }
    
    return 0;
}
