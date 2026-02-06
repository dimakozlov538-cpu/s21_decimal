#include <check.h>
#include <stdlib.h>

#include "s21_test_suites.h"

int main(void) {
    int failed;
    SRunner* sr;

    sr = srunner_create(int_to_decimal_suite());
    srunner_add_suite(sr, float_to_decimal_suite());

    srunner_set_fork_status(sr, CK_FORK);
    srunner_run_all(sr, CK_NORMAL);
    failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}