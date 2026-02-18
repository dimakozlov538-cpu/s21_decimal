#include "s21_decimal.h"

int s21_is_greater(s21_decimal a, s21_decimal b) {
    if(is_zero(a) && is_zero(b)) {
        return 0;
    }

    int result = 0;

    if (get_sign(a) && !get_sign(b)) {
        result = 0;
    } else if (!get_sign(a) && get_sign(b)){
        result = 1;
    } else {
        big_decimal big_a;
        big_decimal big_b;
        
        decimal_to_big(&big_a, a);
        decimal_to_big(&big_b, b);

        align_scales(&big_a, &big_b);

        int is_less = 0;
        for(int i = 7; i >= 0 && !is_less; --i) {
            if (big_a.bits[i] != big_b.bits[i]) {
                if (get_sign(a)) {
                    if (big_a.bits[i] < big_b.bits[i]) {
                        result = 1;
                        is_less = 1;
                    } else {
                        is_less = 1;
                    }
                } else {
                    if (big_a.bits[i] > big_b.bits[i]) {
                        result = 1;
                        is_less = 1;
                    } else {
                        is_less = 1;
                    }
                }
            }
        }
    }

    return result;
}