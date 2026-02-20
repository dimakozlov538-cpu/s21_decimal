#include <check.h>
#include <stdint.h>

#include "s21_decimal.h"
#include "s21_decimal/s21_utility/s21_decimal_extended.h"

static s21_decimal s21_make_decimal(uint32_t lo, uint32_t mid, uint32_t hi,
                                    uint8_t scale, int sign) {
  s21_decimal value;

  value.bits[0] = (int)lo;
  value.bits[1] = (int)mid;
  value.bits[2] = (int)hi;

  value.bits[3] = 0;
  if (sign) value.bits[3] |= (int)(1u << 31);
  value.bits[3] |= (int)((uint32_t)scale << 16);

  return value;
}

static void s21_assert_decimal_eq(s21_decimal actual, s21_decimal expected) {
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}

typedef struct {
  uint32_t in_lo;
  uint32_t in_mid;
  uint32_t in_hi;
  uint8_t in_scale;
  int in_sign;
  uint32_t out_lo;
  uint32_t out_mid;
  uint32_t out_hi;
  uint8_t out_scale;
  int out_sign;
} t_s21_unary_case;

static const t_s21_unary_case s21_truncate_cases_data[] = {
    {12345u, 0, 0, 2, 0, 123u, 0, 0, 0, 0},
    {98765u, 0, 0, 2, 1, 987u, 0, 0, 0, 1},
    {55u, 0, 0, 0, 0, 55u, 0, 0, 0, 0},
    {1u, 0, 0, 1, 0, 0u, 0, 0, 0, 0},
    {1u, 0, 0, 1, 1, 0u, 0, 0, 0, 1},
    {1000u, 0, 0, 3, 0, 1u, 0, 0, 0, 0},
    {1000u, 0, 0, 3, 1, 1u, 0, 0, 0, 1},
};

static const t_s21_unary_case s21_floor_cases_data[] = {
    {1234u, 0, 0, 2, 0, 12u, 0, 0, 0, 0}, {1234u, 0, 0, 2, 1, 13u, 0, 0, 0, 1},
    {1200u, 0, 0, 2, 1, 12u, 0, 0, 0, 1}, {9u, 0, 0, 0, 1, 9u, 0, 0, 0, 1},
    {1u, 0, 0, 1, 0, 0u, 0, 0, 0, 0},     {1u, 0, 0, 1, 1, 1u, 0, 0, 0, 1},
    {1000u, 0, 0, 3, 1, 1u, 0, 0, 0, 1},
};

static const t_s21_unary_case s21_round_cases_data[] = {
    {124u, 0, 0, 1, 0, 12u, 0, 0, 0, 0}, {125u, 0, 0, 1, 0, 13u, 0, 0, 0, 0},
    {125u, 0, 0, 1, 1, 13u, 0, 0, 0, 1}, {42u, 0, 0, 0, 0, 42u, 0, 0, 0, 0},
    {149u, 0, 0, 2, 0, 1u, 0, 0, 0, 0},  {150u, 0, 0, 2, 0, 2u, 0, 0, 0, 0},
    {150u, 0, 0, 2, 1, 2u, 0, 0, 0, 1},  {500u, 0, 0, 2, 0, 5u, 0, 0, 0, 0},
    {999u, 0, 0, 2, 0, 10u, 0, 0, 0, 0},
};

static const t_s21_unary_case s21_negate_cases_data[] = {
    {7u, 0, 0, 0, 0, 7u, 0, 0, 0, 1},     {7u, 0, 0, 0, 1, 7u, 0, 0, 0, 0},
    {0u, 0, 0, 0, 0, 0u, 0, 0, 0, 1},     {0u, 0, 0, 0, 1, 0u, 0, 0, 0, 0},
    {123u, 0, 0, 2, 1, 123u, 0, 0, 2, 0},
};

START_TEST(s21_truncate_cases) {
  const t_s21_unary_case test_case = s21_truncate_cases_data[_i];
  s21_decimal value =
      s21_make_decimal(test_case.in_lo, test_case.in_mid, test_case.in_hi,
                       test_case.in_scale, test_case.in_sign);
  s21_decimal expected =
      s21_make_decimal(test_case.out_lo, test_case.out_mid, test_case.out_hi,
                       test_case.out_scale, test_case.out_sign);
  s21_decimal result;
  int ret = s21_truncate(value, &result);
  ck_assert_int_eq(ret, 0);
  s21_assert_decimal_eq(result, expected);
}
END_TEST

