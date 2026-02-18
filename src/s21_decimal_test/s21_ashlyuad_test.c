#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "s21_decimal.h"

s21_decimal create_decimal(unsigned int low, unsigned int mid, 
                          unsigned int high, int scale) {
    s21_decimal result;
    result.bits[0] = low;
    result.bits[1] = mid;
    result.bits[2] = high;
    result.bits[3] = (scale << 16);
    return result;
}

START_TEST(sub_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_8) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_9) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_10) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_12) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_13) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_14) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_15) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_16) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_17) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_18) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_19) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_20) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = 100;
  int tmp2 = 99999;
  int res_s21 = 0;
  int res = -99899;
  s21_decimal res1;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(sub_21) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = -100;
  int tmp2 = -99999;
  int res_s21 = 0;
  s21_decimal res1;
  int res = 99899;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(add_0) {
  s21_decimal val1 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_1) {
  s21_decimal val1 = {{15, 0, 0, 0}};
  s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_2) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{1, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_3) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_8) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_9) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_10) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_12) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_13) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_14) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_15) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_16) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_17) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_scale(&val1, 5);
  set_scale(&val2, 3);
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_18) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  set_scale(&val1, 5);
  set_scale(&val2, 3);
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(is_less_1) {
    s21_decimal val1 = {{0, 0, 0, 0}};
    s21_decimal val2 = {{0, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_2) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{10, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_3) {
    s21_decimal val1 = {{10, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_4) {
    s21_decimal val1 = {{10, 0, 0, 0}};
    s21_decimal val2 = {{10, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_5) {
    s21_decimal val1 = {{UINT_MAX, 0, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, 1, 0, 0}};
    ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_6) {
    s21_decimal val1 = {{UINT_MAX, 1, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_7) {
    s21_decimal val1 = {{0, 0, 0, 0}};
    s21_decimal val2 = {{0, 0, 0, 0}};
    set_scale(&val1, 2);
    set_scale(&val2, 1);
    ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_8) {
    s21_decimal val1 = {{100, 0, 0, 0}};
    s21_decimal val2 = {{10, 0, 0, 0}};
    set_scale(&val1, 2);
    set_scale(&val2, 1);
    ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_9) {
    s21_decimal val1 = {{10, 0, 0, 0}};
    s21_decimal val2 = {{100, 0, 0, 0}};
    set_scale(&val1, 1);
    set_scale(&val2, 2);
    ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_10) {
    s21_decimal val1 = {{1, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{1, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_11) {
    s21_decimal val1 = {{1, 0, 0, 0}};
    s21_decimal val2 = {{1, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_12) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{10, 0, 0, 0}};
    set_sign(&val1, 1);
    set_sign(&val2, 1);
    ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_13) {
    s21_decimal val1 = {{10, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_14) {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_15) {
    s21_decimal val1 = {{UINT_MAX - 1, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_16) {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{UINT_MAX - 1, UINT_MAX, UINT_MAX, 0}};
    ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_17) {
    s21_decimal val1 = {{0, 0, 0, 0}};
    s21_decimal val2 = {{0, 0, 0, 0}};
    set_sign(&val1, 1);
    set_sign(&val2, 1);
    ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_18) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    set_scale(&val1, 2);
    set_scale(&val2, 1);
    ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_19) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    set_scale(&val1, 1);
    set_scale(&val2, 2);
    ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_20) {
    s21_decimal val1 = {{0, 1, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_1) {
    s21_decimal val1 = {{0, 0, 0, 0}};
    s21_decimal val2 = {{0, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_2) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{10, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_3) {
    s21_decimal val1 = {{10, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_4) {
    s21_decimal val1 = {{10, 0, 0, 0}};
    s21_decimal val2 = {{10, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_5) {
    s21_decimal val1 = {{UINT_MAX, 0, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, 1, 0, 0}};
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_6) {
    s21_decimal val1 = {{UINT_MAX, 1, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_7) {
    s21_decimal val1 = {{100, 0, 0, 0}};
    s21_decimal val2 = {{100, 0, 0, 0}};
    set_scale(&val1, 2);
    set_scale(&val2, 1);
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_8) {
    s21_decimal val1 = {{100, 0, 0, 0}};
    s21_decimal val2 = {{1000, 0, 0, 0}};
    set_scale(&val1, 1);
    set_scale(&val2, 2);
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_9) {
    s21_decimal val1 = {{150, 0, 0, 0}};
    s21_decimal val2 = {{15, 0, 0, 0}};
    set_scale(&val1, 2);
    set_scale(&val2, 1);
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_10) {
    s21_decimal val1 = {{15, 0, 0, 0}};
    s21_decimal val2 = {{150, 0, 0, 0}};
    set_scale(&val1, 1);
    set_scale(&val2, 2);
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_11) {
    s21_decimal val1 = {{1, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{1, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_12) {
    s21_decimal val1 = {{1, 0, 0, 0}};
    s21_decimal val2 = {{1, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_13) {
    s21_decimal val1 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{10, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_14) {
    s21_decimal val1 = {{10, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_15) {
    s21_decimal val1 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_16) {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_17) {
    s21_decimal val1 = {{UINT_MAX - 1, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_18) {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{UINT_MAX - 1, UINT_MAX, UINT_MAX, 0}};
    ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_19) {
    s21_decimal val1 = {{0, 0, 0, 0}};
    s21_decimal val2 = {{0, 0, 0, 0}};
    set_sign(&val1, 1);
    set_sign(&val2, 1);
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_20) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    set_scale(&val1, 2);
    set_scale(&val2, 1);
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_21) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    set_scale(&val1, 1);
    set_scale(&val2, 2);
    ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_22) {
    s21_decimal val1 = {{0, 1, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_23) {
    s21_decimal val1 = {{UINT_MAX, 0, 0, 0}};
    s21_decimal val2 = {{0, 1, 0, 0}};
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_24) {
    s21_decimal val1 = {{100, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{10, 0, 0, 0}};
    set_scale(&val1, 1);
    set_scale(&val2, 0);
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_25) {
    s21_decimal val1 = {{10, 0, 0, 0}};
    s21_decimal val2 = {{100, 0, 0, ~(UINT_MAX / 2)}};
    set_scale(&val1, 0);
    set_scale(&val2, 1);
    ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_26) {
    s21_decimal val1 = {{100, 0, 0, 0}};
    s21_decimal val2 = {{10000, 0, 0, 0}};
    set_scale(&val1, 1);
    set_scale(&val2, 3);
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_27) {
    s21_decimal val1 = {{1, 0, 0, 0}};
    s21_decimal val2 = {{1000000, 0, 0, 0}};
    set_scale(&val1, 0);
    set_scale(&val2, 6);
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_28) {
    s21_decimal val1 = {{150, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
    set_scale(&val1, 2);
    set_scale(&val2, 1);
    ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_1) {
    s21_decimal val1 = {{0, 0, 0, 0}};
    s21_decimal val2 = {{0, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_2) {
    s21_decimal val1 = {{10, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_3) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{10, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_4) {
    s21_decimal val1 = {{10, 0, 0, 0}};
    s21_decimal val2 = {{10, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_5) {
    s21_decimal val1 = {{UINT_MAX, 1, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_6) {
    s21_decimal val1 = {{UINT_MAX, 0, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, 1, 0, 0}};
    ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_7) {
    s21_decimal val1 = {{100, 0, 0, 0}};
    s21_decimal val2 = {{100, 0, 0, 0}};
    set_scale(&val1, 1);
    set_scale(&val2, 2);
    ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_8) {
    s21_decimal val1 = {{100, 0, 0, 0}};
    s21_decimal val2 = {{1000, 0, 0, 0}};
    set_scale(&val1, 1);
    set_scale(&val2, 2);
    ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_9) {
    s21_decimal val1 = {{150, 0, 0, 0}};
    s21_decimal val2 = {{15, 0, 0, 0}};
    set_scale(&val1, 2);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(0, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_10) {
    s21_decimal val1 = {{151, 0, 0, 0}};
    s21_decimal val2 = {{15, 0, 0, 0}};
    set_scale(&val1, 2);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(1, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_11) {
    s21_decimal val1 = {{1, 0, 0, 0}};
    s21_decimal val2 = {{1, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(1, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_12) {
    s21_decimal val1 = {{1, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{1, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_13) {
    s21_decimal val1 = {{10, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(0, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_14) {
    s21_decimal val1 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{10, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(1, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_15) {
    s21_decimal val1 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(0, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_16) {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    ck_assert_int_eq(0, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_17) {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{UINT_MAX - 1, UINT_MAX, UINT_MAX, 0}};
    ck_assert_int_eq(1, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_18) {
    s21_decimal val1 = {{UINT_MAX - 1, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    ck_assert_int_eq(0, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_19) {
    s21_decimal val1 = {{0, 0, 0, 0}};
    s21_decimal val2 = {{0, 0, 0, 0}};
    set_sign(&val1, 1);
    set_sign(&val2, 1);
    ck_assert_int_eq(0, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_20) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    set_scale(&val1, 1);   
    set_scale(&val2, 2);   
    ck_assert_int_eq(1, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_21) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    set_scale(&val1, 2);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(0, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_22) {
    s21_decimal val1 = {{0, 1, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_23) {
    s21_decimal val1 = {{UINT_MAX, 0, 0, 0}};
    s21_decimal val2 = {{0, 1, 0, 0}};
    ck_assert_int_eq(0, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_24) {
    s21_decimal val1 = {{10, 0, 0, 0}};
    s21_decimal val2 = {{100, 0, 0, ~(UINT_MAX / 2)}};
    set_scale(&val1, 0);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(1, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_25) {
    s21_decimal val1 = {{100, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{10, 0, 0, 0}};
    set_scale(&val1, 1);   
    set_scale(&val2, 0);   
    ck_assert_int_eq(0, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_26) {
    s21_decimal val1 = {{100, 0, 0, 0}};
    s21_decimal val2 = {{10000, 0, 0, 0}};
    set_scale(&val1, 1);   
    set_scale(&val2, 3);   
    ck_assert_int_eq(0, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_27) {
    s21_decimal val1 = {{1, 0, 0, 0}};
    s21_decimal val2 = {{1000000, 0, 0, 0}};
    set_scale(&val1, 0);   
    set_scale(&val2, 6);   
    ck_assert_int_eq(0, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_28) {
    s21_decimal val1 = {{2, 0, 0, 0}};
    s21_decimal val2 = {{1000000, 0, 0, 0}};
    set_scale(&val1, 0);   
    set_scale(&val2, 6);   
    ck_assert_int_eq(1, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_29) {
     
    s21_decimal val1 = {{149, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
    set_scale(&val1, 2);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(1, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_30) {
     
    s21_decimal val1 = {{151, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
    set_scale(&val1, 2);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(0, s21_is_greater(val1, val2));  
}
END_TEST

START_TEST(is_greater_31) {
     
    s21_decimal val1 = {{0, 0, 0, 0}};
    s21_decimal val2 = {{0, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_32) {
     
    s21_decimal val1 = {{0, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{0, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_33) {
     
    s21_decimal val1 = {{0x5A126E1D, 0x5E8A1B91, 0x204FCE5E, 0}};  
    s21_decimal val2 = {{0x5A126E1C, 0x5E8A1B91, 0x204FCE5E, 0}};  
    ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_34) {
     
    s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  
    s21_decimal val2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, ~(UINT_MAX / 2)}};  
    ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_1) {
    s21_decimal val1 = {{0, 0, 0, 0}};
    s21_decimal val2 = {{0, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_2) {
    s21_decimal val1 = {{10, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_3) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{10, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_4) {
    s21_decimal val1 = {{10, 0, 0, 0}};
    s21_decimal val2 = {{10, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_5) {
    s21_decimal val1 = {{UINT_MAX, 1, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_6) {
    s21_decimal val1 = {{UINT_MAX, 0, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, 1, 0, 0}};
    ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_7) {
    s21_decimal val1 = {{100, 0, 0, 0}};
    s21_decimal val2 = {{100, 0, 0, 0}};
    set_scale(&val1, 1);   
    set_scale(&val2, 2);   
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_8) {
    s21_decimal val1 = {{100, 0, 0, 0}};
    s21_decimal val2 = {{1000, 0, 0, 0}};
    set_scale(&val1, 1);   
    set_scale(&val2, 2);   
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_9) {
    s21_decimal val1 = {{150, 0, 0, 0}};
    s21_decimal val2 = {{15, 0, 0, 0}};
    set_scale(&val1, 2);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_10) {
    s21_decimal val1 = {{149, 0, 0, 0}};
    s21_decimal val2 = {{15, 0, 0, 0}};
    set_scale(&val1, 2);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_11) {
    s21_decimal val1 = {{1, 0, 0, 0}};
    s21_decimal val2 = {{1, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_12) {
    s21_decimal val1 = {{1, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{1, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_13) {
    s21_decimal val1 = {{10, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_14) {
    s21_decimal val1 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{10, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_15) {
    s21_decimal val1 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_16) {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_17) {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{UINT_MAX - 1, UINT_MAX, UINT_MAX, 0}};
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_18) {
    s21_decimal val1 = {{UINT_MAX - 1, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_19) {
    s21_decimal val1 = {{0, 0, 0, 0}};
    s21_decimal val2 = {{0, 0, 0, 0}};
    set_sign(&val1, 1);
    set_sign(&val2, 1);
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_20) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    set_scale(&val1, 1);   
    set_scale(&val2, 2);   
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_21) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    set_scale(&val1, 2);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_22) {
    s21_decimal val1 = {{0, 1, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_23) {
    s21_decimal val1 = {{UINT_MAX, 0, 0, 0}};
    s21_decimal val2 = {{0, 1, 0, 0}};
    ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_24) {
    s21_decimal val1 = {{10, 0, 0, 0}};
    s21_decimal val2 = {{100, 0, 0, ~(UINT_MAX / 2)}};
    set_scale(&val1, 0);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_25) {
    s21_decimal val1 = {{100, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{10, 0, 0, 0}};
    set_scale(&val1, 1);   
    set_scale(&val2, 0);   
    ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_26) {
    s21_decimal val1 = {{100, 0, 0, 0}};
    s21_decimal val2 = {{10000, 0, 0, 0}};
    set_scale(&val1, 1);   
    set_scale(&val2, 3);   
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_27) {
    s21_decimal val1 = {{1, 0, 0, 0}};
    s21_decimal val2 = {{1000000, 0, 0, 0}};
    set_scale(&val1, 0);   
    set_scale(&val2, 6);   
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_28) {
    s21_decimal val1 = {{2, 0, 0, 0}};
    s21_decimal val2 = {{1000000, 0, 0, 0}};
    set_scale(&val1, 0);   
    set_scale(&val2, 6);   
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_29) {
     
    s21_decimal val1 = {{149, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
    set_scale(&val1, 2);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_30) {
     
    s21_decimal val1 = {{151, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
    set_scale(&val1, 2);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_greater_or_equal_31) {
     
    s21_decimal val1 = {{0, 0, 0, 0}};
    s21_decimal val2 = {{0, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_32) {
     
    s21_decimal val1 = {{0, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{0, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_33) {
     
    s21_decimal val1 = {{0x5A126E1D, 0x5E8A1B91, 0x204FCE5E, 0}};  
    s21_decimal val2 = {{0x5A126E1C, 0x5E8A1B91, 0x204FCE5E, 0}};  
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_34) {
     
    s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  
    s21_decimal val2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, ~(UINT_MAX / 2)}};  
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_35) {
     
    s21_decimal val1 = {{150, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
    set_scale(&val1, 2);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_36) {
     
    s21_decimal val1 = {{1, 0, 0, 0}};
    s21_decimal val2 = {{0, 0, 0, 0}};
    set_scale(&val1, 28);   
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_37) {
     
    s21_decimal val1 = {{0, 0, 0, 0}};
    s21_decimal val2 = {{1, 0, 0, ~(UINT_MAX / 2)}};
    set_scale(&val2, 28);   
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_38) {
     
    s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_1) {
    s21_decimal val1 = {{0, 0, 0, 0}};
    s21_decimal val2 = {{0, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_2) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_3) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{10, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_4) {
    s21_decimal val1 = {{10, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_5) {
    s21_decimal val1 = {{UINT_MAX, 0, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_6) {
    s21_decimal val1 = {{UINT_MAX, 0, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, 1, 0, 0}};
    ck_assert_int_eq(0, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_7) {
    s21_decimal val1 = {{100, 0, 0, 0}};
    s21_decimal val2 = {{100, 0, 0, 0}};
    set_scale(&val1, 2);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(0, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_8) {
    s21_decimal val1 = {{100, 0, 0, 0}};
    s21_decimal val2 = {{1000, 0, 0, 0}};
    set_scale(&val1, 1);   
    set_scale(&val2, 2);   
    ck_assert_int_eq(1, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_9) {
    s21_decimal val1 = {{150, 0, 0, 0}};
    s21_decimal val2 = {{15, 0, 0, 0}};
    set_scale(&val1, 2);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(1, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_10) {
    s21_decimal val1 = {{151, 0, 0, 0}};
    s21_decimal val2 = {{15, 0, 0, 0}};
    set_scale(&val1, 2);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(0, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_11) {
    s21_decimal val1 = {{1, 0, 0, 0}};
    s21_decimal val2 = {{1, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(0, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_12) {
    s21_decimal val1 = {{1, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{1, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(1, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_13) {
    s21_decimal val1 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{10, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(0, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_14) {
    s21_decimal val1 = {{10, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(0, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_15) {
    s21_decimal val1 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(1, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_16) {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    ck_assert_int_eq(1, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_17) {
    s21_decimal val1 = {{UINT_MAX - 1, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    ck_assert_int_eq(0, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_18) {
    s21_decimal val1 = {{0, 0, 0, 0}};
    s21_decimal val2 = {{0, 0, 0, 0}};
    set_sign(&val1, 1);
    set_sign(&val2, 1);
    ck_assert_int_eq(1, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_19) {
    s21_decimal val1 = {{0, 0, 0, 0}};
    s21_decimal val2 = {{0, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(1, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_20) {
    s21_decimal val1 = {{0, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{0, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_21) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    set_scale(&val1, 2);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(0, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_22) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    set_scale(&val1, 1);   
    set_scale(&val2, 2);   
    ck_assert_int_eq(0, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_23) {
    s21_decimal val1 = {{0, 1, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_24) {
    s21_decimal val1 = {{UINT_MAX, 0, 0, 0}};
    s21_decimal val2 = {{0, 1, 0, 0}};
    ck_assert_int_eq(0, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_25) {
    s21_decimal val1 = {{0, 1, 0, 0}};
    s21_decimal val2 = {{0, 1, 0, 0}};
    ck_assert_int_eq(1, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_26) {
    s21_decimal val1 = {{10, 0, 0, 0}};
    s21_decimal val2 = {{100, 0, 0, ~(UINT_MAX / 2)}};
    set_scale(&val1, 0);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(0, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_27) {
    s21_decimal val1 = {{100, 0, 0, 0}};
    s21_decimal val2 = {{100, 0, 0, 0}};
    set_scale(&val1, 1);   
    set_scale(&val2, 3);   
    ck_assert_int_eq(0, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_28) {
    s21_decimal val1 = {{1, 0, 0, 0}};
    s21_decimal val2 = {{1000000, 0, 0, 0}};
    set_scale(&val1, 0);   
    set_scale(&val2, 6);   
    ck_assert_int_eq(1, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_29) {
    s21_decimal val1 = {{2, 0, 0, 0}};
    s21_decimal val2 = {{1000000, 0, 0, 0}};
    set_scale(&val1, 0);   
    set_scale(&val2, 6);   
    ck_assert_int_eq(0, s21_is_equal(val1, val2));  
}
END_TEST

START_TEST(is_equal_30) {
     
    s21_decimal val1 = {{149, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
    set_scale(&val1, 2);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_31) {
     
    s21_decimal val1 = {{150, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
    set_scale(&val1, 2);   
    set_scale(&val2, 1);   
    ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_32) {
     
    s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    s21_decimal val2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_33) {
    s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    s21_decimal val2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_34) {
    s21_decimal val1 = {{12345, 0, 0, 0}};
    s21_decimal val2 = {{12345, 0, 0, 0}};
    set_scale(&val1, 2);
    set_scale(&val2, 3);
    ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_35) {
    s21_decimal val1 = {{1, 0, 0, 0}};
    s21_decimal val2 = {{1, 0, 0, 0}};
    set_scale(&val1, 28);
    set_scale(&val2, 28);
    ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_36) {
    s21_decimal val1 = {{123450, 0, 0, 0}};
    s21_decimal val2 = {{12345, 0, 0, 0}};
    set_scale(&val1, 3);
    set_scale(&val2, 2);
    ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_37) {
    s21_decimal val1 = {{0x99999999, 0x99999999, 0x19999999, 0}};
    s21_decimal val2 = {{0x99999999, 0x99999999, 0x19999999, 0}};
    set_scale(&val1, 5);
    set_scale(&val2, 10);
    ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_38) {
    s21_decimal val1 = {{123456789, 0, 0, 0}};
    s21_decimal val2 = {{123456789, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_1) {
    s21_decimal val1 = {{0, 0, 0, 0}};
    s21_decimal val2 = {{0, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_2) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_3) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{10, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_4) {
    s21_decimal val1 = {{10, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_5) {
    s21_decimal val1 = {{UINT_MAX, 0, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_6) {
    s21_decimal val1 = {{UINT_MAX, 0, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, 1, 0, 0}};
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_7) {
    s21_decimal val1 = {{100, 0, 0, 0}};
    s21_decimal val2 = {{100, 0, 0, 0}};
    set_scale(&val1, 2);
    set_scale(&val2, 1);
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_8) {
    s21_decimal val1 = {{100, 0, 0, 0}};
    s21_decimal val2 = {{1000, 0, 0, 0}};
    set_scale(&val1, 1);
    set_scale(&val2, 2);
    ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_9) {
    s21_decimal val1 = {{150, 0, 0, 0}};
    s21_decimal val2 = {{15, 0, 0, 0}};
    set_scale(&val1, 2);
    set_scale(&val2, 1);
    ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_10) {
    s21_decimal val1 = {{151, 0, 0, 0}};
    s21_decimal val2 = {{15, 0, 0, 0}};
    set_scale(&val1, 2);
    set_scale(&val2, 1);
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_11) {
    s21_decimal val1 = {{1, 0, 0, 0}};
    s21_decimal val2 = {{1, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_12) {
    s21_decimal val1 = {{1, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{1, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_13) {
    s21_decimal val1 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{10, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_14) {
    s21_decimal val1 = {{10, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_15) {
    s21_decimal val1 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{5, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_16) {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_17) {
    s21_decimal val1 = {{UINT_MAX - 1, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_18) {
    s21_decimal val1 = {{0, 0, 0, 0}};
    s21_decimal val2 = {{0, 0, 0, 0}};
    set_sign(&val1, 1);
    set_sign(&val2, 1);
    ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_19) {
    s21_decimal val1 = {{0, 0, 0, 0}};
    s21_decimal val2 = {{0, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_20) {
    s21_decimal val1 = {{0, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{0, 0, 0, 0}};
    ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_21) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    set_scale(&val1, 2);
    set_scale(&val2, 1);
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_22) {
    s21_decimal val1 = {{5, 0, 0, 0}};
    s21_decimal val2 = {{5, 0, 0, 0}};
    set_scale(&val1, 1);
    set_scale(&val2, 2);
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_23) {
    s21_decimal val1 = {{0, 1, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, 0, 0, 0}};
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_24) {
    s21_decimal val1 = {{UINT_MAX, 0, 0, 0}};
    s21_decimal val2 = {{0, 1, 0, 0}};
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_25) {
    s21_decimal val1 = {{0, 1, 0, 0}};
    s21_decimal val2 = {{0, 1, 0, 0}};
    ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_26) {
    s21_decimal val1 = {{10, 0, 0, 0}};
    s21_decimal val2 = {{100, 0, 0, ~(UINT_MAX / 2)}};
    set_scale(&val1, 0);
    set_scale(&val2, 1);
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_27) {
    s21_decimal val1 = {{100, 0, 0, 0}};
    s21_decimal val2 = {{100, 0, 0, 0}};
    set_scale(&val1, 1);
    set_scale(&val2, 3);
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_28) {
    s21_decimal val1 = {{1, 0, 0, 0}};
    s21_decimal val2 = {{1000000, 0, 0, 0}};
    set_scale(&val1, 0);
    set_scale(&val2, 6);
    ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_29) {
    s21_decimal val1 = {{2, 0, 0, 0}};
    s21_decimal val2 = {{1000000, 0, 0, 0}};
    set_scale(&val1, 0);
    set_scale(&val2, 6);
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_30) {
    s21_decimal val1 = {{149, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
    set_scale(&val1, 2);
    set_scale(&val2, 1);
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_31) {
    s21_decimal val1 = {{150, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
    set_scale(&val1, 2);
    set_scale(&val2, 1);
    ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_32) {
    s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    s21_decimal val2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_33) {
    s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    s21_decimal val2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_34) {
    s21_decimal val1 = {{12345, 0, 0, 0}};
    s21_decimal val2 = {{12345, 0, 0, 0}};
    set_scale(&val1, 2);
    set_scale(&val2, 3);
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_35) {
    s21_decimal val1 = {{1, 0, 0, 0}};
    s21_decimal val2 = {{1, 0, 0, 0}};
    set_scale(&val1, 28);
    set_scale(&val2, 28);
    ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_36) {
    s21_decimal val1 = {{123450, 0, 0, 0}};
    s21_decimal val2 = {{12345, 0, 0, 0}};
    set_scale(&val1, 3);
    set_scale(&val2, 2);
    ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_37) {
    s21_decimal val1 = {{0x99999999, 0x99999999, 0x19999999, 0}};
    s21_decimal val2 = {{0x99999999, 0x99999999, 0x19999999, 0}};
    set_scale(&val1, 5);
    set_scale(&val2, 10);
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_38) {
    s21_decimal val1 = {{123456789, 0, 0, 0}};
    s21_decimal val2 = {{123456789, 0, 0, ~(UINT_MAX / 2)}};
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_39) {
    s21_decimal val1 = {{555, 0, 0, 0}};
    s21_decimal val2 = {{555, 0, 0, 0}};
    set_scale(&val1, 2);
    set_scale(&val2, 2);
    ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_40) {
    s21_decimal val1 = {{555, 0, 0, 0}};
    s21_decimal val2 = {{556, 0, 0, 0}};
    set_scale(&val1, 2);
    set_scale(&val2, 2);
    ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

Suite* s21_decimal_suite(void) {
    Suite* suite = suite_create("s21_decimal");
    
    TCase *tc_sub = tcase_create("tc_sub");
    tcase_add_test(tc_sub, sub_0);
    tcase_add_test(tc_sub, sub_1);
    tcase_add_test(tc_sub, sub_2);
    tcase_add_test(tc_sub, sub_3);
    tcase_add_test(tc_sub, sub_4);
    tcase_add_test(tc_sub, sub_5);
    tcase_add_test(tc_sub, sub_6);
    tcase_add_test(tc_sub, sub_7);
    tcase_add_test(tc_sub, sub_8);
    tcase_add_test(tc_sub, sub_9);
    tcase_add_test(tc_sub, sub_10);
    tcase_add_test(tc_sub, sub_11);
    tcase_add_test(tc_sub, sub_12);
    tcase_add_test(tc_sub, sub_13);
    tcase_add_test(tc_sub, sub_14);
    tcase_add_test(tc_sub, sub_15);
    tcase_add_test(tc_sub, sub_16);
    tcase_add_test(tc_sub, sub_17);
    tcase_add_test(tc_sub, sub_18);
    tcase_add_test(tc_sub, sub_19);
    tcase_add_test(tc_sub, sub_20);
    tcase_add_test(tc_sub, sub_21);

    TCase* tc_add = tcase_create("tc_add");
    tcase_add_test(tc_add, add_0);
    tcase_add_test(tc_add, add_1);
    tcase_add_test(tc_add, add_2);
    tcase_add_test(tc_add, add_3);
    tcase_add_test(tc_add, add_4);
    tcase_add_test(tc_add, add_5);
    tcase_add_test(tc_add, add_6);
    tcase_add_test(tc_add, add_7);
    tcase_add_test(tc_add, add_8);
    tcase_add_test(tc_add, add_9);
    tcase_add_test(tc_add, add_10);
    tcase_add_test(tc_add, add_11);
    tcase_add_test(tc_add, add_12);
    tcase_add_test(tc_add, add_13);
    tcase_add_test(tc_add, add_14);
    tcase_add_test(tc_add, add_15);
    tcase_add_test(tc_add, add_16);
    tcase_add_test(tc_add, add_17);
    tcase_add_test(tc_add, add_18);

    TCase *tc_is_less = tcase_create("tc_is_less");
    tcase_add_test(tc_is_less, is_less_1);
    tcase_add_test(tc_is_less, is_less_2);
    tcase_add_test(tc_is_less, is_less_3);
    tcase_add_test(tc_is_less, is_less_4);
    tcase_add_test(tc_is_less, is_less_5);
    tcase_add_test(tc_is_less, is_less_6);
    tcase_add_test(tc_is_less, is_less_7);
    tcase_add_test(tc_is_less, is_less_8);
    tcase_add_test(tc_is_less, is_less_9);
    tcase_add_test(tc_is_less, is_less_10);
    tcase_add_test(tc_is_less, is_less_11);
    tcase_add_test(tc_is_less, is_less_12);
    tcase_add_test(tc_is_less, is_less_13);
    tcase_add_test(tc_is_less, is_less_14);
    tcase_add_test(tc_is_less, is_less_15);
    tcase_add_test(tc_is_less, is_less_16);
    tcase_add_test(tc_is_less, is_less_17);
    tcase_add_test(tc_is_less, is_less_18);
    tcase_add_test(tc_is_less, is_less_19);
    tcase_add_test(tc_is_less, is_less_20);

    TCase *tc_is_less_or_equal = tcase_create("tc_is_less_or_equal");
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_1);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_2);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_3);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_4);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_5);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_6);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_7);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_8);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_9);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_10);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_11);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_12);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_13);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_14);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_15);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_16);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_17);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_18);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_19);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_20);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_21);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_22);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_23);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_24);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_25);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_26);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_27);
    tcase_add_test(tc_is_less_or_equal, is_less_or_equal_28);

    TCase *tc_is_greater = tcase_create("tc_is_greater");
    tcase_add_test(tc_is_greater, is_greater_1);
    tcase_add_test(tc_is_greater, is_greater_2);
    tcase_add_test(tc_is_greater, is_greater_3);
    tcase_add_test(tc_is_greater, is_greater_4);
    tcase_add_test(tc_is_greater, is_greater_5);
    tcase_add_test(tc_is_greater, is_greater_6);
    tcase_add_test(tc_is_greater, is_greater_7);
    tcase_add_test(tc_is_greater, is_greater_8);
    tcase_add_test(tc_is_greater, is_greater_9);
    tcase_add_test(tc_is_greater, is_greater_10);
    tcase_add_test(tc_is_greater, is_greater_11);
    tcase_add_test(tc_is_greater, is_greater_12);
    tcase_add_test(tc_is_greater, is_greater_13);
    tcase_add_test(tc_is_greater, is_greater_14);
    tcase_add_test(tc_is_greater, is_greater_15);
    tcase_add_test(tc_is_greater, is_greater_16);
    tcase_add_test(tc_is_greater, is_greater_17);
    tcase_add_test(tc_is_greater, is_greater_18);
    tcase_add_test(tc_is_greater, is_greater_19);
    tcase_add_test(tc_is_greater, is_greater_20);
    tcase_add_test(tc_is_greater, is_greater_21);
    tcase_add_test(tc_is_greater, is_greater_22);
    tcase_add_test(tc_is_greater, is_greater_23);
    tcase_add_test(tc_is_greater, is_greater_24);
    tcase_add_test(tc_is_greater, is_greater_25);
    tcase_add_test(tc_is_greater, is_greater_26);
    tcase_add_test(tc_is_greater, is_greater_27);
    tcase_add_test(tc_is_greater, is_greater_28);
    tcase_add_test(tc_is_greater, is_greater_29);
    tcase_add_test(tc_is_greater, is_greater_30);
    tcase_add_test(tc_is_greater, is_greater_31);
    tcase_add_test(tc_is_greater, is_greater_32);
    tcase_add_test(tc_is_greater, is_greater_33);
    tcase_add_test(tc_is_greater, is_greater_34);

    TCase *tc_is_greater_or_equal = tcase_create("tc_is_greater_or_equal");
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_1);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_2);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_3);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_4);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_5);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_6);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_7);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_8);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_9);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_10);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_11);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_12);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_13);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_14);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_15);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_16);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_17);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_18);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_19);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_20);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_21);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_22);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_23);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_24);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_25);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_26);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_27);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_28);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_29);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_30);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_31);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_32);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_33);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_34);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_35);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_36);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_37);
    tcase_add_test(tc_is_greater_or_equal, is_greater_or_equal_38);

    TCase *tc_is_equal = tcase_create("tc_is_equal");
    tcase_add_test(tc_is_equal, is_equal_1);
    tcase_add_test(tc_is_equal, is_equal_2);
    tcase_add_test(tc_is_equal, is_equal_3);
    tcase_add_test(tc_is_equal, is_equal_4);
    tcase_add_test(tc_is_equal, is_equal_5);
    tcase_add_test(tc_is_equal, is_equal_6);
    tcase_add_test(tc_is_equal, is_equal_7);
    tcase_add_test(tc_is_equal, is_equal_8);
    tcase_add_test(tc_is_equal, is_equal_9);
    tcase_add_test(tc_is_equal, is_equal_10);
    tcase_add_test(tc_is_equal, is_equal_11);
    tcase_add_test(tc_is_equal, is_equal_12);
    tcase_add_test(tc_is_equal, is_equal_13);
    tcase_add_test(tc_is_equal, is_equal_14);
    tcase_add_test(tc_is_equal, is_equal_15);
    tcase_add_test(tc_is_equal, is_equal_16);
    tcase_add_test(tc_is_equal, is_equal_17);
    tcase_add_test(tc_is_equal, is_equal_18);
    tcase_add_test(tc_is_equal, is_equal_19);
    tcase_add_test(tc_is_equal, is_equal_20);
    tcase_add_test(tc_is_equal, is_equal_21);
    tcase_add_test(tc_is_equal, is_equal_22);
    tcase_add_test(tc_is_equal, is_equal_23);
    tcase_add_test(tc_is_equal, is_equal_24);
    tcase_add_test(tc_is_equal, is_equal_25);
    tcase_add_test(tc_is_equal, is_equal_26);
    tcase_add_test(tc_is_equal, is_equal_27);
    tcase_add_test(tc_is_equal, is_equal_28);
    tcase_add_test(tc_is_equal, is_equal_29);
    tcase_add_test(tc_is_equal, is_equal_30);
    tcase_add_test(tc_is_equal, is_equal_31);
    tcase_add_test(tc_is_equal, is_equal_32);
    tcase_add_test(tc_is_equal, is_equal_33);
    tcase_add_test(tc_is_equal, is_equal_34);
    tcase_add_test(tc_is_equal, is_equal_35);
    tcase_add_test(tc_is_equal, is_equal_36);
    tcase_add_test(tc_is_equal, is_equal_37);
    tcase_add_test(tc_is_equal, is_equal_38);

    TCase *tc_is_not_equal = tcase_create("tc_is_not_equal");
    tcase_add_test(tc_is_not_equal, is_not_equal_1);
    tcase_add_test(tc_is_not_equal, is_not_equal_2);
    tcase_add_test(tc_is_not_equal, is_not_equal_3);
    tcase_add_test(tc_is_not_equal, is_not_equal_4);
    tcase_add_test(tc_is_not_equal, is_not_equal_5);
    tcase_add_test(tc_is_not_equal, is_not_equal_6);
    tcase_add_test(tc_is_not_equal, is_not_equal_7);
    tcase_add_test(tc_is_not_equal, is_not_equal_8);
    tcase_add_test(tc_is_not_equal, is_not_equal_9);
    tcase_add_test(tc_is_not_equal, is_not_equal_10);
    tcase_add_test(tc_is_not_equal, is_not_equal_11);
    tcase_add_test(tc_is_not_equal, is_not_equal_12);
    tcase_add_test(tc_is_not_equal, is_not_equal_13);
    tcase_add_test(tc_is_not_equal, is_not_equal_14);
    tcase_add_test(tc_is_not_equal, is_not_equal_15);
    tcase_add_test(tc_is_not_equal, is_not_equal_16);
    tcase_add_test(tc_is_not_equal, is_not_equal_17);
    tcase_add_test(tc_is_not_equal, is_not_equal_18);
    tcase_add_test(tc_is_not_equal, is_not_equal_19);
    tcase_add_test(tc_is_not_equal, is_not_equal_20);
    tcase_add_test(tc_is_not_equal, is_not_equal_21);
    tcase_add_test(tc_is_not_equal, is_not_equal_22);
    tcase_add_test(tc_is_not_equal, is_not_equal_23);
    tcase_add_test(tc_is_not_equal, is_not_equal_24);
    tcase_add_test(tc_is_not_equal, is_not_equal_25);
    tcase_add_test(tc_is_not_equal, is_not_equal_26);
    tcase_add_test(tc_is_not_equal, is_not_equal_27);
    tcase_add_test(tc_is_not_equal, is_not_equal_28);
    tcase_add_test(tc_is_not_equal, is_not_equal_29);
    tcase_add_test(tc_is_not_equal, is_not_equal_30);
    tcase_add_test(tc_is_not_equal, is_not_equal_31);
    tcase_add_test(tc_is_not_equal, is_not_equal_32);
    tcase_add_test(tc_is_not_equal, is_not_equal_33);
    tcase_add_test(tc_is_not_equal, is_not_equal_34);
    tcase_add_test(tc_is_not_equal, is_not_equal_35);
    tcase_add_test(tc_is_not_equal, is_not_equal_36);
    tcase_add_test(tc_is_not_equal, is_not_equal_37);
    tcase_add_test(tc_is_not_equal, is_not_equal_38);
    tcase_add_test(tc_is_not_equal, is_not_equal_39);
    tcase_add_test(tc_is_not_equal, is_not_equal_40);
    
    suite_add_tcase(suite, tc_sub);
    suite_add_tcase(suite, tc_add);
    suite_add_tcase(suite, tc_is_less);
    suite_add_tcase(suite, tc_is_less_or_equal);
    suite_add_tcase(suite, tc_is_greater);
    suite_add_tcase(suite, tc_is_greater_or_equal);
    suite_add_tcase(suite, tc_is_equal);
    suite_add_tcase(suite, tc_is_not_equal);

    return suite;
}

