#ifndef S21_TEST_SUITES_H
#define S21_TEST_SUITES_H

#include <check.h>

Suite* s21_ashlyuad_suite(void);
Suite* s21_orlandoh_suite(void);
Suite* s21_decimal_suite(void);
Suite* conversion_suite(void);
Suite* int_to_decimal_suite(void);
Suite* float_to_decimal_suite(void);
// Suite* from_int_to_decimal_suite(void);
// Suite* from_float_to_decimal_suite(void);
Suite* s21_add_other_function_suite(void);

#endif