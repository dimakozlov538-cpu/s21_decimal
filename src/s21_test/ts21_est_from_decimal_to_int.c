#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "../s21_decimal.h"

START_TEST(test_valid_positive) {
    s21_decimal d = {0};
    d.bits[0] = 12345;
    d.bits[3] = 0;

    int result;
    int status = s21_from_decimal_to_int(d, &result);

    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(result, 12345);
}
END_TEST

START_TEST(test_valid_negative) {
    s21_decimal d = {0};
    d.bits[0] = 98765;
    d.bits[3] = 0x80000000;

    int result;
    int status = s21_from_decimal_to_int(d, &result);

    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(result, -98765);
}
END_TEST

START_TEST(test_with_exponent) {
    s21_decimal d = {0};
    d.bits[0] = 123450;
    d.bits[3] = 0x00010000;

    int result;
    int status = s21_from_decimal_to_int(d, &result);

    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(result, 12345);
}
END_TEST

START_TEST(test_null_dst) {
    s21_decimal d = {0};
    d.bits[0] = 100;

    int status = s21_from_decimal_to_int(d, NULL);
    ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_overflow) {
    s21_decimal d = {0};
    d.bits[0] = 0xFFFFFFFF;
    d.bits[1] = 0xFFFFFFFF;
    d.bits[2] = 0xFFFFFFFF;
    d.bits[3] = 0;

    int result;
    int status = s21_from_decimal_to_int(d, &result);
    ck_assert_int_eq(status, 2);
}
END_TEST

Suite *decimal_suite(void) {
    Suite *s = suite_create("s21_from_decimal_to_int");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_valid_positive);
    tcase_add_test(tc_core, test_valid_negative);
    tcase_add_test(tc_core, test_with_exponent);
    tcase_add_test(tc_core, test_null_dst);
    tcase_add_test(tc_core, test_overflow);

    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    Suite *s = decimal_suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}