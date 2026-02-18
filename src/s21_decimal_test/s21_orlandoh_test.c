#include <check.h>
#include <math.h>
#include <stdlib.h>
#include "s21_decimal.h"

static s21_decimal make_decimal(unsigned int lo, unsigned int mid, unsigned int hi, int scale, int sign) {
    s21_decimal d = {0};
    d.bits[0] = lo;
    d.bits[1] = mid;
    d.bits[2] = hi;
    d.bits[3] = ((unsigned int)scale << 16) | ((unsigned int)(sign ? 1 : 0) << 31);
    return d;
}

START_TEST(test_int_valid_positive) {
    s21_decimal d = make_decimal(12345, 0, 0, 0, 0);
    int result = 0;
    int status = s21_from_decimal_to_int(d, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(result, 12345);
}
END_TEST

START_TEST(test_int_valid_negative) {
    s21_decimal d = make_decimal(98765, 0, 0, 0, 1);
    int result = 0;
    int status = s21_from_decimal_to_int(d, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(result, -98765);
}
END_TEST

START_TEST(test_int_with_scale) {
    s21_decimal d = make_decimal(123450, 0, 0, 1, 0);
    int result = 0;
    int status = s21_from_decimal_to_int(d, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(result, 12345);
}
END_TEST

START_TEST(test_int_null_pointer) {
    s21_decimal d = make_decimal(100, 0, 0, 0, 0);
    int status = s21_from_decimal_to_int(d, NULL);
    ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_int_overflow_positive) {
    s21_decimal d = make_decimal(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0, 0);
    int result = 0;
    int status = s21_from_decimal_to_int(d, &result);
    ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_int_invalid_scale) {
    s21_decimal d = {{1, 0, 0, (29 << 16)}};
    int result = 999;
    int status = s21_from_decimal_to_int(d, &result);
    ck_assert_int_eq(status, 1);
    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_float_zero) {
    s21_decimal d = {{0, 0, 0, 0}};
    float result = 0.0f;
    int status = s21_from_decimal_to_float(d, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_float_eq(result, 0.0f);
}
END_TEST

START_TEST(test_float_one) {
    s21_decimal d = make_decimal(1, 0, 0, 0, 0);
    float result = 0.0f;
    int status = s21_from_decimal_to_float(d, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_float_eq(result, 1.0f);
}
END_TEST

START_TEST(test_float_minus_one) {
    s21_decimal d = make_decimal(1, 0, 0, 0, 1);
    float result = 0.0f;
    int status = s21_from_decimal_to_float(d, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_float_eq(result, -1.0f);
}
END_TEST

START_TEST(test_float_123_456) {
    s21_decimal d = make_decimal(123456, 0, 0, 3, 0);
    float result = 0.0f;
    int status = s21_from_decimal_to_float(d, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_float_eq_tol(result, 123.456f, 1e-3f);
}
END_TEST

START_TEST(test_float_negative_zero) {
    s21_decimal d = make_decimal(0, 0, 0, 0, 1);
    float result = 1.0f;
    int status = s21_from_decimal_to_float(d, &result);
    ck_assert_int_eq(status, 0);
    ck_assert(result == 0.0f);
    ck_assert(signbit(result) != 0);
}
END_TEST

START_TEST(test_float_invalid_scale) {
    s21_decimal d = {{1, 0, 0, (29 << 16) | (1U << 31)}};
    float result = 0.0f;
    int status = s21_from_decimal_to_float(d, &result);
    ck_assert_int_eq(status, 1);
    ck_assert(result == 0.0f);
    ck_assert(signbit(result) != 0);
}
END_TEST

START_TEST(test_float_null_pointer) {
    s21_decimal d = make_decimal(1, 0, 0, 0, 0);
    int status = s21_from_decimal_to_float(d, NULL);
    ck_assert_int_eq(status, 1);
}
END_TEST

Suite *conversion_suite(void) {
    Suite *s = suite_create("Conversion");
    TCase *tc_int = tcase_create("to_int");
    TCase *tc_float = tcase_create("to_float");

    tcase_add_test(tc_int, test_int_valid_positive);
    tcase_add_test(tc_int, test_int_valid_negative);
    tcase_add_test(tc_int, test_int_with_scale);
    tcase_add_test(tc_int, test_int_null_pointer);
    tcase_add_test(tc_int, test_int_overflow_positive);
    tcase_add_test(tc_int, test_int_invalid_scale);

    tcase_add_test(tc_float, test_float_zero);
    tcase_add_test(tc_float, test_float_one);
    tcase_add_test(tc_float, test_float_minus_one);
    tcase_add_test(tc_float, test_float_123_456);
    tcase_add_test(tc_float, test_float_negative_zero);
    tcase_add_test(tc_float, test_float_invalid_scale);
    tcase_add_test(tc_float, test_float_null_pointer);

    suite_add_tcase(s, tc_int);
    suite_add_tcase(s, tc_float);
    return s;
}
