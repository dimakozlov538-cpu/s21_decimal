#include <check.h>
#include <stddef.h>

#include "s21_decimal.h"

#define SCALE(x) (x << 16)

// ========================
// TEST DATA
// ========================
typedef struct {
    float input;
    int exp_return_value;
    s21_decimal exp_result;
} test_data_t;

static const test_data_t test_data[] = {
    // --- Слишком маленький модуль ---
    {1e-29f, S21_CONVERSION_ERROR, {{0}}},    // 0
    {1e-30f, S21_CONVERSION_ERROR, {{0}}},    // 1
    {-1e-29f, S21_CONVERSION_ERROR, {{0}}},   // 2
    {FLT_MIN, S21_CONVERSION_ERROR, {{0}}},   // 3
    {-FLT_MIN, S21_CONVERSION_ERROR, {{0}}},  // 4
    // --- Слишком большой модуль ---
    {7.93e28f, S21_CONVERSION_ERROR, {{0}}},   // 5
    {-7.93e28f, S21_CONVERSION_ERROR, {{0}}},  // 6
    {INFINITY, S21_CONVERSION_ERROR, {{0}}},   // 7
    {-INFINITY, S21_CONVERSION_ERROR, {{0}}},  // 8
    // --- NaN ---
    {NAN, S21_CONVERSION_ERROR, {{0}}},  // 9
    // --- Пограничные случаи ---
    // --- Округление ---
    {1234567.0f,
     S21_CONVERSION_OK,
     {{1234567, 0, 0, S21_SIGN_POSITIVE}}},  // 10 Ровно 7 цифр - должно точно преобразоваться
    {1234567.8f, S21_CONVERSION_OK, {{1234568, 0, 0, S21_SIGN_POSITIVE}}},  // 11 8 цифр - должно округлиться
    {1234567.5f,
     S21_CONVERSION_OK,
     {{1234568, 0, 0, S21_SIGN_POSITIVE}}},  // 12 Ровно посередине - банковское округление вверх
    {1234568.5f,
     S21_CONVERSION_OK,
     {{1234568, 0, 0, S21_SIGN_POSITIVE}}},  // 13  Ровно посередине - банковское округление вниз
    // --- Ноль и близкие к нулю ---
    {0.0f, S21_CONVERSION_OK, {{0}}},                                          // 14
    {-0.0f, S21_CONVERSION_OK, {{0, 0, 0, S21_SIGN_NEGATIVE}}},                // 15
    {1e-28f, S21_CONVERSION_OK, {{1, 0, 0, SCALE(28) | S21_SIGN_POSITIVE}}},   // 16
    {-1e-28f, S21_CONVERSION_OK, {{1, 0, 0, SCALE(28) | S21_SIGN_NEGATIVE}}},  // 17
    // --- Нормальные случаи ---
    // --- Целые числа ---
    {1.0f, S21_CONVERSION_OK, {{1, 0, 0, S21_SIGN_POSITIVE}}},                                   // 18
    {-1.0f, S21_CONVERSION_OK, {{1, 0, 0, S21_SIGN_NEGATIVE}}},                                  // 19
    {21.0f, S21_CONVERSION_OK, {{21, 0, 0, S21_SIGN_POSITIVE}}},                                 // 20
    {123456.0f, S21_CONVERSION_OK, {{123456, 0, 0, S21_SIGN_POSITIVE}}},                         // 21
    {1.234567e19f, S21_CONVERSION_OK, {{1882349568U, 2874450292U, 0, S21_SIGN_POSITIVE}}},       // 22
    {1.234567e25f, S21_CONVERSION_OK, {{2841116672U, 479917308U, 669260U, S21_SIGN_POSITIVE}}},  // 23
    // --- Дробные числа ---
    {0.1f, S21_CONVERSION_OK, {{1, 0, 0, SCALE(1) | S21_SIGN_POSITIVE}}},           // 24
    {-0.5f, S21_CONVERSION_OK, {{5, 0, 0, SCALE(1) | S21_SIGN_NEGATIVE}}},          // 25
    {123.456f, S21_CONVERSION_OK, {{123456, 0, 0, SCALE(3) | S21_SIGN_POSITIVE}}},  // 26
    // --- Степени 10 ---
    {1e5f, S21_CONVERSION_OK, {{100000, 0, 0, S21_SIGN_POSITIVE}}},         // 27 100000
    {1e-5f, S21_CONVERSION_OK, {{1, 0, 0, SCALE(5) | S21_SIGN_POSITIVE}}},  // 28 0.00001
    {1e10f, S21_CONVERSION_OK, {{1410065408, 2, 0, S21_SIGN_POSITIVE}}}     // 29 10000000000
};

// ========================
// TCase
// ========================
START_TEST(test_float_to_decimal) {
    float input = test_data[_i].input;
    int exp_return_value = test_data[_i].exp_return_value;
    s21_decimal exp_result = test_data[_i].exp_result;

    s21_decimal result = {0};
    int return_value = s21_from_float_to_decimal(input, &result);

    ck_assert_int_eq(return_value, exp_return_value);
    ck_assert_uint_eq(result.bits[0], exp_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], exp_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], exp_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], exp_result.bits[3]);
}
END_TEST

Suite* float_to_decimal_suite(void) {
    Suite* s = suite_create("S21_FROM_FLOAT_TO_DECIMAL SUITE");

    TCase* tc = tcase_create("s21_from_float_to_decimal");
    suite_add_tcase(s, tc);
    tcase_add_loop_test(tc, test_float_to_decimal, 0, sizeof(test_data) / sizeof(test_data[0]));

    return s;
}