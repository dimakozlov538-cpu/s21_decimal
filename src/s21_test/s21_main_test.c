#include <check.h>
#include <stdlib.h>

#include "s21_test_suites.h"

int main(void) {
    SRunner* sr = srunner_create(s21_add_ashlyuad_suite());
    srunner_add_suite(sr, s21_add_dragonad_suite());
    srunner_add_suite(sr, s21_add_other_function_suite());
    srunner_add_suite(sr, s21_add_conversion_suite());
    srunner_add_suite(sr, s21_add_int_to_decimal_suite());
    srunner_add_suite(sr, s21_add_float_to_decimal_suite());
    
    srunner_run_all(sr, CK_NORMAL);
    
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}