START_TEST(s21_floor_cases) {
  const t_s21_unary_case test_case = s21_floor_cases_data[_i];
  s21_decimal value =
      s21_make_decimal(test_case.in_lo, test_case.in_mid, test_case.in_hi,
                       test_case.in_scale, test_case.in_sign);
  s21_decimal expected =
      s21_make_decimal(test_case.out_lo, test_case.out_mid, test_case.out_hi,
                       test_case.out_scale, test_case.out_sign);
  s21_decimal result;
  int ret = s21_floor(value, &result);
  ck_assert_int_eq(ret, 0);
  s21_assert_decimal_eq(result, expected);
}
END_TEST

START_TEST(s21_round_cases) {
  const t_s21_unary_case test_case = s21_round_cases_data[_i];
  s21_decimal value =
      s21_make_decimal(test_case.in_lo, test_case.in_mid, test_case.in_hi,
                       test_case.in_scale, test_case.in_sign);
  s21_decimal expected =
      s21_make_decimal(test_case.out_lo, test_case.out_mid, test_case.out_hi,
                       test_case.out_scale, test_case.out_sign);
  s21_decimal result;
  int ret = s21_round(value, &result);
  ck_assert_int_eq(ret, 0);
  s21_assert_decimal_eq(result, expected);
}
END_TEST

START_TEST(s21_negate_cases) {
  const t_s21_unary_case test_case = s21_negate_cases_data[_i];
  s21_decimal value =
      s21_make_decimal(test_case.in_lo, test_case.in_mid, test_case.in_hi,
                       test_case.in_scale, test_case.in_sign);
  s21_decimal expected =
      s21_make_decimal(test_case.out_lo, test_case.out_mid, test_case.out_hi,
                       test_case.out_scale, test_case.out_sign);
  s21_decimal result;
  int ret = s21_negate(value, &result);
  ck_assert_int_eq(ret, 0);
  s21_assert_decimal_eq(result, expected);
}
END_TEST

START_TEST(s21_floor_null_result) {
  s21_decimal value = s21_make_decimal(10u, 0, 0, 1, 0);
  int ret = s21_floor(value, NULL);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(s21_round_null_result) {
  s21_decimal value = s21_make_decimal(10u, 0, 0, 1, 0);
  int ret = s21_round(value, NULL);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(s21_truncate_null_result) {
  s21_decimal value = s21_make_decimal(10u, 0, 0, 1, 0);
  int ret = s21_truncate(value, NULL);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(s21_negate_null_result) {
  s21_decimal value = s21_make_decimal(10u, 0, 0, 1, 0);
  int ret = s21_negate(value, NULL);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(s21_bit_helpers) {
  s21_decimal value = s21_make_decimal(0, 0, 0, 0, 0);
  ck_assert_int_eq(s21_test_bit(&value, 0), 0);
  s21_set_bit(&value, 0);
  ck_assert_int_eq(s21_test_bit(&value, 0), 1);
  s21_unset_bit(&value, 0);
  ck_assert_int_eq(s21_test_bit(&value, 0), 0);
}
END_TEST

START_TEST(s21_zero_helpers) {
  s21_decimal value = s21_make_decimal(0, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_zero(&value), 1);
  value = s21_make_decimal(1u, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_zero(&value), 0);
}
END_TEST

Suite* s21_add_other_function_suite(void) {
  Suite* suite = suite_create("S21_OTHER_FUNCTION SUITE");
  TCase* ts_other_functions = tcase_create("other_functions");

  tcase_add_loop_test(ts_other_functions, s21_truncate_cases, 0,
                      (int)(sizeof(s21_truncate_cases_data) /
                            sizeof(s21_truncate_cases_data[0])));
  tcase_add_loop_test(
      ts_other_functions, s21_floor_cases, 0,
      (int)(sizeof(s21_floor_cases_data) / sizeof(s21_floor_cases_data[0])));
  tcase_add_loop_test(
      ts_other_functions, s21_round_cases, 0,
      (int)(sizeof(s21_round_cases_data) / sizeof(s21_round_cases_data[0])));
  tcase_add_loop_test(
      ts_other_functions, s21_negate_cases, 0,
      (int)(sizeof(s21_negate_cases_data) / sizeof(s21_negate_cases_data[0])));
  tcase_add_test(ts_other_functions, s21_floor_null_result);
  tcase_add_test(ts_other_functions, s21_round_null_result);
  tcase_add_test(ts_other_functions, s21_truncate_null_result);
  tcase_add_test(ts_other_functions, s21_negate_null_result);
  tcase_add_test(ts_other_functions, s21_bit_helpers);
  tcase_add_test(ts_other_functions, s21_zero_helpers);

  suite_add_tcase(suite, ts_other_functions);

  return suite;
}
