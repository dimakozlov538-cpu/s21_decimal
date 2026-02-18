#include "s21_decimal.h"

int big_to_decimal(big_decimal big, s21_decimal* result) {
    int error = 0;
    
    int can_normalize = 1;
    while (big.scale > 0 && can_normalize) {
        big_decimal temp = big;
        unsigned long long int remainder = 0;
        
        for (int i = 7; i >= 0; i--) {
            unsigned long long int value = ((unsigned long long int)(unsigned int)remainder << 32) | temp.bits[i];
            temp.bits[i] = (unsigned int)(value / 10);
            remainder = value % 10;
        }
        
        if (remainder == 0) {
            big = temp;
            big.scale--;
        } else {
            can_normalize = 0;
        }
    }
    
    int overflow = 0;
    for (int i = 3; i < 8 && !overflow; i++) {
        if (big.bits[i] != 0) {
            overflow = 1;
        }
    }
    
    if (overflow) {
        while (overflow && big.scale > 0) {
            unsigned long long int remainder = 0;
            for (int i = 7; i >= 0; i--) {
                unsigned long long int value = ((unsigned long long int)(unsigned int)remainder << 32) | big.bits[i];
                big.bits[i] = (unsigned int)(value / 10);
                remainder = value % 10;
            }
            big.scale--;
            
            overflow = 0;
            for (int i = 3; i < 8 && !overflow; i++) {
                if (big.bits[i] != 0) {
                    overflow = 1;
                }
            }
        }
        
        if (overflow) {
            error = 1;
        }
    }
    
    if (!error) {
        result->bits[0] = big.bits[0];
        result->bits[1] = big.bits[1];
        result->bits[2] = big.bits[2];
        result->bits[3] = 0;
        set_scale(result, big.scale);
        set_sign(result, big.sign);
    }
    
    return error;
}