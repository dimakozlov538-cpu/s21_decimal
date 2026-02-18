#include "s21_decimal.h"

int compare_big_decimals(big_decimal value1, big_decimal value2) {
    align_scales(&value1, &value2);
    
    for (int i = 7; i >= 0; i--) {
        if (value1.bits[i] > value2.bits[i]) {
            return 1;
        } else if (value1.bits[i] < value2.bits[i]) {
            return -1;
        }
    }
    return 0;
}
