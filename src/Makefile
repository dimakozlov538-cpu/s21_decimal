CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -I.
LIBS = -lcheck -lsubunit -lm -lpthread -lrt

COV_FLAGS =

SRC_DIR = s21_decimal
TEST_DIR = s21_test
BUILD_DIR = build
COV_REPORT_DIR = coverage_report

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
TEST_FILES := $(wildcard $(TEST_DIR)/*.c)

SRC_OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%_test.o, $(TEST_FILES))

TEST_BIN = $(BUILD_DIR)/tests

$(shell mkdir -p $(BUILD_DIR) $(dir $(SRC_OBJS)) $(dir $(TEST_OBJS)))

.PHONY: all test clean gcov_report coverage help

all: test

coverage: COV_FLAGS = -fprofile-arcs -ftest-coverage
coverage: clean test
	gcov $(SRC_FILES)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c s21_decimal.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(COV_FLAGS) -c $< -o $@

$(BUILD_DIR)/%_test.o: $(TEST_DIR)/%.c s21_decimal.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(COV_FLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

$(TEST_BIN): $(SRC_OBJS) $(TEST_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(COV_FLAGS) $^ -o $@ $(LIBS)

test: $(TEST_BIN)
	./$(TEST_BIN)

gcov_report: COV_FLAGS = -fprofile-arcs -ftest-coverage
gcov_report: clean test
	lcov --capture --directory $(BUILD_DIR) --output-file coverage.info -q

clean:
	rm -rf $(BUILD_DIR) coverage.info $(COV_REPORT_DIR)

help:
	@echo "Available targets:"
	@echo "  make           build and run tests"
	@echo "  make test      run tests"
	@echo "  make coverage  generate text gcov report"
	@echo "  make gcov_report  generate HTML coverage report"
	@echo "  make clean    remove all build artifacts"