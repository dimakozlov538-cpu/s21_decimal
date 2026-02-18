#include "s21_decimal.h"

int s21_is_equal(s21_decimal a, s21_decimal b) {
    if(is_zero(a) && is_zero(b)) {
        return 1;
    }
    if(get_sign(a) != get_sign(b)) {
        return 0;
    }

    int result = 1;

    big_decimal big_a;
    big_decimal big_b;

    decimal_to_big(&big_a, a);
    decimal_to_big(&big_b, b);

    align_scales(&big_a, &big_b);

    int is_less = 0;
    for (int i = 7; i >= 0 && !is_less; --i) {
        if(big_a.bits[i] != big_b.bits[i]) {
            is_less = 1;
            result = 0;
        }
    }

    return result;
}