#include <check.h>
#include <stdlib.h>

Suite* s21_decimal_suite(void);
Suite* conversion_suite(void);
Suite* int_to_decimal_suite(void);
Suite* float_to_decimal_suite(void);

int main(void) {
    SRunner* sr = srunner_create(s21_decimal_suite());
    
    srunner_add_suite(sr, conversion_suite());
    srunner_add_suite(sr, int_to_decimal_suite());
    srunner_add_suite(sr, float_to_decimal_suite());

    srunner_run_all(sr, CK_NORMAL);
    
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}