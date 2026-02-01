CC = gcc
CC_FLAGS = -Werror -Wall -Wextra -std=c11

INCLUDE = -I.
GCOV_FLAGS = --coverage
LINK_FLAGS = $(shell pkg-config --cflags --libs check) --coverage -lm

LIB_HEADERS = s21_decimal.h s21_decimal/s21_utility/s21_decimal_extended.h
LIB_SRC = $(shell find s21_decimal/ -name "s21_*.c")
TESTS_HEADERS = s21_test/s21_test_suites.h
TESTS_SRC = $(shell find s21_test/ -name "s21_*.c")

TARGET_LIB = s21_decimal.a
TARGET_TESTS = s21_tests
TARGET_COVERATE = s21_tests_coverage
TARGET_COVERATE_INFO = s21_coverage.info

LIB_OBJ = $(LIB_SRC:%.c=%.o)
TESTS_OBJ = $(TESTS_SRC:%.c=%.o)
GCOV_OBJ = $(LIB_SRC:.c=.gcov.o) $(TESTS_SRC:.c=.gcov.o)

REPORT_OUT = lcov_out

%.o: %.c $(LIB_HEADERS)
	$(CC) $(CC_FLAGS) $(INCLUDE) -c $< -o $@

%.gcov.o: %.c $(LIB_HEADERS)
	$(CC) $(CC_FLAGS) $(GCOV_FLAGS) $(INCLUDE) -c $< -o $@

all: $(TARGET_LIB)

$(TARGET_LIB): $(LIB_OBJ)
	ar rcs $@ $?

test: $(TARGET_TESTS)

run_tests: $(TARGET_TESTS)
	@./$<

$(TARGET_TESTS) : $(TESTS_OBJ) $(TARGET_LIB)
	$(CC) $(INCLUDE) $^ -o $@ $(LINK_FLAGS)

gcov_report: $(TARGET_COVERATE_INFO)

$(TARGET_COVERATE_INFO): $(TARGET_COVERATE)
	-./$<
	lcov -c -d . -o $@
	genhtml $@ --output-directory $(REPORT_OUT)

$(TARGET_COVERATE) : $(GCOV_OBJ)
	$(CC) $(INCLUDE) $^ -o $@ $(LINK_FLAGS)

clean:
	rm -f $(TARGET_LIB) $(TARGET_TESTS) $(TARGET_COVERATE) $(TARGET_COVERATE_INFO)
	rm -f $(LIB_OBJ) $(TESTS_OBJ) $(GCOV_OBJ) $(GCOV_OBJ:.o=.gcda) $(GCOV_OBJ:.o=.gcno)
	rm -rf $(REPORT_OUT)

rebuild: clean all

format: $(LIB_HEADERS) $(LIB_SRC) $(TESTS_HEADERS) $(TESTS_SRC)
	@cp ../materials/linters/.clang-format .
	clang-format -i $^
	@rm .clang-format

.PHONY: all test run_tests gcov_report clean rebuild format
