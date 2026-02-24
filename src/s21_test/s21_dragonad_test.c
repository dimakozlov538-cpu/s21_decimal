#include <check.h>
#include <stdbool.h>
#include <stdint.h>

#include "s21_decimal.h"
#include "s21_decimal/s21_utility/s21_decimal_extended.h"

// === Константы для тестов (вместо макросов, чтобы избежать -Wmissing-braces)
// ===
static const s21_decimal S21_DECIMAL_INF = {
    .bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};

// Вспомогательная функция для создания decimal
static s21_decimal make_decimal(unsigned int b0, unsigned int b1,
                                unsigned int b2, unsigned int b3) {
  s21_decimal d = {0};
  d.bits[0] = b0;
  d.bits[1] = b1;
  d.bits[2] = b2;
  d.bits[3] = b3;
  return d;
}

// ==================== ТЕСТЫ ДЛЯ s21_mul ====================

START_TEST(test_mul_basic_2x3) {
  s21_decimal result;
  int code =
      s21_mul(make_decimal(2, 0, 0, 0), make_decimal(3, 0, 0, 0), &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(result.bits[0], 6);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_mul_by_zero) {
  s21_decimal result;
  int code =
      s21_mul(make_decimal(123, 0, 0, 0), make_decimal(0, 0, 0, 0), &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_mul_negative_positive) {
  s21_decimal result;
  int code = s21_mul(make_decimal(5, 0, 0, 0x80000000),
                     make_decimal(3, 0, 0, 0), &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(s21_get_sign(&result), S21_NEG_SIGN);
  ck_assert_int_eq(result.bits[0], 15);
}
END_TEST

START_TEST(test_mul_positive_overflow) {
  s21_decimal result;
  int code = s21_mul(make_decimal(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0),
                     make_decimal(2, 0, 0, 0), &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_BIG);
}
END_TEST

START_TEST(test_mul_negative_overflow) {
  s21_decimal result;
  int code =
      s21_mul(make_decimal(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000),
              make_decimal(2, 0, 0, 0), &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_SMALL);
}
END_TEST

START_TEST(test_mul_null_pointer) {
  int code = s21_mul(make_decimal(1, 0, 0, 0), make_decimal(2, 0, 0, 0), NULL);
  ck_assert_int_eq(code, S21_ARITHMETIC_ERROR);
}
END_TEST

START_TEST(test_mul_scale_addition) {
  s21_decimal result;
  int code = s21_mul(make_decimal(15, 0, 0, 0x00010000),  // 1.5
                     make_decimal(20, 0, 0, 0x00010000),  // 2.0
                     &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(s21_get_scale(&result), 2);
  ck_assert_int_eq(result.bits[0], 300);  // 3.00
}
END_TEST

START_TEST(test_mul_invalid_decimal) {
  s21_decimal result;
  int code = s21_mul(make_decimal(123, 0, 0, 0x001D0000),  // scale=29
                     make_decimal(2, 0, 0, 0), &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_ERROR);
}
END_TEST

START_TEST(test_mul_inf_operand) {
  s21_decimal result;
  int code = s21_mul(S21_DECIMAL_INF, make_decimal(2, 0, 0, 0), &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_ERROR);
}
END_TEST

START_TEST(test_mul_decimal_0_5x0_5) {
  s21_decimal result;
  int code = s21_mul(make_decimal(5, 0, 0, 0x00010000),  // 0.5
                     make_decimal(5, 0, 0, 0x00010000),  // 0.5
                     &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(result.bits[0], 25);
  ck_assert_int_eq(s21_get_scale(&result), 2);  // 0.25
}
END_TEST

START_TEST(test_mul_large_numbers) {
  s21_decimal result;
  int code = s21_mul(make_decimal(0, 1, 0, 0),  // 2^32
                     make_decimal(2, 0, 0, 0), &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 2);  // 2 * 2^32
}
END_TEST

START_TEST(test_mul_max_scale) {
  s21_decimal result;
  int code = s21_mul(make_decimal(1, 0, 0, 0x00070000),  // 1e-7
                     make_decimal(1, 0, 0, 0x00070000),  // 1e-7
                     &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(s21_get_scale(&result), 14);  // 1e-14
}
END_TEST

START_TEST(test_mul_negative_negative) {
  s21_decimal result;
  int code = s21_mul(make_decimal(2, 0, 0, 0x80000000),  // -2
                     make_decimal(3, 0, 0, 0x80000000),  // -3
                     &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(s21_get_sign(&result), S21_POS_SIGN);
  ck_assert_int_eq(result.bits[0], 6);
}
END_TEST

START_TEST(test_mul_zero_negative) {
  s21_decimal result;
  int code = s21_mul(make_decimal(0, 0, 0, 0),
                     make_decimal(5, 0, 0, 0x80000000),  // -5
                     &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_mul_small_overflow) {
  s21_decimal a = make_decimal(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00100000);
  s21_decimal b = make_decimal(10, 0, 0, 0x00100000);
  s21_decimal result;
  int code = s21_mul(a, b, &result);
  // Может вернуть OK или переполнение
  ck_assert(code == S21_ARITHMETIC_OK || code == S21_ARITHMETIC_BIG ||
            code == S21_ARITHMETIC_SMALL);
}
END_TEST

// ==================== ТЕСТЫ ДЛЯ s21_div ====================

START_TEST(test_div_basic_6_3) {
  s21_decimal result;
  int code =
      s21_div(make_decimal(6, 0, 0, 0), make_decimal(3, 0, 0, 0), &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(result.bits[0], 2);
}
END_TEST

START_TEST(test_div_by_zero) {
  s21_decimal result;
  int code =
      s21_div(make_decimal(6, 0, 0, 0), make_decimal(0, 0, 0, 0), &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_ZERO_DIV);
}
END_TEST

START_TEST(test_div_zero_by_number) {
  s21_decimal result;
  int code =
      s21_div(make_decimal(0, 0, 0, 0), make_decimal(5, 0, 0, 0), &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_div_negative_positive) {
  s21_decimal result;
  int code = s21_div(make_decimal(6, 0, 0, 0x80000000),  // -6
                     make_decimal(3, 0, 0, 0),           // 3
                     &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(s21_get_sign(&result), S21_NEG_SIGN);
  ck_assert_int_eq(result.bits[0], 2);
}
END_TEST

START_TEST(test_div_positive_negative) {
  s21_decimal result;
  int code = s21_div(make_decimal(6, 0, 0, 0),           // 6
                     make_decimal(3, 0, 0, 0x80000000),  // -3
                     &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(s21_get_sign(&result), S21_NEG_SIGN);
  ck_assert_int_eq(result.bits[0], 2);
}
END_TEST

START_TEST(test_div_negative_negative) {
  s21_decimal result;
  int code = s21_div(make_decimal(6, 0, 0, 0x80000000),  // -6
                     make_decimal(3, 0, 0, 0x80000000),  // -3
                     &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(s21_get_sign(&result), S21_POS_SIGN);
  ck_assert_int_eq(result.bits[0], 2);
}
END_TEST

START_TEST(test_div_with_scale) {
  s21_decimal result;
  int code = s21_div(make_decimal(15, 0, 0, 0x00010000),  // 1.5
                     make_decimal(5, 0, 0, 0x00010000),   // 0.5
                     &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(result.bits[0], 3);
  ck_assert_int_eq(s21_get_scale(&result), 0);
}
END_TEST

START_TEST(test_div_different_scales) {
  s21_decimal result;
  int code = s21_div(make_decimal(15, 0, 0, 0x00010000),  // 1.5
                     make_decimal(25, 0, 0, 0x00020000),  // 0.25
                     &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(result.bits[0], 6);
  ck_assert_int_eq(s21_get_scale(&result), 0);
}
END_TEST

START_TEST(test_div_fractional_result) {
  s21_decimal result;
  int code =
      s21_div(make_decimal(1, 0, 0, 0), make_decimal(3, 0, 0, 0), &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_gt(s21_get_scale(&result), 0);
}
END_TEST

START_TEST(test_div_exact_fractional) {
  s21_decimal result;
  int code =
      s21_div(make_decimal(1, 0, 0, 0), make_decimal(4, 0, 0, 0), &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(result.bits[0], 25);
  ck_assert_int_eq(s21_get_scale(&result), 2);
}
END_TEST

START_TEST(test_div_1_by_2) {
  s21_decimal result;
  int code =
      s21_div(make_decimal(1, 0, 0, 0), make_decimal(2, 0, 0, 0), &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(s21_get_scale(&result), 1);
}
END_TEST

START_TEST(test_div_1_by_10) {
  s21_decimal result;
  int code =
      s21_div(make_decimal(1, 0, 0, 0), make_decimal(10, 0, 0, 0), &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(s21_get_scale(&result), 1);
}
END_TEST

START_TEST(test_div_large_integer) {
  s21_decimal result;
  int code = s21_div(make_decimal(1000000000, 0, 0, 0),
                     make_decimal(2, 0, 0, 0), &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(result.bits[0], 500000000);
}
END_TEST

START_TEST(test_div_scale_in_dividend) {
  s21_decimal result;
  int code = s21_div(make_decimal(100, 0, 0, 0x00020000),  // 1.00
                     make_decimal(2, 0, 0, 0), &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq(s21_get_scale(&result), 2);
}
END_TEST

START_TEST(test_div_scale_in_divisor) {
  s21_decimal result;
  int code = s21_div(make_decimal(1, 0, 0, 0),
                     make_decimal(200, 0, 0, 0x00020000),  // 2.00
                     &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(s21_get_scale(&result), 1);
}
END_TEST

START_TEST(test_div_null_pointer) {
  int code = s21_div(make_decimal(6, 0, 0, 0), make_decimal(3, 0, 0, 0), NULL);
  ck_assert_int_eq(code, S21_ARITHMETIC_ERROR);
}
END_TEST

START_TEST(test_div_invalid_decimal) {
  s21_decimal result;
  int code = s21_div(make_decimal(1, 0, 0, 0x001D0000),  // scale=29
                     make_decimal(2, 0, 0, 0), &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_ERROR);
}
END_TEST

START_TEST(test_div_max_by_1) {
  s21_decimal result;
  s21_decimal max = make_decimal(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0);
  int code = s21_div(max, make_decimal(1, 0, 0, 0), &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_uint_eq((uint32_t)result.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq((uint32_t)result.bits[1], 0xFFFFFFFF);
  ck_assert_uint_eq((uint32_t)result.bits[2], 0xFFFFFFFF);
}
END_TEST

START_TEST(test_div_0_2_by_0_1) {
  s21_decimal result;
  int code = s21_div(make_decimal(2, 0, 0, 0x00010000),  // 0.2
                     make_decimal(1, 0, 0, 0x00010000),  // 0.1
                     &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(s21_get_scale(&result), 0);
}
END_TEST

START_TEST(test_div_0_2_by_0_02) {
  s21_decimal result;
  int code = s21_div(make_decimal(2, 0, 0, 0x00010000),  // 0.2
                     make_decimal(2, 0, 0, 0x00020000),  // 0.02
                     &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq(s21_get_scale(&result), 0);
}
END_TEST

START_TEST(test_div_maximal_divisor) {
  s21_decimal result;
  s21_decimal divisor = make_decimal(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0);
  int code = s21_div(make_decimal(1, 0, 0, 0), divisor, &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_SMALL);
  ck_assert(s21_is_zero(&result) == true);
}
END_TEST

START_TEST(test_div_1e_28_by_1e_28) {
  s21_decimal result;
  s21_decimal small = make_decimal(1, 0, 0, 0x001C0000);  // 1e-28
  int code = s21_div(small, small, &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(s21_get_scale(&result), 0);
}
END_TEST

START_TEST(test_div_max_scale) {
  s21_decimal result;
  s21_decimal a = make_decimal(1, 0, 0, 0x001C0000);  // 1e-28
  s21_decimal b = make_decimal(2, 0, 0, 0x001C0000);  // 2e-28
  int code = s21_div(a, b, &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(s21_get_scale(&result), 1);  // 0.5
}
END_TEST

Suite *s21_add_dragonad_suite(void) {
  Suite *s = suite_create("S21_MULTIPLICATION_AND_DIVISION_SUITE");

  TCase *tc_mul = tcase_create("Multiplication");
  tcase_add_test(tc_mul, test_mul_basic_2x3);
  tcase_add_test(tc_mul, test_mul_by_zero);
  tcase_add_test(tc_mul, test_mul_negative_positive);
  tcase_add_test(tc_mul, test_mul_positive_overflow);
  tcase_add_test(tc_mul, test_mul_negative_overflow);
  tcase_add_test(tc_mul, test_mul_null_pointer);
  tcase_add_test(tc_mul, test_mul_scale_addition);
  tcase_add_test(tc_mul, test_mul_invalid_decimal);
  tcase_add_test(tc_mul, test_mul_inf_operand);
  tcase_add_test(tc_mul, test_mul_decimal_0_5x0_5);
  tcase_add_test(tc_mul, test_mul_large_numbers);
  tcase_add_test(tc_mul, test_mul_max_scale);
  tcase_add_test(tc_mul, test_mul_negative_negative);
  tcase_add_test(tc_mul, test_mul_zero_negative);
  tcase_add_test(tc_mul, test_mul_small_overflow);

  TCase *tc_div = tcase_create("Division");
  tcase_set_timeout(tc_div, 300);
  tcase_add_test(tc_div, test_div_basic_6_3);
  tcase_add_test(tc_div, test_div_by_zero);
  tcase_add_test(tc_div, test_div_zero_by_number);
  tcase_add_test(tc_div, test_div_negative_positive);
  tcase_add_test(tc_div, test_div_positive_negative);
  tcase_add_test(tc_div, test_div_negative_negative);
  tcase_add_test(tc_div, test_div_with_scale);
  tcase_add_test(tc_div, test_div_different_scales);
  tcase_add_test(tc_div, test_div_fractional_result);
  tcase_add_test(tc_div, test_div_exact_fractional);
  tcase_add_test(tc_div, test_div_1_by_2);
  tcase_add_test(tc_div, test_div_1_by_10);
  tcase_add_test(tc_div, test_div_large_integer);
  tcase_add_test(tc_div, test_div_scale_in_dividend);
  tcase_add_test(tc_div, test_div_scale_in_divisor);
  tcase_add_test(tc_div, test_div_null_pointer);
  tcase_add_test(tc_div, test_div_invalid_decimal);
  tcase_add_test(tc_div, test_div_max_by_1);
  tcase_add_test(tc_div, test_div_0_2_by_0_1);
  tcase_add_test(tc_div, test_div_0_2_by_0_02);
  tcase_add_test(tc_div, test_div_maximal_divisor);
  tcase_add_test(tc_div, test_div_1e_28_by_1e_28);
  tcase_add_test(tc_div, test_div_max_scale);

  suite_add_tcase(s, tc_mul);
  suite_add_tcase(s, tc_div);
  return s;
}