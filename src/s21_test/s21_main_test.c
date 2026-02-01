#include <check.h>

#include "s21_test_suites.h"

int main() {
  int number_failed;
  Suite* suite = suite_create("s21_string");
  SRunner* runner;

  s21_add_other_function_suite(suite);

  runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (number_failed == 0) ? 0 : 1;
}
