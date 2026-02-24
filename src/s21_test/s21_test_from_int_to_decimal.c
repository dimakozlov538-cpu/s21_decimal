#include <check.h>
#include <limits.h>
#include <stddef.h>

#include "s21_decimal.h"
#include "s21_decimal/s21_helper/s21_helper.h"

// ========================
// TEST DATA
// ========================
typedef struct {
    int input;
    int exp_return_value;
    s21_decimal exp_result;
} test_data_t;

static const test_data_t test_data[] = {
    {12345, S21_CONVERSION_OK, {.bits = {12345, 0, 0, S21_SIGN_POSITIVE}}},      // positive integer
    {-67890, S21_CONVERSION_OK, {.bits = {67890, 0, 0, S21_SIGN_NEGATIVE}}},     // negative integer
    {0, S21_CONVERSION_OK, {.bits = {0, 0, 0, S21_SIGN_POSITIVE}}},              // zero
    {INT_MAX, S21_CONVERSION_OK, {.bits = {INT_MAX, 0, 0, S21_SIGN_POSITIVE}}},  // INT_MAX
    {INT_MIN,
     S21_CONVERSION_OK,
     {.bits = {(unsigned int)INT_MAX + 1, 0, 0,
               S21_SIGN_NEGATIVE}}}  // INT_MIN - special case (requires unsigned conversion)
};

// ========================
// TCase: Valid Data
// ========================
START_TEST(test_int_to_decimal_valid) {
    int input = test_data[_i].input;
    int exp_return_value = test_data[_i].exp_return_value;
    s21_decimal exp_result = test_data[_i].exp_result;

    s21_decimal result = {0};
    int return_value = s21_from_int_to_decimal(input, &result);

    ck_assert_int_eq(return_value, exp_return_value);
    ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
    ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
    ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
    ck_assert_int_eq(result.bits[3], exp_result.bits[3]);
}
END_TEST

// ========================
// TCase: Null pointer
// ========================
START_TEST(test_int_to_decimal_null_pointer) {
    int input = 123;
    int exp_return_value = S21_CONVERSION_ERROR;

    int return_value = s21_from_int_to_decimal(input, NULL);

    ck_assert_int_eq(return_value, exp_return_value);
}
END_TEST

// ========================
// SUITE
// ========================
Suite* s21_add_int_to_decimal_suite(void) {
    Suite* s = suite_create("S21_FROM_INT_TO_DECIMAL SUITE");

    TCase* tc_valid = tcase_create("s21_from_int_to_decimal: Valid data");
    suite_add_tcase(s, tc_valid);
    tcase_add_loop_test(tc_valid, test_int_to_decimal_valid, 0, sizeof(test_data) / sizeof(test_data[0]));

    TCase* tc_null_pointer = tcase_create("s21_from_int_to_decimal: Null pointer");
    suite_add_tcase(s, tc_null_pointer);
    tcase_add_test(tc_null_pointer, test_int_to_decimal_null_pointer);

    return s;
}